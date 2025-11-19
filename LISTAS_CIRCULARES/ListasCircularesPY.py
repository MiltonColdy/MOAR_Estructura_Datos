class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

head = None

def beginsert():
    global head
    item = int(input("Ingrese valor: "))
    ptr = Node(item)

    if head is None:
        head = ptr
        ptr.next = head
    else:
        temp = head
        while temp.next != head:
            temp = temp.next

        ptr.next = head
        head = ptr
        temp.next = head

    print("Nodo insertado")

def lastinsert():
    global head
    item = int(input("Ingrese valor: "))
    ptr = Node(item)

    if head is None:
        head = ptr
        ptr.next = head
    else:
        temp = head
        while temp.next != head:
            temp = temp.next

        temp.next = ptr
        ptr.next = head

    print("Nodo insertado")

def randominsert():
    global head
    item = int(input("Valor: "))
    loc = int(input("Ubicación: "))

    ptr = Node(item)
    temp = head

    for _ in range(loc):
        temp = temp.next
        if temp == head:
            print("No se puede insertar")
            return

    ptr.next = temp.next
    temp.next = ptr
    print("Nodo insertado")

def begdelete():
    global head
    if head is None:
        print("Lista vacía")
        return

    if head.next == head:
        head = None
        print("Nodo eliminado")
        return

    last = head
    while last.next != head:
        last = last.next

    head = head.next
    last.next = head
    print("Nodo eliminado")

def lastdelete():
    global head
    if head is None:
        print("Lista vacía")
        return

    if head.next == head:
        head = None
        print("Nodo eliminado")
        return

    ptr = head
    prev = None

    while ptr.next != head:
        prev = ptr
        ptr = ptr.next

    prev.next = head
    print("Nodo eliminado")

def randelete():
    global head
    loc = int(input("Ubicación: "))

    if head is None:
        print("Lista vacía")
        return

    ptr = head
    prev = None

    for _ in range(loc):
        prev = ptr
        ptr = ptr.next
        if ptr == head:
            print("No se puede eliminar")
            return

    prev.next = ptr.next
    print("Nodo eliminado")

def search():
    global head
    if head is None:
        print("Lista vacía")
        return

    item = int(input("Elemento a buscar: "))
    ptr = head
    i = 0
    found = False

    while True:
        if ptr.data == item:
            print("Elemento encontrado en la ubicación", i + 1)
            found = True

        ptr = ptr.next
        i += 1

        if ptr == head:
            break

    if not found:
        print("Elemento no encontrado")

def display():
    global head
    if head is None:
        print("Nada que imprimir")
        return

    print("Imprimiendo valores...")
    ptr = head
    
    while True:
        print(ptr.data)
        ptr = ptr.next
        if ptr == head:
            break

def menu():
    choice = 0
    while choice != 9:
        print("\n******MENÚ PRINCIPAL******")
        print("1. Insertar al principio\n2. Insertar al final\n3. Insertar\n4. Eliminar del principio")
        print("5. Eliminar desde último\n6. Eliminar después de ubicación\n7. Buscar\n8. Mostrar\n9. Salir")
        choice = int(input("Ingrese opción: "))

        if choice == 1: beginsert()
        elif choice == 2: lastinsert()
        elif choice == 3: randominsert()
        elif choice == 4: begdelete()
        elif choice == 5: lastdelete()
        elif choice == 6: randelete()
        elif choice == 7: search()
        elif choice == 8: display()
        elif choice == 9: return

menu()