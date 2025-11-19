package LISTAS_DOBLEMENTE_ENLAZADAS;


import java.util.Scanner;

class Node {
    int data;
    Node next;
    Node prev;
}

public class ListaEnlazadaDobleJAVA {
    static Node head = null;
    static Scanner sc = new Scanner(System.in);

    public static void beginsert() {
        Node ptr = new Node();
        System.out.println("Ingrese valor:");
        ptr.data = sc.nextInt();

        ptr.next = head;
        ptr.prev = null;

        if (head != null)
            head.prev = ptr;

        head = ptr;
        System.out.println("Nodo insertado");
    }

    public static void lastinsert() {
        Node ptr = new Node();
        System.out.println("Ingrese valor:");
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

    public static void randominsert() {
        System.out.println("Valor:");
        int item = sc.nextInt();
        System.out.println("Ubicación:");
        int loc = sc.nextInt();

        Node ptr = new Node();
        ptr.data = item;

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

    public static void begdelete() {
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

    public static void lastdelete() {
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

    public static void randelete() {
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

        System.out.println("Nodo eliminado");
    }

    public static void search() {
        System.out.println("Elemento a buscar:");
        int item = sc.nextInt();

        Node ptr = head;
        int i = 0;
        int flag = 1;

        while (ptr != null) {
            if (ptr.data == item) {
                System.out.println("Elemento encontrado en la ubicación " + (i + 1));
                flag = 0;
            }
            i++;
            ptr = ptr.next;
        }

        if (flag == 1)
            System.out.println("Elemento no encontrado");
    }

    public static void display() {
        Node ptr = head;
        if (ptr == null) {
            System.out.println("Nada que imprimir");
            return;
        }

        System.out.println("Imprimiendo valores...");
        while (ptr != null) {
            System.out.println(ptr.data);
            ptr = ptr.next;
        }
    }

    public static void main(String[] args) {
        int choice = 0;

        while (choice != 9) {
            System.out.println("\n1.Insertar inicio\n2.Insertar final\n3.Insertar\n4.Borrar inicio\n5.Borrar final\n6.Borrar en pos\n7.Buscar\n8.Mostrar\n9.Salir");
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
                default: System.out.println("Opción inválida");
            }
        }
    }
}