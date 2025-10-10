const readline = require("readline");
const N = 25;
const MAX_SALIDAS = 3;
let laberinto = [];
for(let i=0;i<N;i++){
    laberinto[i] = [];
    for(let j=0;j<N;j++){
        laberinto[i][j] = "█";
    }
}
//De esta forma podemos declarar un arreglo, el cual va a estar lleno de cubitos (paredes).
function generar(x,y) {
    laberinto[x][y] = " ";
    let dir = [[-1,0],[1,0],[0,-1],[0,1]];
    dir.sort(() => Math.random()-0.5);

    for (let i = 0; i < dir.length; i++) {
        let ori = dir[i];
        let nx = x + ori[0]*2;
        let ny = y + ori[1]*2;

        if (nx > 0 && nx < N-1 && ny > 0 && ny < N-1 && laberinto[nx][ny] == "█") {
            laberinto[x+ori[0]][y+ori[1]] = " ";
            generar(nx, ny);
        }
    }
    for (let i = 0; i < N; i++) {
        laberinto[0][i] = "█";
        laberinto[24][i] = "█";
        laberinto[i][0] = "█";
        laberinto[i][24] = "█";
    }
    let pasillos = [];
        for (let i = 0; i < N-1; i++) {
            for (let j = 0; j < N-1; j++) {
                if(laberinto[i][j] == " ") {
                    pasillos.push([i, j]);
                }
        }
    }

    let puertas = [];
    while(puertas.length<MAX_SALIDAS) {
        let idx = Math.floor(Math.random()*pasillos.length);
    }
    laberinto[1][1] = "P";
}
function dibujar(){
    console.clear();
    for(let i=0;i<25;i++){
        console.log(laberinto[i].join(""));
    }
}
generar(1,1);
dibujar();
