arr = [10,5,25,45,30,50,35,20]
def ordInsercion(arr):
    for i in range(1,len(arr)): # En este tipo de for, el índice actual de arr es 
                                # lo que se guarda en i (como un contador inicializado en 1).
        temp = arr[i] # El valor del elemento actual se almacena temporalmente aquí.
        j = i-1 # j es el índice previo al actual del ciclo for.
        while j>=0 and temp < arr[j]:
            arr[j+1] = arr[j]
            j -= 1
        arr[j + 1] = temp
def printArr(arr):
    for i in range(len(arr)):
        print (arr[i],end=" ")
print("Arreglo original: ")
printArr(arr)
ordInsercion(arr)
print("\nArreglo ordenado: ") 
printArr(arr)
    