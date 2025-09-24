arr = [10,30,5,25,35,50,45]
print ("Arreglo desordenado: ")
print (arr)
for i in range(0, len(arr)):
    min = i
    for j in range (i + 1, len(arr)):
        if arr[min] > arr [j]:
            min = j
    
    temp = arr[i]
    arr[i] = arr[min]
    arr[min] = temp

print ("Arreglo ordenado: ")
print (arr)