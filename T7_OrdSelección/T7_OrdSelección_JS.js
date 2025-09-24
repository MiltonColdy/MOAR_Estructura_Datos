arr = [10,30,5,25,35,50,45]
function printArr() {
    for (let i = 0; i < arr.length; i++) {
        process.stdout.write(arr[i].toString() + " ")
    }
}
console.log("Arreglo desordenado: ")
printArr()
for (let i = 0; i < arr.length; i++) {
    min = i
    for (let j = i + 1; j < arr.length; j++) {
        if (arr[min] > arr [j]) {
            min = j
        }
    }
    temp = arr[i]
    arr[i] = arr[min]
    arr[min] = temp
}
console.log("\nArreglo ordenado: ")
printArr()