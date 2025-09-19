let arr = [11,2,63,19,0,1,49,14,23]

function burbuja() {
    for (var i = 0; i < arr.length; i++) {
        for (var j = 0; j < arr.length - i - 1; j++){
            if (arr[j] > arr[j+1]) {
                let temp = arr[j]
                arr[j] = arr[j+1]
                arr[j+1] = temp
            }
        }
            
                
    }
}
        
console.log("Arreglo original: ",arr)
burbuja()
console.log("Arreglo en orden: ",arr)