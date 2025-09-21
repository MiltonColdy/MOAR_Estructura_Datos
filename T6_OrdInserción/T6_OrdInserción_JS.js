arr = [10,5,25,45,30,50,35,20]
function ordInsercion() { 
    for (let i = 0; i < arr.length; i++) {
        temp = arr[i] // El valor del elemento actual se almacena temporalmente aquí.
        j = i-1 // j es el índice previo al actual del ciclo for.
        while (j>=0 && temp < arr[j]){
            arr[j+1] = arr[j]
            j -= 1
        }
           arr[j + 1] = temp
        }
    }                           
    
        
    
function printArr() {
    for (let i = 0; i < arr.length; i++) {
        process.stdout.write(arr[i].toString() + " ")
    }
}
console.log("Arreglo original: ")
printArr()
ordInsercion()
console.log("\nArreglo ordenado: ") 
printArr()
    