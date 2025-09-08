let numeros = [4,5,6,1,2,3,7,8,9];
let val = 9;
let pos = 0;
console.log("Arreglo antes de insertar:",numeros);

for (i = numeros.Length - 1; i > pos; i--) {
        numeros[i] = arr[i-1];
}

numeros[pos] = val;

console.log("Arreglo después de insertar:",numeros);
