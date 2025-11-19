class Node:
    def __init__(self):
        self.data = 0
        self.next = None
        self.prev = None

head = None

def beginsert():
    global head
    item = int(input("Ingrese valor: "))
    ptr = Node()
    ptr.data = item
    ptr.next = head
    ptr.prev = None

    if head is not None:
        head.prev = ptr

    head = ptr
    print("Nodo insertado")

def lastinsert():
    global head
    ptr = Node()
    ptr.data = int(input("Ingrese valor: "))
    ptr.next = None

    if head is None:
        ptr.prev = None
        head = ptr
        return

    temp = head
    while temp.next is not None:
        temp = temp.next

    temp.next = ptr
    ptr.prev = temp

def randominsert():
    global head
    item = int(input("Valor: "))
    ptr = Node()
    ptr.data = item

    loc = int(input("Ubicación: "))

    temp = head
    for i in range(loc):
        temp = temp.next
        if temp is None:
            print("No se puede insertar")
            return

    ptr.next = temp.next
    ptr.prev = temp

    if temp.next is not None:
        temp.next.prev = ptr

    temp.next = ptr

def begdelete():
    global head
    if head is None:
        print("Lista vacía")
        return

    ptr = head
    head = head.next

    if head is not None:
        head.prev = None

    print("Nodo eliminado desde el principio")

def lastdelete():
    global head
    if head is None:
        print("Lista vacía")
        return
    if head.next is None:
        head = None
        return

    temp = head
    while temp.next is not None:
        temp = temp.next

    temp.prev.next = None

def randelete():
    global head
    loc = int(input("Ubicación: "))
    ptr = head

    for i in range(loc):
        ptr = ptr.next
        if ptr is None:
            print("No se puede eliminar")
            return

    if ptr.prev is not None:
        ptr.prev.next = ptr.next

    if ptr.next is not None:
        ptr.next.prev = ptr.prev

def display():
    ptr = head
    if ptr is None:
        print("Nada que imprimir")
    else:
        print("Imprimiendo valores...")
        while ptr is not None:
            print(ptr.data)
            ptr = ptr.next


while True:
    print("\n1.Insertar principio\n2.Insertar final\n3.Insertar\n4.Eliminar principio\n5.Eliminar final\n6.Insertar loc\n7.Eliminar loc\n8.Mostrar\n9.Salir")
    c = int(input("Opción: "))

    if c == 9:
        break

    if c == 1: beginsert()
    elif c == 2: lastinsert()
    elif c == 3: randominsert()
    elif c == 4: begdelete()
    elif c == 5: lastdelete()
    elif c == 6: randominsert()
    elif c == 7: randelete()
    elif c == 8: display()