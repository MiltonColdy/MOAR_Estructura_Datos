package LISTAS_CIRCULARES_DOBLE_ENLACE;


import java.util.Scanner;

class Node {
    int data;
    Node next;
    Node prev;
}

public class ListasCircularesDobleJAVA {
    static Node head;
    static Scanner sc = new Scanner(System.in);

    public static void main(String[] args) {
        int choice = 0;

        while (choice != 9) {
            System.out.println("\n\n******MENÚ PRINCIPAL******");
            System.out.println("\n1. Insertar al principio\n2. Insertar al final\n3. Insertar\n4. Eliminar del principio\n5. Eliminar desde el último\n6. Insertar ubicación\n7. Eliminar ubicación\n8. Mostrar\n9. Salir");
            System.out.println("\nIngrese su opción:");
            choice = sc.nextInt();

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
                default: System.out.println("Introduzca una opción válida...");
            }
        }
    }

    static void beginsert() {
        System.out.println("Ingrese valor:");
        int item = sc.nextInt();

        Node ptr = new Node();
        ptr.data = item;
        ptr.next = head;
        ptr.prev = null;

        if (head != null)
            head.prev = ptr;

        head = ptr;

        System.out.println("Nodo insertado");
    }

    static void lastinsert() {
        System.out.println("Ingrese valor:");
        Node ptr = new Node();
        ptr.data = sc.nextInt();
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
        System.out.println("Valor:");
        int item = sc.nextInt();

        Node ptr = new Node();
        ptr.data = item;

        System.out.println("Ubicación:");
        int loc = sc.nextInt();

        Node temp = head;
        for (int i = 0; i < loc; i++) {
            temp = temp.next;
            if (temp == null) {
                System.out.println("No se puede insertar");
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
            System.out.println("Lista vacía");
            return;
        }

        Node ptr = head;
        head = head.next;

        if (head != null)
            head.prev = null;

        System.out.println("Nodo eliminado desde el principio");
    }

    static void lastdelete() {
        if (head == null) {
            System.out.println("Lista vacía");
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
        System.out.println("Ubicación:");
        int loc = sc.nextInt();

        Node ptr = head;

        for (int i = 0; i < loc; i++) {
            ptr = ptr.next;
            if (ptr == null) {
                System.out.println("No se puede eliminar");
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
            System.out.println("Nada que imprimir");
        } else {
            System.out.println("\nImprimiendo valores...");
            while (ptr != null) {
                System.out.println(ptr.data);
                ptr = ptr.next;
            }
        }
    }
}