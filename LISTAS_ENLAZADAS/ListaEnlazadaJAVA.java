package LISTAS_ENLAZADAS;
import java.util.Scanner;

class Node {
    int data;
    Node next;
}

public class ListaEnlazadaJAVA {
    static Node head;
    static Scanner sc = new Scanner(System.in);

    public static void main(String[] args) {
        int choice = 0;
        while (choice != 9) {
            System.out.println("\n\n******MENÚ PRINCIPAL******");
            System.out.println("\nELIGE UNA OPCIÓN...");
            System.out.println("\n1. Insertar al principio\n2. Insertar al final\n3. Insertar\n4. Eliminar del principio\n"
                    + "5. Eliminar desde el último\n6. Eliminar nodo después de la ubicación\n7. Buscar\n8. Mostrar\n9. Salir");

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
                default: System.out.println("Opción inválida");
            }
        }
    }

    static void beginsert() {
        Node ptr = new Node();
        System.out.println("Ingrese valor:");
        ptr.data = sc.nextInt();
        ptr.next = head;
        head = ptr;
        System.out.println("Nodo insertado");
    }

    static void lastinsert() {
        Node ptr = new Node();
        System.out.println("Ingrese valor:");
        ptr.data = sc.nextInt();

        if (head == null) {
            head = ptr;
            return;
        }
        Node temp = head;
        while (temp.next != null) temp = temp.next;
        temp.next = ptr;
    }

    static void randominsert() {
        Node ptr = new Node();
        System.out.println("Ingrese valor:");
        ptr.data = sc.nextInt();

        System.out.println("Ingrese ubicación:");
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
        temp.next = ptr;
    }

    static void begdelete() {
        if (head == null) {
            System.out.println("Lista vacía");
            return;
        }
        head = head.next;
        System.out.println("Nodo eliminado");
    }

    static void lastdelete() {
        if (head == null) {
            System.out.println("Lista vacía");
            return;
        } else if (head.next == null) {
            head = null;
            System.out.println("Nodo eliminado");
            return;
        }
        Node ptr = head, ptr1 = null;
        while (ptr.next != null) {
            ptr1 = ptr;
            ptr = ptr.next;
        }
        ptr1.next = null;
        System.out.println("Nodo eliminado");
    }

    static void randelete() {
        System.out.println("Ubicación:");
        int loc = sc.nextInt();

        Node ptr = head, ptr1 = null;

        for (int i = 0; i < loc; i++) {
            ptr1 = ptr;
            ptr = ptr.next;
            if (ptr == null) {
                System.out.println("No se puede eliminar");
                return;
            }
        }
        ptr1.next = ptr.next;
    }

    static void search() {
        System.out.println("Elemento a buscar:");
        int item = sc.nextInt();
        Node ptr = head;
        int i = 1;
        boolean found = false;

        while (ptr != null) {
            if (ptr.data == item) {
                System.out.println("Encontrado en " + i);
                found = true;
            }
            ptr = ptr.next;
            i++;
        }
        if (!found) System.out.println("No encontrado");
    }

    static void display() {
        Node ptr = head;
        if (ptr == null) {
            System.out.println("Nada que imprimir");
            return;
        }
        while (ptr != null) {
            System.out.println(ptr.data);
            ptr = ptr.next;
        }
    }
}