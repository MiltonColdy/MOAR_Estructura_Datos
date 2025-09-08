Num = [7,2,6,1,5,4,3,8,9]
enc = 0
buscar = 6
c = -1
for i in Num:
    c = c + 1
    if i == buscar:
        enc = 1
        
        print("El número [",buscar,"] ha sido encontrado en el índice: ",c)
        
if enc != 1:
    print("El número [",buscar,"] NO ha sido encontrado.")