package LISTAS_CIRCULARES;


import java.util.Scanner;

class Node {
    int data;
    Node next;
}

public class ListasCircularesJAVA {
    static Node head = null;
    static Scanner sc = new Scanner(System.in);

    public static void main(String[] args) {
        int choice = 0;

        while (choice != 9) {
            System.out.println("\n\n******MENÚ PRINCIPAL******");
            System.out.println("1. Insertar al principio\n2. Insertar al final\n3. Insertar\n4. Eliminar del principio");
            System.out.println("5. Eliminar desde el último\n6. Eliminar después de ubicación\n7. Buscar\n8. Mostrar\n9. Salir");
            System.out.print("Ingrese opción: ");
            choice = sc.nextInt();

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
                default: System.out.println("Opción inválida"); break;
            }
        }
    }

    static void beginsert() {
        System.out.print("Ingrese valor: ");
        int item = sc.nextInt();

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
        System.out.println("Nodo insertado");
    }

    static void lastinsert() {
        System.out.print("Ingrese valor: ");
        int item = sc.nextInt();

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
        System.out.println("Nodo insertado");
    }

    static void randominsert() {
        System.out.print("Valor: ");
        int item = sc.nextInt();

        System.out.print("Ubicación: ");
        int loc = sc.nextInt();

        Node ptr = new Node();
        ptr.data = item;

        Node temp = head;

        for (int i = 0; i < loc; i++) {
            temp = temp.next;

            if (temp == head) {
                System.out.println("No se puede insertar");
                return;
            }
        }

        ptr.next = temp.next;
        temp.next = ptr;

        System.out.println("Nodo insertado");
    }

    static void begdelete() {
        if (head == null) {
            System.out.println("Lista vacía");
            return;
        }

        if (head.next == head) {
            head = null;
            System.out.println("Nodo eliminado");
            return;
        }

        Node last = head;
        while (last.next != head)
            last = last.next;

        head = head.next;
        last.next = head;

        System.out.println("Nodo eliminado");
    }

    static void lastdelete() {
        if (head == null) {
            System.out.println("Lista vacía");
            return;
        }

        if (head.next == head) {
            head = null;
            System.out.println("Nodo eliminado");
            return;
        }

        Node ptr = head, ptr1 = null;

        while (ptr.next != head) {
            ptr1 = ptr;
            ptr = ptr.next;
        }

        ptr1.next = head;

        System.out.println("Nodo eliminado");
    }

    static void randelete() {
        System.out.print("Ubicación: ");
        int loc = sc.nextInt();

        if (head == null) {
            System.out.println("Lista vacía");
            return;
        }

        Node ptr = head, ptr1 = null;

        for (int i = 0; i < loc; i++) {
            ptr1 = ptr;
            ptr = ptr.next;

            if (ptr == head) {
                System.out.println("No se puede eliminar");
                return;
            }
        }

        ptr1.next = ptr.next;

        System.out.println("Nodo eliminado");
    }

    static void search() {
        if (head == null) {
            System.out.println("Lista vacía");
            return;
        }

        System.out.print("Elemento a buscar: ");
        int item = sc.nextInt();

        Node ptr = head;
        int i = 0;
        boolean found = false;

        do {
            if (ptr.data == item) {
                System.out.println("Elemento encontrado en la ubicación " + (i + 1));
                found = true;
            }

            ptr = ptr.next;
            i++;
        } while (ptr != head);

        if (!found)
            System.out.println("Elemento no encontrado");
    }

    static void display() {
        if (head == null) {
            System.out.println("Nada que imprimir");
            return;
        }

        System.out.println("Imprimiendo valores...");
        Node ptr = head;

        do {
            System.out.println(ptr.data);
            ptr = ptr.next;
        } while (ptr != head);
    }
}
