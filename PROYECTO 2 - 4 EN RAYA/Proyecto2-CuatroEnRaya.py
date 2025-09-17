import os
def victoria(tabl, fig):
    # Horizontal
    for fila in tabl:
        for j in range(len(fila) - 3):
            if all(celda == fig for celda in fila[j:j+4]):
                return True
    # Vertical
    for j in range(len(tabl[0])):
        for i in range(len(tabl) - 3):
            if all(tabl[i+k][j] == fig for k in range(4)):
                return True
    # Diagonal descendente (\)
    for i in range(len(tabl) - 3):
        for j in range(len(tabl[0]) - 3):
            if all(tabl[i+k][j+k] == fig for k in range(4)):
                return True
    # Diagonal ascendente (/)
    for i in range(3, len(tabl)):
        for j in range(len(tabl[0]) - 3):
            if all(tabl[i-k][j+k] == fig for k in range(4)):
                return True
    return False
def clear():
    os.system('cls' if os.name == 'nt' else 'clear') 
    # Esto permite que el clear pueda realizarse tanto en Linux como en Windows.
def tablero():
    for i in range(len(tabl)):         # i son las filas.
        for j in range(len(tabl[i])):  # j son las columnas.
                print("[", tabl[i][j], "]", end="")
        print("")
    for i in range(len(tabl[i])):  
        print(" ",i+1," ", end="")
    print("")
tabl = [[" "]*7 for i in range(6)] # Tablero.
print("| CUATRO EN RAYA |")
print("-------------------------------------")
turno = 1 # El turno.
ganar = False # Booleano de victoria.
con = "n"
while True:
   
    while True:
        try:
            clear()
            tablero()
            print("-------------------------------------")
            fig = "O" if turno  == 1 else "X" # Este es un else if compacto, me gustó esta forma de representarlo.
            print("TURNO DE LA FIGURA",fig)
            col = int(input("Columna en la que colocará su ficha (1-7): "))
            col -= 1  # Se ajusta el índice para que sea inicializado en 0.

            if 0 <= col <= 6:  # Validación dentro del rango.
                if tabl[0][col] == " ":  # Validación de espacio libre en la columna.
                    break 
                else:
                    print("Esta columna no tiene espacio libre.")
            else:
                print("Entrada inválida, ingrese un número dentro del rango.")
        except ValueError:
            print("Entrada inválida, ingrese un número entero.")
       
        
          
    for i in reversed(range(len(tabl))): # Es un barrido inverso de la matriz para cada fila.
        if tabl[i][col] == " ": # Es para la fila actual en la columna seleccionada.
            tabl[i][col] = fig
            break
    turno = 2 if turno == 1 else 1
    if victoria(tabl, fig):
        print(f"¡Jugador {fig} gana!")
        ganar = True
    if ganar == True:
        break
