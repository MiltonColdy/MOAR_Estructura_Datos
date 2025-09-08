Num = [[7,2,6],[1,5,4],[3,8,9]]
c = -1

filas = len(Num)
columnas = len(Num[0])

for j in range(columnas):  
    print("Columna de indice", j, ":", end=" ")
    for i in range(filas):  
        print("[", Num[i][j], "]", end=" ")
    print()