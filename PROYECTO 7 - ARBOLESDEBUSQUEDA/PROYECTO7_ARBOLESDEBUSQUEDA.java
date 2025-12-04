import java.io.*;
import java.util.*;

class Nodo {
    int key;
    Nodo left;
    Nodo right;

    public Nodo(int key) {
        this.key = key;
        left = null;
        right = null;
    }
}

class BST {
    private Nodo root;
    private int total;

    public BST() {
        root = null;
        total = 0;
    }

    // ------------------------------
    // INSERTAR
    // ------------------------------
    private Nodo insertarNodo(Nodo actual, int key) {
        if (actual == null) {
            total++;
            return new Nodo(key);
        }
        if (key < actual.key) {
            actual.left = insertarNodo(actual.left, key);
        } else if (key > actual.key) {
            actual.right = insertarNodo(actual.right, key);
        }
        return actual;
    }

    public void insert(int key) {
        root = insertarNodo(root, key);
    }

    // ------------------------------
    // BUSCAR (con ruta)
    // ------------------------------
    private boolean buscarNodo(Nodo actual, int key) {
        if (actual == null) return false;

        System.out.print(actual.key + " ");

        if (key == actual.key) return true;

        if (key < actual.key)
            return buscarNodo(actual.left, key);
        else
            return buscarNodo(actual.right, key);
    }

    public boolean search(int key) {
        return buscarNodo(root, key);
    }

    // ------------------------------
    // MINIMO
    // ------------------------------
    private Nodo minimo(Nodo actual) {
        while (actual.left != null)
            actual = actual.left;
        return actual;
    }

    // ------------------------------
    // ELIMINAR
    // ------------------------------
    private Nodo eliminarNodo(Nodo actual, int key) {
        if (actual == null)
            return null;

        if (key < actual.key) {
            actual.left = eliminarNodo(actual.left, key);
        }
        else if (key > actual.key) {
            actual.right = eliminarNodo(actual.right, key);
        }
        else {
            // Caso 1: hoja
            if (actual.left == null && actual.right == null) {
                total--;
                return null;
            }
            // Caso 2: un hijo
            else if (actual.left == null) {
                total--;
                return actual.right;
            }
            else if (actual.right == null) {
                total--;
                return actual.left;
            }
            // Caso 3: dos hijos
            else {
                Nodo suc = minimo(actual.right);
                actual.key = suc.key;
                actual.right = eliminarNodo(actual.right, suc.key);
            }
        }

        return actual;
    }

    public void deleteKey(int key) {
        root = eliminarNodo(root, key);
    }

    // ------------------------------
    // RECORRIDOS
    // ------------------------------
    private void inorderRec(Nodo actual) {
        if (actual == null) return;
        inorderRec(actual.left);
        System.out.print(actual.key + " ");
        inorderRec(actual.right);
    }

    private void preorderRec(Nodo actual) {
        if (actual == null) return;
        System.out.print(actual.key + " ");
        preorderRec(actual.left);
        preorderRec(actual.right);
    }

    private void postorderRec(Nodo actual) {
        if (actual == null) return;
        postorderRec(actual.left);
        postorderRec(actual.right);
        System.out.print(actual.key + " ");
    }

    public void inorder() { inorderRec(root); System.out.println(); }
    public void preorder() { preorderRec(root); System.out.println(); }
    public void postorder() { postorderRec(root); System.out.println(); }

    // ------------------------------
    // ALTURA
    // ------------------------------
    private int heightRec(Nodo actual) {
        if (actual == null) return 0;

        int h1 = heightRec(actual.left);
        int h2 = heightRec(actual.right);

        return 1 + Math.max(h1, h2);
    }

    public int height() {
        return heightRec(root);
    }

    // ------------------------------
    // TAMAÑO
    // ------------------------------
    public int size() {
        return total;
    }

    // ------------------------------
    // EXPORTAR INORDER
    // ------------------------------
    private void inorderToFile(Nodo actual, PrintWriter pw) {
        if (actual == null) return;
        inorderToFile(actual.left, pw);
        pw.print(actual.key + " ");
        inorderToFile(actual.right, pw);
    }

    public void exportar(String archivo) {
        try {
            PrintWriter pw = new PrintWriter(new FileWriter(archivo));
            inorderToFile(root, pw);
            pw.close();
            System.out.println("Exportado a: " + archivo);
        } catch (Exception e) {
            System.out.println("No se pudo exportar.");
        }
    }
}

// ========================================
// MENÚ PRINCIPAL
// ========================================
public class PROYECTO7_ARBOLESDEBUSQUEDA {

    public static void help() {
        System.out.println("insert X");
        System.out.println("search X");
        System.out.println("delete X");
        System.out.println("inorder");
        System.out.println("preorder");
        System.out.println("postorder");
        System.out.println("height");
        System.out.println("size");
        System.out.println("export archivo.txt");
        System.out.println("help");
        System.out.println("exit");
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        BST arbol = new BST();

        System.out.println("Gestor de BST en Java");
        System.out.println("Escribe 'help' para ver comandos.");
        System.out.println();

        while (true) {
            System.out.print("> ");
            String cmd = sc.next();

            if (cmd.equals("insert")) {
                int x = sc.nextInt();
                arbol.insert(x);
                System.out.println("Insertado.");
            }
            else if (cmd.equals("search")) {
                int x = sc.nextInt();
                System.out.print("Ruta: ");
                if (arbol.search(x))
                    System.out.println(" -> Encontrado");
                else
                    System.out.println(" -> No existe");
            }
            else if (cmd.equals("delete")) {
                int x = sc.nextInt();
                arbol.deleteKey(x);
                System.out.println("Eliminado.");
            }
            else if (cmd.equals("inorder")) arbol.inorder();
            else if (cmd.equals("preorder")) arbol.preorder();
            else if (cmd.equals("postorder")) arbol.postorder();
            else if (cmd.equals("height")) System.out.println("Altura: " + arbol.height());
            else if (cmd.equals("size")) System.out.println("Nodos: " + arbol.size());
            else if (cmd.equals("export")) {
                String archivo = sc.next();
                arbol.exportar(archivo);
            }
            else if (cmd.equals("help")) help();
            else if (cmd.equals("exit")) break;
            else System.out.println("Comando no valido.");
        }

        sc.close();
    }
}