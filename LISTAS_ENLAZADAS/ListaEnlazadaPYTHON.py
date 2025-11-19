class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

head = None

def beginsert():
    global head
    item = int(input("Ingrese valor: "))
    ptr = Node(item)
    ptr.next = head
    head = ptr

def lastinsert():
    global head
    item = int(input("Ingrese valor: "))
    ptr = Node(item)

    if head is None:
        head = ptr
        return

    temp = head
    while temp.next:
        temp = temp.next
    temp.next = ptr

def randominsert():
    global head
    item = int(input("Valor: "))
    loc = int(input("Ubicación: "))

    ptr = Node(item)
    temp = head

    for i in range(loc):
        temp = temp.next
        if temp is None:
            print("No se puede insertar")
            return

    ptr.next = temp.next
    temp.next = ptr

def begdelete():
    global head
    if head is None:
        print("Lista vacía")
        return
    head = head.next

def lastdelete():
    global head
    if head is None:
        print("Lista vacía")
        return
    if head.next is None:
        head = None
        return

    ptr = head
    ptr1 = None

    while ptr.next:
        ptr1 = ptr
        ptr = ptr.next

    ptr1.next = None

def randelete():
    global head
    loc = int(input("Ubicación: "))
    ptr = head
    ptr1 = None

    for i in range(loc):
        ptr1 = ptr
        ptr = ptr.next
        if ptr is None:
            print("No se puede eliminar")
            return

    ptr1.next = ptr.next

def search():
    item = int(input("Buscar: "))
    ptr = head
    i = 1
    found = False

    while ptr:
        if ptr.data == item:
            print("Encontrado en", i)
            found = True
        ptr = ptr.next
        i += 1

    if not found:
        print("No encontrado")

def display():
    ptr = head
    if not ptr:
        print("Nada que imprimir")
        return
    while ptr:
        print(ptr.data)
        ptr = ptr.next