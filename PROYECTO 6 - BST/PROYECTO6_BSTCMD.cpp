#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

/*===========================
   ESTRUCTURA DEL NODO
===========================*/
struct Node {
    int id;
    string nombre;
    string tipo;        // "folder" o "file"
    string contenido;   // solo si es archivo

    Node* parent;
    vector<Node*> children;
};

/*==================================
SERIALIZAR (Convertir Node* a JSON)
====================================*/
void to_json(json& j, const Node* n) {
    if (!n) {
        j = nullptr;
        return;
    }

    // Estructura base
    j["id"] = n->id;
    j["nombre"] = n->nombre;
    j["tipo"] = n->tipo;

    if (n->tipo == "file") {
        j["contenido"] = n->contenido;
    }

    // Función recursiva
    json children_j = json::array();
    for (const auto& child : n->children) {
        json child_j;
        to_json(child_j, child);
        children_j.push_back(child_j);
    }
    j["children"] = children_j;
}

/*====================================
DESERIALIZAR (Convertir JSON a Node*)
======================================*/
void from_json(const json& j, Node*& n) {
    if (j.is_null()) {
        n = nullptr;
        return;
    }

    // Crear el nuevo nodo y asignar valores
    n = new Node();
    n->id = j.at("id").get<int>();
    n->nombre = j.at("nombre").get<string>();
    n->tipo = j.at("tipo").get<string>();
    n->parent = nullptr;

    if (n->tipo == "file" && j.count("contenido")) {
        n->contenido = j.at("contenido").get<string>();
    } else {
        n->contenido = "";
    }

    // Procesar los hijos recursivamente
    if (j.count("children")) {
        for (const auto& child_j : j.at("children")) {
            Node* child = nullptr;
            from_json(child_j, child); // <--- Llamada recursiva
            if (child) {
                child->parent = n;
                n->children.push_back(child);
            }
        }
    }
}

void Pausa() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\nPress Key...";
    cin.get();
}

/*===========================
   ÁRBOL DE ARCHIVOS
===========================*/
class FileSystemTree {
private:
    Node* root;
    int nextID;

    // Limpieza de Memoria
    void deleteNodes(Node* node) {
        if (!node) {
            return;
        }

        // 1. Liberar recursivamente a todos los hijos (Postorden)
        for (Node* child : node->children) {
            deleteNodes(child);
        }

        // 2. Liberar la memoria del nodo actual
        delete node;
    }

public:
    // CONSTRUCTOR
    FileSystemTree() {
        root = new Node();
        root->id = 0;
        root->nombre = "/";
        root->tipo = "folder";
        root->parent = nullptr;
        nextID = 1;
    }

    // DESTRUCTOR
    ~FileSystemTree() {
        // Recorre y elimina todos los nodos a partir de la raíz
        deleteNodes(root);
        root = nullptr;
    }

    // GUARDAR EL ESTADO DEL ÁRBOL
    void save(const string& filename = "filesystem.json") {
        // 1. Serialización (Convertir el árbol C++ a formato JSON)
        json j;
        to_json(j, root); // 'j' ahora contiene la estructura completa del árbol

        // 2. Persistencia (Escribir el JSON en un archivo)
        ofstream file(filename);

        if (file.is_open()) {
            file << j.dump(2); // Convierte el objeto JSON a un string con '4' espacios de indentación
            file.close(); // Cierra el archivo después de escribir
            cout << "Sistema de archivos guardado en: " << filename << "\n";
        } else {
            cout << "ERROR: No se pudo abrir el archivo para guardar.\n";
        }
    }

    // REPARAR EL ESTADO DEL ARCHIVO
    void repair(const string& filename = "filesystem.json") {
        cout << "Reparando...\n\n";
        root = new Node();
        root->id = 0;
        root->nombre = "/";
        root->tipo = "folder";
        root->parent = nullptr;
        nextID = 1;
        FileSystemTree fs;
        fs.save(filename); // Guarda en memoria el nodo vacío (necesario)
    }

    // CARGAR EL ESTADO DEL ÁRBOL
    void load(const string& filename = "filesystem.json") {

        // 1. Limpieza Inicial de seguridad
        deleteNodes(root);
        root = nullptr; // Aseguramos que la raíz esté limpia antes de cargar

        // 2. Persistencia (Leer el archivo)
        // Se usa 'ifstream' para manejar la ENTRADA desde un archivo
        ifstream file(filename);

        if (!file.is_open()) {
            cout << "AVISO: Archivo " << filename << " no encontrado. Creando sistema vacío.\n";

            repair(); // Si el archivo no existe, inicializa un nuevo archivo limpio

            return; // Termina la función
        }

        try {
            // 3. Deserialización (Leer el JSON y reconstruir el árbol)

            // Convierte el contenido del archivo a un objeto json
            json j = json::parse(file);

            // Cierra el archivo después de leerlo
            file.close();

            // Reconstruye el árbol
            from_json(j, root);

            // Actualizar nextID para evitar IDs duplicados
            if (root) {
                // Encontramos el ID más alto de todo el árbol que acabamos de cargar
                int maxUsedID = findMaxID(root);

                // Se asigna el siguiente valor disponible
                nextID = maxUsedID + 1;
            }
            cout << "Sistema cargado exitosamente desde: " << filename << "\n";
            cout << "Elementos Totales del Arbol: " << nextID << "\n";

        } catch (const nlohmann::json::parse_error& e) {
            cout << "ERROR: El archivo JSON esta corrupto o mal formado.\n\n"; repair();
        } catch (...) {
            cout << "ERROR desconocido durante la carga.\n"; repair();
        }
    }

    // ENCONTRAR EL ID MÁXIMO
    int findMaxID(Node* node) {
        if (!node) {
            return -1; // Retorna un valor base (menor que 0) si el nodo es nulo
        }

        // 1. Inicializa el máximo con el ID del nodo actual (raíz)
        int maxId = node->id;

        // 2. Recorre recursivamente a todos los hijos
        for (Node* child : node->children) {
            // Llama a la función recursivamente para encontrar el ID más alto en el subárbol del hijo
            int childMaxId = findMaxID(child);

            // 3. Actualiza el máximo si se encuentra un ID más grande
            if (childMaxId > maxId) {
                maxId = childMaxId;
            }
        }

        return maxId;
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
        if (path == "/") return root;

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

    /*---------------------------
            MKDIR (carpeta)
    ---------------------------*/
    void mkdir(const string& path, const string& name) {
        Node* parent = findNodeByPath(path);

        cout << "\n";

        if (!parent) {
            cout << "Ruta no encontrada.\n";
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

    /*---------------------------
            TOUCH (archivo)
    ---------------------------*/
    void touch(const string& path, const string& name, const string& contenido = "") {
        Node* parent = findNodeByPath(path);

        cout << "\n";

        if (!parent) {
            cout << "Ruta no encontrada.\n";
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
            cout << "Ruta no encontrada.\n";
            return;
        }

        for (Node* c : node->children) {
            cout << (c->tipo == "folder" ? "[DIR] " : "[FILE] ");
            cout << c->nombre << "\n";
        }
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
            if (p != "/") fullPath += "/";
            fullPath += p;
        }
        return fullPath;
    }

    /*---------------------------
          PREORDER RECURSIVO
    ---------------------------*/
    void preorder(Node* node) {
        if (!node) return;
        cout << node->nombre << " (" << node->tipo << ")\n";
        for (Node* c : node->children)
            preorder(c);
    }

    void printPreorder() {
        preorder(root);
    }
};

/*=====================
    Flujo del Menú
=======================*/

void Mkdir(auto& fs) {
    string path, name;
    cout << "Ruta del padre: ";
    cin >> path;
    cout << "Nombre de la carpeta: ";
    cin >> name;
    fs.mkdir(path, name);
}

void Touch(auto& fs) {
    string path, name;
    cout << "Ruta del padre: ";
    cin >> path;
    cout << "Nombre del archivo: ";
    cin >> name;
    fs.touch(path, name);
}

void Ls(auto& fs) {
    string path;
    cout << "Ruta: ";
    cin >> path;
    fs.ls(path);
}

void FullRute(auto& fs) {
    string path;
    cout << "Ruta: ";
    cin >> path;
    Node* nodo = fs.findNodeByPath(path);
    if (nodo) {
        cout << fs.getFullPath(nodo) << "\n";
    } else {
        cout << "Ruta no encontrada.\n";
    }
}

void Guardar(auto& fs) {
    string filename = "filesystem.json";
    fs.save(filename);
}

/*===========================
            MAIN
===========================*/

int main() {
    FileSystemTree fs;
    fs.load("filesystem.json"); // Carga el Arbol desde la memoria

    cout << "\nContinuar...";
    cin.ignore();

    char Option;

    do {
        system("cls");
        cout << "\n===== MENU =====\n";
        cout << "1. MKDIR\n";
        cout << "2. TOUCH\n";
        cout << "3. LS\n";
        cout << "4. Ruta Completa\n";
        cout << "5. Preorden\n";
        cout << "6. Guardar\n";
        cout << "7. Salir\n\n";
        cout << "Opcion: ";
        cin >> Option;
        cout << "\n";

        if (Option == '1') {Mkdir(fs);}
        else if (Option == '2') {Touch(fs);}
        else if (Option == '3') {Ls(fs);}
        else if (Option == '4') {FullRute(fs);}
        else if (Option == '5') {fs.printPreorder();}
        else if (Option == '6') {Guardar(fs);}
        else if (Option == '7') {cout << "Adios :D.\n";}
        else {cout << "\nOpcion invalida.\n";}

        if (Option != '7') Pausa();

    } while (Option != '7');
    return 0;
}
