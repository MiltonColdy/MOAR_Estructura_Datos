arr = [11,2,63,19,0,1,49,14,23]

def burbuja():
    for i in range(len(arr)):
        for j in range(len(arr)-i-1):
            if arr[j] > arr[j+1]:
                temp = arr[j]
                arr[j] = arr[j+1]
                arr[j+1] = temp
print("Arreglo original: ",arr)
burbuja()
print("Arreglo en orden: ",arr)