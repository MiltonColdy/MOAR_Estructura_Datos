/*===============
   LIBRERÍAS
===============*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits>
using namespace std;
using json = nlohmann::json;
string rootname = "S:";

/*================
   ESTRUCTURAS
================*/

// NODO
struct Node {
    int id;
    string nombre;
    string tipo;        // "Folder" o "File"
    string contenido;   // Solo si es archivo

    Node* parent;
    vector<Node*> children;
};

void pausa() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Presiona ENTER para continuar...";
    cin.get();
}

/*===========================
   ÁRBOL DE ARCHIVOS
=======================*/
class FileSystemTree {
private:
    Node* root;
    int nextID;

public:
    /*-----------------
        CONSTRUCTOR
    -----------------*/
    FileSystemTree() {
        root = new Node();
        root->id = 0;
        root->nombre = rootname;
        root->tipo = "folder";
        root->parent = nullptr;
        nextID = 1;
    }

    /*---------------------------
         SPLIT DE RUTAS
    ---------------------------*/
    vector<string> splitPath(const string& path) {
        vector<string> tokens;
        string temp;
        stringstream ss(path);

        while (getline(ss, temp, '/')) {
            if (!temp.empty())
                tokens.push_back(temp);
        }
        return tokens;
    }

    /*---------------------------
        BUSCAR NODO POR RUTA
    ---------------------------*/
    Node* findNodeByPath(const string& path) {
        if (path == rootname) return root;

        vector<string> parts = splitPath(path);
        Node* current = root;

        for (auto& p : parts) {
            bool found = false;
            for (Node* child : current->children) {
                if (child->nombre == p) {
                    current = child;
                    found = true;
                    break;
                }
            }
            if (!found) return nullptr;
        }
        return current;
    }

    /*-----------------------
        MKDIR (Carpeta++)
    -----------------------*/
    void mkdir(const string& path, const string& name) {
        Node* parent = findNodeByPath(path);

        cout << "\n";

        if (!parent) {
            cout << "\tRuta no encontrada.\n";
            return;
        }

        Node* nuevo = new Node();
        nuevo->id = nextID++;
        nuevo->nombre = name;
        nuevo->tipo = "folder";
        nuevo->contenido = "";
        nuevo->parent = parent;

        parent->children.push_back(nuevo);
        cout << "Carpeta creada: " << name << "\n";
    }

    /*-----------------------
        TOUCH (Archivo++)
    -----------------------*/
    void touch(const string& path, const string& name, const string& contenido = "") {
        Node* parent = findNodeByPath(path);

        cout << "\n";

        if (!parent) {
            cout << "\tRuta no encontrada.\n";
            return;
        }

        Node* nuevo = new Node();
        nuevo->id = nextID++;
        nuevo->nombre = name;
        nuevo->tipo = "file";
        nuevo->contenido = contenido;
        nuevo->parent = parent;

        parent->children.push_back(nuevo);
        cout << "Archivo creado: " << name << "\n";
    }

    /*---------------------------
        LISTAR HIJOS
    ---------------------------*/
    void ls(const string& path) {
        Node* node = findNodeByPath(path);
        if (!node) {
            cout << "\tRuta no encontrada.\n";
            return;
        }

        for (Node* c : node->children) {
            cout << "\t" << (c->tipo == "folder" ? "[DIR] " : "[FILE] ");
            cout << c->nombre << "\n";
        }
    }

    // AUXILIAR DE LLAMADA ENTRE MENU Y PRIVATE
    Node* JmpAuxID(int targetID) {
        return AuxNodeID(root, targetID);
    }

    /*---------------------------
        OBTENER RUTA COMPLETA
    ---------------------------*/
    string getFullPath(Node* node) {
        vector<string> parts;
        Node* cur = node;

        while (cur != nullptr) {
            parts.push_back(cur->nombre);
            cur = cur->parent;
        }
        reverse(parts.begin(), parts.end());

        string fullPath;
        for (auto& p : parts) {
            if (p != rootname) fullPath += "/";
            fullPath += p;
        }
        return fullPath;
    }

    // AUXILIAR DE PREORDEN
    void printPreorder() {
        if (!root) return;
        cout << root->nombre << " (folder)\n"; // Imprime la raíz

        // Llamada a la función recursiva para los hijos de la raíz
        for (size_t i = 0; i < root->children.size(); ++i) {
            bool childIsLast = (i == root->children.size() - 1);
            preorder(root->children[i], "", childIsLast); // Comienza con prefijo vacío
        }
    }

    /*------------------------
        PREORDEN RECURSIVO
    ------------------------*/
    void preorder(Node* node) {
        if (!node) return;
        cout << node->nombre << " (" << node->tipo << ")\n";
        for (Node* c : node->children)
            preorder(c);
    }
};

/*===========================
            MAIN
===========================*/
int main() {
    FileSystemTree fs;
    int opcion;

    while (true) {
        system("cls");
        cout << "\n===== MENU =====\n";
        cout << "1. mkdir\n";
        cout << "2. touch\n";
        cout << "3. ls\n";
        cout << "4. ver ruta completa\n";
        cout << "5. preorden\n";
        cout << "6. salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            string path, name;
            cout << "Ruta del padre: ";
            cin >> path;
            cout << "Nombre carpeta: ";
            cin >> name;
            fs.mkdir(path, name);
        }
        else if (opcion == 2) {
            string path, name;
            cout << "Ruta del padre: ";
            cin >> path;
            cout << "Nombre archivo: ";
            cin >> name;
            fs.touch(path, name);
        }
        else if (opcion == 3) {
            string path;
            cout << "Ruta: ";
            cin >> path;
            fs.ls(path);
        }
        else if (opcion == 4) {
            string path;
            cout << "Ruta: ";
            cin >> path;
            Node* nodo = fs.findNodeByPath(path);
            if (nodo)
                cout << fs.getFullPath(nodo) << "\n";
            else
                cout << "Ruta no encontrada.\n";
        }
        else if (opcion == 5) {
            fs.printPreorder();
        }
        else if (opcion == 6) {
            break;
        }
        else {
            cout << "Opcion invalida.\n";
        }
        pausa();
    }

    return 0;
}
