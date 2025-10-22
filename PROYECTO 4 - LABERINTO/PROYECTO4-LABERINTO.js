const readline = require("readline");
const N = 25;
const fs = require("fs");
const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});
let MaxExits;
let MaxTraps;
let MaxLives;
let MaxKeys;
function RawMode() {
    readline.emitKeypressEvents(process.stdin);
    process.stdin.setRawMode(true);
    process.stdout.write("\x1B[?25l");
}
let points = 0;
let lives = 2;
let health = 100;
let keys = 0;
let lab = [];
let labH = [];
let hitWall = false;
let level = 1;
for (let i = 0; i < N; i++) {
    lab[i] = [];
    for (let j = 0; j < N; j++) {
        lab[i][j] = "█";
    }
}
for (let i = 0; i < N; i++) {
    labH[i] = [];
    for (let j = 0; j < N; j++) {
        labH[i][j] = "█";
    }
}
let P = [1,1];
function saveGame(filename = "save.txt") {
    const data = {
        lives,
        health,
        keys,
        level,
        P,       // posición del jugador
        lab       // estado del laberinto
    };

    fs.writeFileSync(filename, JSON.stringify(data), "utf8");
}
function loadGame(filename = "save.txt") {
    const raw = fs.readFileSync(filename, "utf8");
    const data = JSON.parse(raw);

    lives = data.lives;
    health = data.health;
    keys = data.keys;
    level = data.level;
    P = data.P;
    lab = data.lab;
    draw();  // refresca la pantalla con los valores cargados
}
function labArr() {
    for (let i = 0; i < N; i++) {
    lab[i] = [];
    for (let j = 0; j < N; j++) {
        lab[i][j] = "█";
    }
}
for (let i = 0; i < N; i++) {
    labH[i] = [];
    for (let j = 0; j < N; j++) {
        labH[i][j] = "█";
    }
}
}
//De esta forma podemos declarar un arreglo, el cual va a estar lleno de cubitos (paredes).
function generate(x,y) {
    lab[x][y] = " ";
    let dir = [[-1,0],[1,0],[0,-1],[0,1]];
    dir.sort(() => Math.random()-0.5);

    for (let i = 0; i < dir.length; i++) {
        let ori = dir[i];
        let nx = x + ori[0]*2;
        let ny = y + ori[1]*2;

        if (nx > 0 && nx < N-1 && ny > 0 && ny < N-1 && lab[nx][ny] == "█") {
            lab[x+ori[0]][y+ori[1]] = " ";
            generate(nx, ny);
        }
    }
    for (let i = 0; i < N; i++) {
        lab[0][i] = "█";
        lab[24][i] = "█";
        lab[i][0] = "█";
        lab[i][24] = "█";
    }
}
function exit() {
    let r = Math.random();
    if (r < 1/3) {
        lab[23][23] = "S";
    } else if (r < 2/3) {
        lab[1][23] = "S";
    } else {
        lab[23][1] = "S";
    }
}
function exitDoors() {
    let c = 0;
    for (let i = 0; i < 25; i++) {
        let r = Math.random();
        if (r < 1/15 && lab[i][0] == "█" && lab[i][1] != "█" && c < MaxExits)
        {
            lab[i][0] = "E";
            c += 1; 
        }
        if (r < 1/15 && lab[i][24] == "█" && lab[i][23] != "█" && c < MaxExits)
        {
            lab[i][24] = "E";
            c += 1;
        }
        if (r < 1/15 && lab[0][i] == "█" && lab[1][i] != "█" && c < MaxExits)
        {
            lab[0][i] = "E";
            c += 1;
        }
        if (r < 1/15 && lab[24][i] == "█" && lab[23][i] != "█" && c < MaxExits)
        {
            c += 1;
            lab[24][i] = "E";
        }
    }
}
function freeSpace(x, y) {
    return lab[x][y] == " " &&
           lab[x][y+1] != "T" && 
           lab[x][y-1] != "T" &&
           lab[x+1][y] != "T" &&
           lab[x-1][y] != "T";
}
function extras() {
    // TRAMPAS
    let c = 0;
    for (let x = 0; x < 24; x++) {
        for (let y = 0; y < 24; y++) {
            let r = Math.random();
            if (r < 1/15 && lab[x][y] == " " && c < MaxTraps && freeSpace(x, y)) {
                lab[x][y] = "T";
                c++;
            }
        }
    }
    // VIDAS
    c = 0;
    for (let x = 0; x < 24; x++) {
        for (let y = 0; y < 24; y++) {
            r = Math.random();
            if (r < 1/40 && lab[x][y] == " " && c < MaxLives) {
                lab[x][y] = "V";
                c++;
            }
        }
    }
    // LLAVES
    c = 0;
    for (let x = 0; x < 24; x++) {
        for (let y = 0; y < 24; y++) {
            r = Math.random();
            if (r < 1/40 && lab[x][y] == " " && c < MaxKeys) {
                lab[x][y] = "L";
                c++;
            }
        }
    }
    
}
function draw() {
    console.clear();
    console.log("VIDAS " + '\x1b[31m♥\x1b[0m' + ": " + lives);
    console.log("SALUD " + '\x1b[32m†\x1b[0m' + ": " + health);
    console.log("LLAVES " + '\x1b[93m↑\x1b[0m' + ": " + keys);
    console.log("NIVEL " + level);
    console.log("PUNTAJE ©: " + points);
    for(let i=0;i<25;i++){
        console.log(lab[i].join(""));
    }
}
function inpt() {
process.stdin.on("keypress", (str, key) => {
    if (key.ctrl && key.name === "c") process.exit(); // Ctrl+C para salir
    lab[P[0]][P[1]] = " ";
    labH[P[0]][P[1]] = " ";
        switch(key.name) {
            case "w":
                P[0] -= 1;
                break;
            case "a":
                P[1] -= 1;
                break;
            case "s":
                P[0] += 1;
                break;
            case "d":
                P[1] += 1;
                break;
        }
    const Ncell = lab[P[0]][P[1]];

    if (P[0] > 24 || Ncell == "█" &&  key.name === "s")  {
        P[0] = P[0] - 1;
        hitWall = true;
    }
    if (P[1] > 24 || Ncell == "█"  && key.name === "d") {
        P[1] = P[1] - 1;
        hitWall = true;
    }
    if (P[0] < 0 || Ncell == "█" &&  key.name === "w" ) {
        P[0] = P[0] + 1;
        hitWall = true;
    }
    if (P[1] < 0 || Ncell == "█"&&  key.name === "a") {
        P[1] = P[1] + 1;
        hitWall = true;
    }

    if (P[0] > 24 || Ncell == "E" &&  key.name === "s" && keys == 0)  {
        P[0] = P[0] - 1;
        hitWall = true;
    }
    if (P[1] > 24 || Ncell == "E"  && key.name === "d" && keys == 0) {
        P[1] = P[1] - 1;
        hitWall = true;
    }
    if (P[0] < 0 || Ncell == "E" &&  key.name === "w" && keys == 0) {
        P[0] = P[0] + 1;
        hitWall = true;
    }
    if (P[1] < 0 || Ncell == "E"&&  key.name === "a" && keys == 0) {
        P[1] = P[1] + 1;
        hitWall = true;
    }
    check();
    lab[P[0]][P[1]] = "P";
    labH[P[0]][P[1]] = "P";
    //update();
    draw();
    });
}
function nextLvl() {
    if (level == 3) {
        draw();
        //update();
        console.log("HAS GANADO OMG :D");
        process.exit();
    } else {
        level += 1;
        MaxValData()
        labArr();
        generate(1,1)
        P[0] = 1;
        P[1] = 1;
        lab[1][1] = "P";
        labH[1][1] = "P";
        exit();
        exitDoors();
        extras();
        draw();
        saveGame();
    }
}
function check() {
    const Ncell = lab[P[0]][P[1]];
    const NcellH = labH[P[0]][P[1]];
    //SALIDAS
    if (Ncell == "S") {
        lab[P[0]][P[1]] = " ";
        draw();
        //update();
        nextLvl();
    } 
    //SALIDAS EXTRA
    if (Ncell == "E" && keys > 0) {
        lab[P[0]][P[1]] = "P";
        draw();
        //update();
        keys -= 1;
        nextLvl();
    }
    //DAÑO Y PÉRDIDA DE VIDAS
    if (Ncell == "T") {
        health -= 50;
        points -= 20;
    } 
    if (health <= 0) {
        if (lives > 0) {
            health = 100;
            lives -= 1;
            points -= 10;
        } else {
            gameOver();
            return;
        }
        
    }
    //SALUD Y VIDAS OBTENIDAS
    if (Ncell == "V") {
        lives += 1;
    } 
    //LLAVES
    if (Ncell == "L") {
        keys += 1;
    }
    //PUNTAJE AL CAMINAR
    if (NcellH == "█") {
        points += 10;
    }
}
function gameOver() {
    try {
        process.stdin.setRawMode(false);
    } catch (e) {}
    process.stdin.removeAllListeners("keypress");

    console.clear();
    console.log("╔═══════════╗");
    console.log("║ GAME OVER ║");
    console.log("╚═══════════╝");
    console.log("\n1) Nuevo juego");
    console.log("0) Salir");

    const rl2 = readline.createInterface({
        input: process.stdin,
        output: process.stdout
    });

    rl2.question("\nSelecciona una opción: ", (opc) => {
        rl2.close(); 
        switch (opc.trim()) {
            case "1":
                lives = 2;
                health = 100;
                keys = 0;
                points = 0;
                level = 1;
                P = [1, 1];
                process.stdin.resume();
                RawMode();
                labArr();
                MaxValData();
                generate(1,1);
                lab[1][1] = "P";
                labH[1][1] = "P";
                exit();
                exitDoors();
                extras();
                draw();
                inpt();
                break;

            case "0":
                console.log("Vuelva pronto :D");
                process.exit();


            default:
                console.log("Opción inválida.");
                setTimeout(gameOver, 1000);
                break;
        }
    });
}

function MaxValData() {
    switch (level) {
        case 1:
            MaxExits = 3;
            MaxKeys = 3;
            MaxLives = 3;
            MaxTraps = 20;
            break;
        case 2:
            MaxExits = 2;
            MaxKeys = 2;
            MaxLives = 1;
            MaxTraps = 25;
            break;
        case 3:
            MaxExits = 0;
            MaxKeys = 1;
            MaxLives = 0;
            MaxTraps = 30;
            break;
    }
}
function update() {
    console.clear();
    console.log("VIDAS " + '\x1b[31m♥\x1b[0m' + ": " + lives);
    console.log("SALUD " + '\x1b[32m†\x1b[0m' + ": " + health);
    console.log("LLAVES " + '\x1b[93m↑\x1b[0m' + ": " + keys);
    console.log("NIVEL " + level);
    console.log("PUNTAJE ©: " + points);
    for(let i=0;i<25;i++){
        console.log(labH[i].join(""));
    }
}
function startMenu() {
    let opc;
    console.clear();
    console.log("╔═══════════╗");
    console.log("║ MAZE GAME ║");
    console.log("╚═══════════╝");
    console.log("1) Nuevo juego");
    console.log("2) Cargar partida");
    console.log("0) Salir");

    rl.question("\nSelecciona una opción: ", (opc) => {
        switch (opc.trim()) {
            case "1":
                RawMode();
                MaxValData();
                generate(1,1);
                lab[1][1] = "P";
                labH[1][1] = "P";
                exit();
                exitDoors();
                extras();
                draw();
                //update();
                inpt();
                break;

            case "2":
                if (saveFile == false) {
                    setTimeout(startMenu, 1000);
                    break;
                } else {
                    loadGame();
                    draw();
                    inpt();
                    break;
                }
            case "0":
                console.log("Vuelva pronto :D");
                rl.close();
                process.exit();
                break;

            default:
                console.log("Opción inválida.");
                setTimeout(startMenu, 1000);
                break;
        }
    });
}
startMenu();

