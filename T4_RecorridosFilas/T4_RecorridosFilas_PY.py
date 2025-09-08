Num = [[7,2,6],[1,5,4],[3,8,9]]
c = -1
for fila in Num:
    c = c + 1
    print("Fila de indice",c,":" ,end = " ")
    for n in fila:
        print("[",n,"]",end = " " )
    print(" ")