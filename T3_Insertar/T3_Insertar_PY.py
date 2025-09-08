Num = [7,2,6,1,5,4,3,8,9]
val = 9
pos = 0
print("Arreglo antes de insertar:   ",Num)
for i in range(len(Num)-1,pos,-1):
        Num[i] = Num[i-1]

Num[pos] = val
print("Arreglo despues de insertar: ",Num)
"aita"