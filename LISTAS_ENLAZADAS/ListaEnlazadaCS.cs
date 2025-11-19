using System;

class Node {
    public int data;
    public Node next;
}

class Program {
    static Node head;

    static void Main() {
        int choice = 0;
        while (choice != 9) {
            Console.WriteLine("1. Insertar inicio");
            Console.WriteLine("2. Insertar final");
            Console.WriteLine("3. Insertar");
            Console.WriteLine("4. Eliminar inicio");
            Console.WriteLine("5. Eliminar final");
            Console.WriteLine("6. Eliminar en posición");
            Console.WriteLine("7. Buscar");
            Console.WriteLine("8. Mostrar");
            Console.WriteLine("9. Salir");

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
            }
        }
    }

    static void beginsert() {
        Console.Write("Valor: ");
        int item = int.Parse(Console.ReadLine());
        Node ptr = new Node();
        ptr.data = item;
        ptr.next = head;
        head = ptr;
    }

    static void lastinsert() {
        Console.Write("Valor: ");
        int item = int.Parse(Console.ReadLine());
        Node ptr = new Node { data = item };

        if (head == null) { head = ptr; return; }

        Node temp = head;
        while (temp.next != null) temp = temp.next;
        temp.next = ptr;
    }

    static void randominsert() {
        Console.Write("Valor: ");
        int item = int.Parse(Console.ReadLine());
        Console.Write("Ubicación: ");
        int loc = int.Parse(Console.ReadLine());

        Node ptr = new Node { data = item };
        Node temp = head;

        for (int i = 0; i < loc; i++) {
            temp = temp.next;
            if (temp == null) {
                Console.WriteLine("No se puede insertar");
                return;
            }
        }
        ptr.next = temp.next;
        temp.next = ptr;
    }

    static void begdelete() {
        if (head == null) { Console.WriteLine("Lista vacía"); return; }
        head = head.next;
    }

    static void lastdelete() {
        if (head == null) return;
        if (head.next == null) { head = null; return; }

        Node ptr = head, ptr1 = null;
        while (ptr.next != null) {
            ptr1 = ptr;
            ptr = ptr.next;
        }
        ptr1.next = null;
    }

    static void randelete() {
        Console.Write("Ubicación: ");
        int loc = int.Parse(Console.ReadLine());

        Node ptr = head, ptr1 = null;

        for (int i = 0; i < loc; i++) {
            ptr1 = ptr;
            ptr = ptr.next;
            if (ptr == null) {
                Console.WriteLine("No se puede eliminar");
                return;
            }
        }
        ptr1.next = ptr.next;
    }

    static void search() {
        Console.Write("Buscar: ");
        int item = int.Parse(Console.ReadLine());

        Node ptr = head;
        int pos = 1;
        bool found = false;

        while (ptr != null) {
            if (ptr.data == item) {
                Console.WriteLine($"Encontrado en {pos}");
                found = true;
            }
            ptr = ptr.next;
            pos++;
        }
        if (!found) Console.WriteLine("No encontrado");
    }

    static void display() {
        Node ptr = head;
        while (ptr != null) {
            Console.WriteLine(ptr.data);
            ptr = ptr.next;
        }
    }
}