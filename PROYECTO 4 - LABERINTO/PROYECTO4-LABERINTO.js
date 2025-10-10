const readline = require("readline");
const N = 25;
const MAX_SALIDAS = 3;
readline.emitKeypressEvents(process.stdin);
process.stdin.setRawMode(true);

let lab = [];
for(let i=0;i<N;i++){
    lab[i] = [];
    for(let j=0;j<N;j++){
        lab[i][j] = "█";
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

        if (nx > 0 && nx < N-1 && ny > 0 && ny < N-1 && labo[nx][ny] == "█") {
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

    lab[1][1] = "P";
}
function draw(){
    console.clear();
    for(let i=0;i<25;i++){
        console.log(laberinto[i].join(""));
    }
}

function update() {
    if (key == "w") {
        P = P + [-1,0];
    }
}
process.stdin.on('data', (chunk) => {
    const key = chunk.toString();
    if (key === '\u0003') process.exit(); // Ctrl+C
});

process.stdin.on('keyup', (key) => {
    keys[key.name] = false;
});


generate(1,1);
draw();
