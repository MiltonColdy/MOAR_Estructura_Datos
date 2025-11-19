using System;

class Node {
    public int data;
    public Node next;
    public Node prev;
}

class Program {
    static Node head;

    static void Main() {
        int choice = 0;

        while (choice != 9) {
            Console.WriteLine("\n\n******MENÚ PRINCIPAL******");
            Console.WriteLine("\n1. Insertar al principio\n2. Insertar al final\n3. Insertar\n4. Eliminar del principio\n5. Eliminar desde el último\n6. Insertar ubicación\n7. Eliminar ubicación\n8. Mostrar\n9. Salir");
            Console.WriteLine("\nIngrese su opción:");
            choice = int.Parse(Console.ReadLine());

            switch (choice) {
                case 1: beginsert(); break;
                case 2: lastinsert(); break;
                case 3: randominsert(); break;
                case 4: begdelete(); break;
                case 5: lastdelete(); break;
                case 6: randominsert(); break;
                case 7: randelete(); break;
                case 8: display(); break;
                case 9: return;
                default: Console.WriteLine("Introduzca una opción válida..."); break;
            }
        }
    }

    static void beginsert() {
        Console.WriteLine("Ingrese valor:");
        int item = int.Parse(Console.ReadLine());

        Node ptr = new Node();
        ptr.data = item;
        ptr.next = head;
        ptr.prev = null;

        if (head != null)
            head.prev = ptr;

        head = ptr;
        Console.WriteLine("Nodo insertado");
    }

    static void lastinsert() {
        Console.WriteLine("Ingrese valor:");
        Node ptr = new Node();
        ptr.data = int.Parse(Console.ReadLine());
        ptr.next = null;

        if (head == null) {
            ptr.prev = null;
            head = ptr;
            return;
        }

        Node temp = head;
        while (temp.next != null)
            temp = temp.next;

        temp.next = ptr;
        ptr.prev = temp;
    }

    static void randominsert() {
        Console.WriteLine("Valor:");
        int item = int.Parse(Console.ReadLine());

        Node ptr = new Node();
        ptr.data = item;

        Console.WriteLine("Ubicación:");
        int loc = int.Parse(Console.ReadLine());

        Node temp = head;

        for (int i = 0; i < loc; i++) {
            temp = temp.next;
            if (temp == null) {
                Console.WriteLine("No se puede insertar");
                return;
            }
        }

        ptr.next = temp.next;
        ptr.prev = temp;

        if (temp.next != null)
            temp.next.prev = ptr;

        temp.next = ptr;
    }

    static void begdelete() {
        if (head == null) {
            Console.WriteLine("Lista vacía");
            return;
        }

        Node ptr = head;
        head = head.next;

        if (head != null)
            head.prev = null;

        Console.WriteLine("Nodo eliminado desde el principio");
    }

    static void lastdelete() {
        if (head == null) {
            Console.WriteLine("Lista vacía");
            return;
        }
        if (head.next == null) {
            head = null;
            return;
        }

        Node temp = head;
        while (temp.next != null)
            temp = temp.next;

        temp.prev.next = null;
    }

    static void randelete() {
        Console.WriteLine("Ubicación:");
        int loc = int.Parse(Console.ReadLine());

        Node ptr = head;

        for (int i = 0; i < loc; i++) {
            ptr = ptr.next;
            if (ptr == null) {
                Console.WriteLine("No se puede eliminar");
                return;
            }
        }

        if (ptr.prev != null)
            ptr.prev.next = ptr.next;

        if (ptr.next != null)
            ptr.next.prev = ptr.prev;
    }

    static void display() {
        Node ptr = head;
        if (ptr == null) {
            Console.WriteLine("Nada que imprimir");
        } else {
            Console.WriteLine("\nImprimiendo valores...");
            while (ptr != null) {
                Console.WriteLine(ptr.data);
                ptr = ptr.next;
            }
        }
    }
}