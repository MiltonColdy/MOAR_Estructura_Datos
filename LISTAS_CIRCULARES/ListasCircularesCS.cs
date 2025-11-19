using System;

class Node {
    public int data;
    public Node next;
}

class Program {
    static Node head = null;

    static void Main() {
        int choice = 0;
        while (choice != 9) {
            Console.WriteLine("\n\n******MENÚ PRINCIPAL******");
            Console.WriteLine("\n1. Insertar al principio\n2. Insertar al final\n3. Insertar\n4. Eliminar del principio");
            Console.WriteLine("5. Eliminar desde el último\n6. Eliminar nodo después de ubicación\n7. Buscar\n8. Mostrar\n9. Salir");
            Console.Write("Ingrese opción: ");
            choice = int.Parse(Console.ReadLine());

            switch (choice) {
                case 1: beginsert(); break;
                case 2: lastinsert(); break;
                case 3: randominsert(); break;
                case 4: begdelete(); break;
                case 5: lastdelete(); break;
                case 6: randelete(); break;
                case 7: search(); break;
                case 8: display(); break;
                case 9: return;
                default: Console.WriteLine("Opción inválida"); break;
            }
        }
    }

    static void beginsert() {
        Console.Write("Ingrese valor: ");
        int item = int.Parse(Console.ReadLine());

        Node ptr = new Node();
        ptr.data = item;

        if (head == null) {
            head = ptr;
            ptr.next = head;
        } else {
            Node temp = head;

            while (temp.next != head)
                temp = temp.next;

            ptr.next = head;
            head = ptr;
            temp.next = head;
        }
        Console.WriteLine("Nodo insertado");
    }

    static void lastinsert() {
        Console.Write("Ingrese valor: ");
        int item = int.Parse(Console.ReadLine());

        Node ptr = new Node();
        ptr.data = item;

        if (head == null) {
            head = ptr;
            ptr.next = head;
        } else {
            Node temp = head;

            while (temp.next != head)
                temp = temp.next;

            temp.next = ptr;
            ptr.next = head;
        }
        Console.WriteLine("Nodo insertado");
    }

    static void randominsert() {
        Console.Write("Valor: ");
        int item = int.Parse(Console.ReadLine());

        Console.Write("Ubicación: ");
        int loc = int.Parse(Console.ReadLine());

        Node ptr = new Node();
        ptr.data = item;

        Node temp = head;

        for (int i = 0; i < loc; i++) {
            temp = temp.next;
            if (temp == head) {
                Console.WriteLine("No se puede insertar");
                return;
            }
        }

        ptr.next = temp.next;
        temp.next = ptr;

        Console.WriteLine("Nodo insertado");
    }

    static void begdelete() {
        if (head == null) {
            Console.WriteLine("Lista vacía");
            return;
        }

        if (head.next == head) {
            head = null;
            Console.WriteLine("Nodo eliminado");
            return;
        }

        Node last = head;
        while (last.next != head)
            last = last.next;

        Node ptr = head;
        head = head.next;
        last.next = head;

        Console.WriteLine("Nodo eliminado");
    }

    static void lastdelete() {
        if (head == null) {
            Console.WriteLine("Lista vacía");
            return;
        }

        if (head.next == head) {
            head = null;
            Console.WriteLine("Nodo eliminado");
            return;
        }

        Node ptr = head, ptr1 = null;

        while (ptr.next != head) {
            ptr1 = ptr;
            ptr = ptr.next;
        }

        ptr1.next = head;
        Console.WriteLine("Nodo eliminado");
    }

    static void randelete() {
        Console.Write("Ubicación: ");
        int loc = int.Parse(Console.ReadLine());

        if (head == null) {
            Console.WriteLine("Lista vacía");
            return;
        }

        Node ptr = head, ptr1 = null;

        for (int i = 0; i < loc; i++) {
            ptr1 = ptr;
            ptr = ptr.next;

            if (ptr == head) {
                Console.WriteLine("No se puede eliminar");
                return;
            }
        }

        ptr1.next = ptr.next;

        Console.WriteLine("Nodo eliminado");
    }

    static void search() {
        if (head == null) {
            Console.WriteLine("Lista vacía");
            return;
        }

        Console.Write("Elemento a buscar: ");
        int item = int.Parse(Console.ReadLine());

        Node ptr = head;
        int i = 0;
        bool found = false;

        do {
            if (ptr.data == item) {
                Console.WriteLine("Elemento encontrado en la ubicación " + (i + 1));
                found = true;
            }
            ptr = ptr.next;
            i++;
        } while (ptr != head);

        if (!found)
            Console.WriteLine("Elemento no encontrado");
    }

    static void display() {
        if (head == null) {
            Console.WriteLine("Nada que imprimir");
            return;
        }

        Console.WriteLine("Imprimiendo valores...");
        Node ptr = head;

        do {
            Console.WriteLine(ptr.data);
            ptr = ptr.next;
        } while (ptr != head);
    }
}