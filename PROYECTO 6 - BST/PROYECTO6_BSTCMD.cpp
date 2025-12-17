/*===============
   LIBRERÍAS
===============*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <limits>
#include <chrono>
#include <cstdlib>
#include <unordered_map>

#include "json.hpp"

// SIMPLIFICACIONES DE ESCRITURA
using namespace std;
using json = nlohmann::json;
string rootname = "S:";
string UserName = "USUARIO";

// ESPACIO DE UTILIDADES
namespace Utils {
    // Convertir el string a mayúsculas
    void Mayus(std::string& s) {
        std::transform(s.begin(), s.end(), s.begin(),::toupper);
    }

    bool ContainsIlegal(const string& s) {
        const string Ilegals = "/\:*?!+@#€¬[]^{}<>|";

        for (char c : s) {
            if (Ilegals.find(c) != string::npos) {
                return true;
            }
        }
        return false;
    }

    using namespace std::chrono;

    long long getCurrentTimeMs() {
        return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    }
}

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

// PAPELERA
struct TrashNode {
    Node* node;             // Puntero hacia el nodo que fue eliminado (junto con sus hijos)
    int originalParentID;   // ID del nodo padre al que debe ser restaurado
};

struct TrieNode {
    // Mapa que asocia un carácter (clave) con el siguiente nodo Trie (valor).
    // Esto es ideal ya que los caracteres pueden ser variados (letras, números, '/')
    unordered_map<char, TrieNode*> children;

    // Almacena el ID del nodo real del FileSystem.
    // Solo es true/válido si la ruta termina en este nodo.
    int fileSystemNodeID = -1;

    // Bandera para indicar si este nodo representa el final de una palabra/ruta
    bool isEndOfWord = false;

    TrieNode() : isEndOfWord(false) {}

    // Destructor para liberar memoria de los hijos
    ~TrieNode() {
        for (auto const& [key, val] : children) {
            delete val;
        }
    }
};

/*==============================
    INTERCAMBIOS DE MEMORIA
==============================*/

/*--------------------------------
    SERIALIZAR (Node* -> JSON)
--------------------------------*/

// ARBOL (ROOT = 'S:')
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

// PAPELERA (ROOT 'BIN')
void to_json(json& j, const TrashNode& tn) {
    // 1. Serializa el sub-árbol del nodo eliminado
    json node_j;
    to_json(node_j, tn.node); // Usa el to_json para Node*

    j["node"] = node_j;
    j["parent"] = tn.originalParentID; // Guarda el ID del padre
}

/*---------------------------------
    DESERIALIZAR (JSON -> Node*)
---------------------------------*/

// ARBOL (ROOT = 'S:')
void from_json(const json& j, Node*& n) {
    if (j.is_null()) {
        n = nullptr;
        return;
    }

    // Crea el nuevo nodo y asigna valores
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

    // Procesa los hijos recursivamente
    if (j.count("children")) {
        for (const auto& child_j : j.at("children")) {
            Node* child = nullptr;
            from_json(child_j, child); // Llamada recursiva
            if (child) {
                child->parent = n;
                n->children.push_back(child);
            }
        }
    }
}

// PAPELERA (ROOT 'BIN')
void from_json(const json& j, TrashNode& tn) {
    // 1. Deserializa el sub-árbol
    Node* restoredNode = nullptr;
    from_json(j.at("node"), restoredNode); // Usa from_json para Node*
    tn.node = restoredNode;

    // 2. Asigna el ID del padre original
    tn.originalParentID = j.at("parent").get<int>();

    // Se asigna el parent en nullptr para que no apunte a memoria invalida
    if (tn.node) {
        tn.node->parent = nullptr;
    }
}
/*================
    CLASE TRIE
================*/
class Trie {
private:
    TrieNode* root;

    // AUXILIAR: Recorrido DFS para obtener IDs (Usado en Autocompletado)
    void findIDsByPrefix(TrieNode* node, vector<int>& results) {
        if (!node) return;

        if (node->isEndOfWord && node->fileSystemNodeID != -1) {
            results.push_back(node->fileSystemNodeID);
        }

        for (auto const& [key, child] : node->children) {
            findIDsByPrefix(child, results);
        }
    }

    // AUXILIAR: Implementación recursiva de eliminación (O(L))
    // Retorna true si el nodo 'current' debe ser eliminado por su padre.
    bool removeRecursive(TrieNode* current, const string& path, int depth) {
        if (!current) return false;

        // 1. Caso Base: Hemos llegado al final de la ruta a eliminar
        if (depth == path.size()) {
            if (!current->isEndOfWord) return false; // El nodo no estaba indexado como palabra final

            current->isEndOfWord = false;        // Desmarcar el final de la palabra
            current->fileSystemNodeID = -1;      // Desvincular del FileSystem

            // Solo se puede eliminar si no es el final de OTRA palabra y no tiene hijos
            return current->children.empty();
        }

        // 2. Paso Recursivo
        char ch = path[depth];
        auto it = current->children.find(ch);

        if (it == current->children.end()) {
            return false; // Prefijo no existe, no hay nada que borrar
        }

        // Llamada recursiva para el hijo
        bool shouldDeleteChild = removeRecursive(it->second, path, depth + 1);

        // 3. Post-Procesamiento
        if (shouldDeleteChild) {
            delete it->second;      // Liberar la memoria del nodo hijo
            current->children.erase(it); // Quitar la referencia del mapa

            // Devolvemos true si el nodo actual puede ser eliminado (no es final de palabra
            // y su lista de hijos está vacía)
            return !current->isEndOfWord && current->children.empty();
        }
        return false;
    }

public:
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        delete root;
    }

    // Función para normalizar y obtener la ruta que realmente se indexará
    string normalizePath(const string& path) {
        string normalizedPath = path;
        // Si la ruta comienza con la raíz "S:", la omitimos
        if (normalizedPath.rfind(rootname, 0) == 0) {
            normalizedPath = normalizedPath.substr(rootname.length());
        }
        return normalizedPath;
    }

    // Insertar una ruta completa (O(L))
    void insert(const string& path, int nodeID) {
        TrieNode* current = root;
        string normalizedPath = normalizePath(path);

        if (normalizedPath.empty()) {
            // Caso especial: la raíz misma.
            current->fileSystemNodeID = nodeID;
            current->isEndOfWord = true;
            return;
        }

        for (char ch : normalizedPath) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = new TrieNode();
            }
            current = current->children[ch];
        }

        current->isEndOfWord = true;
        current->fileSystemNodeID = nodeID;
    }

    // Nuevo método para eliminar una ruta del índice (O(L))
    void remove(const string& path) {
        string normalizedPath = normalizePath(path);
        removeRecursive(root, normalizedPath, 0);
    }

    // Función principal para autocompletar/buscar por prefijo (O(L + M), donde M es el número de resultados)
    vector<int> autocomplete(const string& prefix) {
        TrieNode* current = root;
        vector<int> foundIDs;
        string normalizedPrefix = normalizePath(prefix); // Usar normalización aquí también

        // 1. Recorrer hasta el final del prefijo dado
        for (char ch : normalizedPrefix) {
            if (current->children.find(ch) == current->children.end()) {
                return {};
            }
            current = current->children[ch];
        }

        // 2. Buscar todos los descendientes
        findIDsByPrefix(current, foundIDs);
        return foundIDs;
    }

    // Función para limpiar y reconstruir el Trie (SOLO útil después de LOAD o como debug)
    void clear() {
        delete root;
        root = new TrieNode();
    }
};

/*=====================
   ÁRBOL DE ARCHIVOS
=======================*/
class FileSystemTree {
private:
    Node* root;
    int nextID;

    vector<TrashNode> trash;

    // NUEVO: Instancia del Trie para indexación
    Trie fileTrie;

    // AUXILIAR: Recorrido para rellenar el Trie
    void buildTrieRecursive(Node* current, const string& currentPath) {
        if (!current) return;

        // Crea la ruta completa del nodo actual
        string fullPath = currentPath + "/" + current->nombre;
        if (current == root) fullPath = rootname; // Caso especial para la raíz

        // Insertar la ruta completa y su ID en el Trie
        fileTrie.insert(fullPath, current->id);

        // Llamada recursiva
        for (Node* child : current->children) {
            buildTrieRecursive(child, fullPath);
        }
    }
    // LIMPIEZA DE MEMORIA
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

    // AUXILIAR RECURSIVO PARA ENOONTRAR UN NODO POR ID
    Node* AuxNodeID(Node* current, int targetID) {
        if (!current) return nullptr;

        if (current->id == targetID) {
            return current;
        }

        for (Node* child : current->children) {
            // Si lo encuentra en un subárbol, lo devuelve inmediatamente
            if (Node* found = AuxNodeID(child, targetID)) {
                return found;
            }
        }
        return nullptr;
    }

    // AUXILIAR RECURSIVO CON SANGRÍA ESTILO ÁRBOL
    void preorder(Node* node, const string& prefix, bool isLast) {
        if (!node) return;

        // 1. Dibuja el prefijo (las líneas de conexión)
        if (node != root) {
            cout << prefix;
            cout << (isLast ? "└── " : "├── "); // Dibuja la conexión actual
        }

        // 2. Imprime la información del nodo
        cout << node->nombre << " (" << node->tipo << ")\n";

        // 3. Prepara el nuevo prefijo para los hijos
        string newPrefix = prefix;
        if (node != root) {
            // El nuevo prefijo añade la línea vertical '|' si no fue el último hermano
            newPrefix += (isLast ? "    " : "│   ");
        }

        // 4. Llamada recursiva con el nuevo prefijo
        for (size_t i = 0; i < node->children.size(); ++i) {
            bool childIsLast = (i == node->children.size() - 1);
            preorder(node->children[i], newPrefix, childIsLast);
        }
    }

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

    /*----------------
        DESTRUCTOR
    ----------------*/
    ~FileSystemTree() {
        // 1. Libera el árbol principal desde 'root'
        deleteNodes(root);
        root = nullptr;

        // 2. Libera la memoria de los nodos en la papelera (trash)
        for (const auto& item : trash) { // Recorre TrashNode
            deleteNodes(item.node); // Libera el puntero al Node*
        }
    }
    /*------------------------------------
        BUSCAR/AUTOCOMPLETAR (por prefijo)
    ------------------------------------*/
    void search(const string& prefix) {
        // 1. Usar el Trie para obtener los IDs de todos los nodos que coinciden.
        vector<int> matchingIDs = fileTrie.autocomplete(prefix);

        if (matchingIDs.empty()) {
            cout << "No se encontraron rutas que coincidan con el prefijo: '" << prefix << "'\n";
            return;
        }

        cout << "\n---------- Resultados de Búsqueda para '" << prefix << "' (" << matchingIDs.size() << ") ----------\n";
        cout << "ID\t| Tipo\t| Ruta Completa\n";
        cout << "----------------------------------------------------------------------------------\n";

        // 2. Iterar sobre los IDs y usar tu función AuxNodeID para obtener el puntero al nodo real.
        for (int id : matchingIDs) {
            Node* node = AuxNodeID(root, id); // Tu función auxiliar recursiva

            if (node) { // Verificar si el nodo existe (debería existir si el Trie está sincronizado)
                cout << node->id << "\t| "
                     << (node->tipo == "folder" ? "DIR" : "FILE") << "\t| "
                     << getFullPath(node) << "\n";
            }
        }
        cout << "----------------------------------------------------------------------------------\n";
    }
    /*--------------------------------
        RECONSTRUIR ÍNDICE (Trie)
    --------------------------------*/
    void rebuildTrie() {
        fileTrie.clear(); // Limpia el Trie anterior
        buildTrieRecursive(root, ""); // Rellena el Trie a partir de la raíz
        cout << "\tIndice de búsqueda (Trie) reconstruido.\n";
    }

    /*---------------------------------
        GUARDAR EL ESTADO DEL ÁRBOL
    ---------------------------------*/
    void save(const string& filename = "filesystem.json") {
        json main_j;

        // 1. Serializar el arbol principal
        json root_j;
        to_json(root_j, root);
        main_j["root"] = root_j; // La raíz va bajo la clave "root"

        // 2. Serializar la papelera
        json trash_j = json::array();
        for (const auto& item : trash) {
            json j_item;
            to_json(j_item, item); // Usamos to_json(TrashNode)
            trash_j.push_back(j_item);
        }
        main_j["trash"] = trash_j; // La papelera va bajo la clave "trash".

        // 3. Persistencia (Escribir el JSON en UN solo archivo)
        ofstream file(filename);

        if (file.is_open()) {
            file << main_j.dump(2); // Guarda el objeto completo
            file.close();
            cout << "Sistema de archivos (root y papelera) guardado en: " << filename << "\n";
        } else {
            cout << "\tERROR: No se pudo abrir el archivo para guardar.\n";
        }
    }

    /*-----------------------------------
        REPARAR EL ESTADO DEL ARCHIVO
    -----------------------------------*/
    void repair(const string& filename = "filesystem.json") {
        cout << "\tReparando...\n";
        root = new Node();
        root->id = 0;
        root->nombre = rootname;
        root->tipo = "folder";
        root->parent = nullptr;
        nextID = 1;
        FileSystemTree fs;
        fs.save(filename); // Guarda en memoria el nodo vacío (necesario)
        cout << "\t";
    }

    /*---------------------------------
        CARGAR EL ESTADO DEL ÁRBOL
    ---------------------------------*/
    void load(const string& filename = "filesystem.json") {

        // 1. Limpieza Inicial de seguridad
        deleteNodes(root);
        // Limpia la memoria de los nodos en la papelera antes de cargar.
        for (const auto& item : trash) {
            deleteNodes(item.node);
        }
        trash.clear();
        root = nullptr;

        ifstream file(filename);

        cout << "\n===================================================================\n\n";

        if (!file.is_open()) {
            // Si no encuentra guardado, llama al repair.
            cout << "\tAVISO: Archivo " << filename << " no encontrado. Creando sistema vacío...\n";
            repair(filename); // Usamos repair(filename) para que use el nombre correcto.
            cout << "\n\tLa papelera está vacía.\n";
            cout << "\n===================================================================================";
            return; // Termina la función.
        }

        try {
            json j = json::parse(file);
            file.close();

            // 3.1. Cargar el Árbol Principal (Root)
            if (j.count("root")) { // Verifica que la clave "root" exista
                from_json(j.at("root"), root);
            } else {
                // Si no tiene "root", crea uno vacío.
                repair(filename);
                cout << "\n\tADVERTENCIA: Archivo JSON sin clave 'root' - Creando sistema vacío.\n";
                return;
            }

            // 3.2. Cargar la Papelera (Trash)
            if (j.count("trash")) { // Verifica que la clave "trash" exista
                for (const auto& j_item : j.at("trash")) {
                    TrashNode item;
                    from_json(j_item, item); // Cargamos usando from_json(TrashNode)
                    trash.push_back(item);
                }
                cout << "\tPapelera cargada exitosamente (" << trash.size() << " elementos)\n";
            }


            if (root) {
                int maxUsedID = findMaxID(root);
                // Busca IDs en la papelera para asegurar que nextID sea el máximo global
                for (const auto& item : trash) {
                    maxUsedID = max(maxUsedID, findMaxID(item.node));
                }
                rebuildTrie(); // <-- ¡Llamar aquí!
                nextID = maxUsedID + 1;
            }

            cout << "\tSistema cargado exitosamente desde: " << filename << "\n\n";
            cout << "\tSiguiente ID de elemento disponible: " << nextID << "\n";
            cout << "\n===================================================================";


        } catch (const nlohmann::json::parse_error& e) {

            cout << "\tERROR: El archivo JSON esta corrupto o mal formado...\n\n"; repair();
            cout << "\n\tLa papelera está vacía.\n";
            cout << "\n=====================================================================";
        } catch (...) {

            cout << "\tERROR desconocido durante la carga...\n"; repair();
            cout << "\n\tLa papelera está vacía.\n";
            cout << "\n=====================================================";
        }
    }

    /*----------------------------
        ENCONTRAR EL ID MÁXIMO
    ----------------------------*/
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

        // Valida la ruta
        if (!parent) {
            cout << "Ruta no encontrada.\n";
            return;
        }

        // Valida duplicidad de nombres
        for (Node* child : parent->children) {
            if (child->nombre == name) {
                cout << "ERROR: Ya existe un '" << name << "' en el directorio: " << getFullPath(parent) << "\n";
            return;
            }
        }

        // Creación del nuevo nodo
        Node* nuevo = new Node();
        nuevo->id = nextID++;
        nuevo->nombre = name;
        nuevo->tipo = "folder";
        nuevo->contenido = "";
        nuevo->parent = parent;

        // Guardado en el vector temporal
        parent->children.push_back(nuevo);

        // Confirmación visual
        cout << "Carpeta creada: " << name << "\n";
        // Inserción directa O(L)
        fileTrie.insert(getFullPath(nuevo), nuevo->id);
    }

    /*-----------------------
        TOUCH (Archivo++)
    -----------------------*/
    void touch(const string& path, const string& name, const string& contenido = "") {
        Node* parent = findNodeByPath(path);

        cout << "\n";

        // Valida la ruta
        if (!parent) {
            cout << "Ruta no encontrada.\n";
            return;
        }

        // Valida duplicidad de nombres
        for (Node* child : parent->children) {
            if (child->nombre == name) {
                cout << "ERROR: Ya existe un '" << name << "' en el directorio: " << getFullPath(parent) << "\n";
                return;
            }
        }

        // Creación del nuevo nodo
        Node* nuevo = new Node();
        nuevo->id = nextID++;
        nuevo->nombre = name;
        nuevo->tipo = "file";
        nuevo->contenido = contenido;
        nuevo->parent = parent;

        parent->children.push_back(nuevo);

        // Confirmación visual
        cout << "Archivo creado: " << name << "\n";
        // Inserción directa O(L)
        fileTrie.insert(getFullPath(nuevo), nuevo->id);
    }


    /*----------------
        RENOMBRAR
    ----------------*/
    void renameNode(const string& path, const string& newName) {
        // 1. Validar la búsqueda
        Node* nodeToRename = findNodeByPath(path);

        if (!nodeToRename) {
            cout << "ERROR: Ruta '" << path << "' no encontrada.\n";
            return;
        }

        // La raíz (id 0) no se puede renombrar
            if (nodeToRename == root) {
            cout << "ERROR: No se permite renombrar la carpeta raíz (" << rootname << ").\n";
            return;
        }

        // Obtiene el nodo padre
        Node* parent = nodeToRename->parent;

        // Verifica si el nuevo nombre ya existe en el padre
        for (Node* sibling : parent->children) {
            // Compara con todos los hermanos, excepto consigo mismo (nodeToRename)
            if (sibling != nodeToRename && sibling->nombre == newName) {
                cout << "ERROR: Ya existe un '" << newName << "' en el directorio padre.\n";
                return;
            }
        }

        // Obtiene la ruta antigua antes de renombrar
        string oldPath = getFullPath(nodeToRename);

        // 2. Realiza el renombrado
        string oldName = nodeToRename->nombre;
        nodeToRename->nombre = newName;

        // 3. Quita la entrada antigua del Trie
        fileTrie.remove(oldPath);

        // 4. Obtiene la nueva ruta y añade la nueva entrada
        string newPath = getFullPath(nodeToRename);
        fileTrie.insert(newPath, nodeToRename->id);

        cout << "Nodo renombrado: '" << oldName << "' -> '" << newName << "'\n";
    }

    /*---------------------
        MV (Mover Nodo)
    ---------------------*/
    void mv(const string& sourcePath, const string& destPath) {
        // 1. Encuentra el nodo a mover (origen)
        Node* sourceNode = findNodeByPath(sourcePath);
        if (!sourceNode) {
            cout << "ERROR: Ruta de origen '" << sourcePath << "' no encontrada.\n";
            return;
        }

        // La raíz no puede ser movida
        if (sourceNode == root) {
            cout << "ERROR: No se permite mover la carpeta raíz (" << rootname << ").\n";
            return;
        }

        // El padre del nodo a mover (necesario para la desconexión)
        Node* oldParent = sourceNode->parent;

        // 2. Encuentra el nodo destino
        Node* destParent = findNodeByPath(destPath);
        if (!destParent) {
            cout << "ERROR: Ruta de destino '" << destPath << "' no encontrada.\n";
            return;
        }

        // Verifica que sea una carpeta
        if (destParent->tipo != "folder") {
             cout << "ERROR: El destino '" << destPath << "' no es una carpeta.\n";
             return;
        }

        // Evita mover un nodo a sí mismo, a su padre o a uno de sus hijos
        Node* current = destParent;
        while (current != nullptr) {
            if (current == sourceNode) {
                cout << "ERROR: No se permite mover a un subdirectorio o a si mismo.\n";
                return;
            }
            current = current->parent;
        }

        // Evita duplicidad de nombres
        for (Node* sibling : destParent->children) {
            if (sibling->nombre == sourceNode->nombre) {
                cout << "ERROR: Ya existe un '" << sourceNode->nombre << "' en el directorio: " << destPath << "\n";
                return;
            }
        }

        // Obtiene la RUTA ANTIGUA antes de la desconexión
        string oldPath = getFullPath(sourceNode);

        // 3. Desconectar: Elimina el sourceNode del vector children de su padre original
        auto& children_list = oldParent->children;
        auto it = std::find(children_list.begin(), children_list.end(), sourceNode);

        if (it != children_list.end()) {
            children_list.erase(it); // Eliminación directa
        } else {
            // En caso de milagros...
            cout << "ERROR CRITICO! - Nodo de origen no encontrado.\n";
            return;
        }

        // 4. Reconectar: Añade el sourceNode al nuevo padre
        sourceNode->parent = destParent;
        destParent->children.push_back(sourceNode);

        // Elimina la entrada antigua y pone la nueva
        fileTrie.remove(oldPath);
        fileTrie.insert(getFullPath(sourceNode), sourceNode->id);

        cout << "Movido exitosamente: '" << sourcePath << "' a '" << destPath << "'.\n";
    }

    // CONSULTAR ESTADO DE TRASH
    bool isTrashEmpty() const {
        return trash.empty();
    }

    /*--------------------------------------
        RM (Eliminar y Mover a Papelera)
    --------------------------------------*/
    void rm(const string& path) {
        // 1. Encuentra el nodo a eliminar
        Node* nodeToRemove = findNodeByPath(path);

        if (!nodeToRemove) {
        cout << "ERROR: Ruta '" << path << "' no encontrada.\n";
        return;
        }

        // La raíz no debe ser eliminada
        if (nodeToRemove == root) {
            cout << "ERROR: No se permite eliminar la carpeta raíz (" << rootname << ").\n";
            return;
        }

        Node* oldParent = nodeToRemove->parent;

        // Obtiene la RUTA antes de la desconexión
        string oldPath = getFullPath(nodeToRemove);

        // 2. Desconexión: Elimina el nodo del vector children de su padre original
        auto& children_list = oldParent->children;
        children_list.erase(
            remove_if(children_list.begin(), children_list.end(),
            [nodeToRemove](Node* n)
            {return n == nodeToRemove;})
            );

        // 3. Mueve a la papelera (TrashNode Push)
        TrashNode trashItem;
        trashItem.node = nodeToRemove;
        trashItem.originalParentID = oldParent->id; // Guardamos el ID del padre original

        trash.push_back(trashItem); // Añadimos al vector temporal
        nodeToRemove->parent = nullptr; // Limpia la referencia al padre

        cout << "Elemento '" << nodeToRemove->nombre << "' movido a la papelera.\n";

        // Quita la entrada del Trie
        fileTrie.remove(oldPath);
    }

    /*-----------------------------------
        RESTORE-ID (Restaurar por ID)
    -----------------------------------*/
    void restoreID(int id, const string& destPath) {

        // 1. Búsqueda y Extracción del elemento de la papelera (O(N) en el vector)
        auto it = trash.begin();
        while (it != trash.end() && it->node->id != id) {
            ++it;
        }

        if (it == trash.end()) {
            cout << "ERROR: ID " << id << " no existe en la papelera.\n";
            return;
        }

        TrashNode trashItem = *it;
        trash.erase(it);

        Node* nodeToRestore = trashItem.node;
        Node* newParent = nullptr;
        string newName = nodeToRestore->nombre;
        string finalDestPath = destPath;


        // 2. Determina el padre a restaurar

        if (finalDestPath.empty()) {
            // 2A: Restaura en la ruta original (Si 'destPath' = "")
            newParent = AuxNodeID(root, trashItem.originalParentID);

            if (!newParent) {
                // Si el padre original ya no existe
                cout << "ERROR: Padre original (ID: " << trashItem.originalParentID << ") ya no existe.\n";
                trash.push_back(trashItem);
                return;
            }
            finalDestPath = getFullPath(newParent); // Para el caso de éxito

        } else {
            // 2B: Restaurar en la nueva ruta especificada
            newParent = findNodeByPath(finalDestPath);

            if (!newParent) {
                cout << "ERROR: Ruta de destino '" << finalDestPath << "' no encontrada.\n";
                trash.push_back(trashItem);
                return;
            }
        }

        // 3. Verifica duplicidad (Igual para ambas opciones)
        for (Node* sibling : newParent->children) {
            if (sibling->nombre == newName) {
                cout << "ERROR: Ya existe '" << newName << "' en la ruta destino: " << finalDestPath << "\n";
                trash.push_back(trashItem);
                return;
            }
        }

        // 4. En caso de exito
        nodeToRestore->parent = newParent;
        newParent->children.push_back(nodeToRestore);

        cout << "Elemento '" << nodeToRestore->nombre << "' restaurado exitosamente a: " << finalDestPath << "\n";

        // 5. Optimización del Trie
        fileTrie.insert(getFullPath(nodeToRestore), nodeToRestore->id);
    }

    /*---------------------------------------------
        BORRADO PERMANENTE INDIVIDUAL (DEL-ID)
    --------------------------------------------*/
    void delID(int id) {
        // 1. Busca el elemento por ID en la papelera
        auto it = trash.begin();
        while (it != trash.end()) {
            if (it->node->id == id) {
                break;
            }
            ++it;
        }

        if (it == trash.end()) {
            cout << "ERROR: El ID " << id << " no existe en la papelera.\n";
            return;
        }

        // 2. Borrado: Libera el subárbol del nodo y elimina el TrashNode
        Node* nodeToDelete = it->node;
        string name = nodeToDelete->nombre;

        deleteNodes(nodeToDelete); // Libera recursivamente toda la memoria

        trash.erase(it); // Elimina el elemento de la lista 'trash'

        cout << "Elemento '" << name << "' (ID: " << id << ") eliminado para SIEMPRE.\n";
    }

    /*-------------------------------------
        VACIAR TODA LA PAPELERA (EMPTY)
    -------------------------------------*/
    void emptyTrash() {
        if (trash.empty()) {
            cout << "\nLa papelera ya esta vacia.\n";
            return;
        }

        // 1. Libera la memoria de todos los nodos en la papelera
        for (const auto& item : trash) {
            deleteNodes(item.node);
        }

        // 2. Limpia el vector (los TrashNode)
        trash.clear();

        cout << "\nPapelera vaciada para SIEMPRE.\n";
    }

    /*--------------------------------
        LS-TRASH (Listar Papelera)
    --------------------------------*/
    void lsTrash() {
        if (trash.empty()) {
            cout << "La papelera esta vacia.\n";
            return;
        }

        cout << "\n---------- Papelera Temporal ----------\n";
        cout << "ID\t| Tipo\t| Nombre\n";
        cout << "----------------------------------------\n";

        for (const auto& item : trash) {
            Node* node = item.node;
            cout << node->id << "\t| "
                 << (node->tipo == "folder" ? "DIR" : "FILE") << "\t| "
                 << node->nombre << "\n";
        }
        cout << "----------------------------------------\n";
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
            fullPath += "/";
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

    int countNodes(Node* startNode) {
        if (!startNode) return 0;

        int count = 1; // Contar el nodo actual
        for (Node* child : startNode->children) {
            count += countNodes(child); // Recursividad
        }
        return count;
    }

    void createRandomTree(Node* baseNode, int N) {
        if (!baseNode || baseNode->tipo != "folder") return;

        // 1. Usa un vector para mantener la lista de posibles padres (rootNode inicialmente)
        vector<Node*> possibleParents = { baseNode };

        // 2. Bucle para N iteraciones
        for (int i = 1; i <= N; ++i) {
            // Selecciona un padre aleatorio de la lista de nodos ya creados
            Node* parent = possibleParents[rand() % possibleParents.size()];

            // Generar un nombre único (ej. "n" + ID)
            string name = "n" + to_string(nextID);

            Node* newNode = new Node();
            newNode->id = nextID++;
            newNode->nombre = name;
            newNode->parent = parent;

            // Decide si crear carpeta o archivo
            if (rand() % 2 == 0) {
                newNode->tipo = "folder";
                parent->children.push_back(newNode);
                possibleParents.push_back(newNode);
            } else {
                newNode->tipo = "file";
                parent->children.push_back(newNode);
            }

            // Indexación de Trie: O(L)
            fileTrie.insert(getFullPath(newNode), newNode->id);
        }
    }
};

/*========================
    PROCESOS DEL MENÚ
========================*/

/*-----------
    FLUJO
-----------*/

void Mkdir(auto& fs, stringstream& args) {
    string path, name;

    // Extrae los argumentos necesarios
    if (!(args >> path >> name)) {
        cout << "ERROR! - Sintaxis: MKDIR [Ruta del Padre] [Nombre]\n";
        return;
    }

    // Aplica la validación de caracteres prohibidos
    if (Utils::ContainsIlegal(name)) { // ❗ Llama a la nueva función
        cout << "ERROR: Nombre contiene caracteres prohibidos\n";
        return;
    }

    // Ejecuta la función per se
    fs.mkdir(path, name);
}

void Touch(auto& fs, stringstream& args) {
    string path, name;

    if (!(args >> path >> name)) {
        cout << "ERROR! - Sintaxis: TOUCH [Ruta del Padre] [Nombre]\n";
        return;
    }

    if (Utils::ContainsIlegal(name)) {
        cout << "ERROR: Nombre contiene caracteres prohibidos\n";
        return;
    }

    fs.touch(path, name);
}

void Renombrar(auto& fs, stringstream& args) {
    string path, newName;

    if (!(args >> path >> newName)) {
        cout << "ERROR! - Sintaxis: RN [Ruta] [Nuevo Nombre]\n";
        return;
    }

    if (Utils::ContainsIlegal(newName)) {
        cout << "ERROR: Nuevo nombre contiene caracteres prohibidos\n";
        return;
    }

    fs.renameNode(path, newName);
}

void Mover(auto& fs, stringstream& args) {
    string sourcePath, destPath;

    if (!(args >> sourcePath >> destPath)) {
        cout << "ERROR! - Sintaxis: MV [Ruta Origen] [Ruta Destino]\n";
        return;
    }

    fs.mv(sourcePath, destPath);

}

void Eliminar(auto& fs, stringstream& args) {
    string path;
    if (!(args >> path)) {
        cout << "ERROR! - Sintaxis: RM [Ruta del Nodo]\n";
        return;
    }
    fs.rm(path);
}

void Restore(auto& fs, stringstream& args) {
    if (fs.isTrashEmpty()) {
        cout << "Papelera vacía - Sin elementos a restaurar.\n";
        return;
    }

    int id = 0;
    string idStr, newParentRute = ""; // Inicializada a vacío

    // Lectura del ID (Obligatorio)
    if (!(args >> idStr)) {
        cout << "ERROR! Sintaxis: RS [ID] [Ruta Destino (opcional)]\n";
        return;
    }

    try {
        id = stoi(idStr);
    } catch (...) {
        cout << "ERROR: ID no válido o fuera de rango.\n";
        return;
    }

    if (id <= 0) {
        cout << "ERROR: ID [" << id << "] inválido - Se requiere ID positivo.\n";
        return;
    }

    // Lectura de la Ruta de Destino (Opcional)
    args >> newParentRute;

    // Ejecuta la restauración
    fs.restoreID(id, newParentRute);
}

void Ls(auto& fs, stringstream& args) {
    string path;

    if (!(args >> path)) {
        cout << "ERROR! - Sintaxis: LS [Ruta]\n";
        return;
    }

    fs.ls(path);
}

void FullRute(auto& fs, stringstream& args) {
    int id;
    string idStr;

    if (!(args >> idStr)) {
        cout << "ERROR! - Sintaxis: FR [ID]\n";
        return;
    }

    try {
        id = stoi(idStr);
    } catch (...) {
        cout << "ERROR: ID no válido o fuera de rango.\n";
        return;
    }

    Node* nodo = fs.JmpAuxID(id);

    if (nodo) {
        cout << "Ruta: " << fs.getFullPath(nodo) << "\n";
    } else {
        cout << "\nERROR: ID [ " << id << " ] no encontrado.\n";
    }
}

void DelID(auto& fs, stringstream& args) {
    if (fs.isTrashEmpty()) {
        cout << "Papelera vacía - Sin elementos a restaurar.\n";
        return;
    }

    int id = 0;
    string idStr;

    if (!(args >> idStr)) {
        cout << "ERROR! - Sintaxis: BDEL [ID]\n";
        return;
    }

    // Validación que ID sea mayor a 0
    try {
        id = stoi(idStr);
    } catch (...) {
        cout << "ERROR: ID no válido o fuera de rango.\n";
        return;
    }

    if (id <= 0) {
        cout << "ERROR: ID [" << id << "] inválido - Se requiere ID positivo.\n";
        return;
    }

    // Ejecuta la eliminación permanente
    fs.delID(id);
}

void Empty(auto& fs) {
    if (fs.isTrashEmpty()) {
        cout << "Papelera ya esta vacia.\n";
        return;
    }

    fs.emptyTrash();
}

void Guardar(auto& fs) {
    string filename = "filesystem.json";
    fs.save(filename);
}

void Search(auto& fs, stringstream& args) {
    string prefix;

    if (!(args >> prefix)) {
        cout << "ERROR! - Sintaxis: SR [Prefijo/Ruta]\n";
        return;
    }

    // Llama al método de la clase FileSystemTree
    fs.search(prefix);
}

void Pausa() {
    cout << "\n\nContinuar...";
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
}

void Contar(auto& fs, stringstream& args) {
    string path;

    if (!(args >> path)) {
        cout << "ERROR! - Sintaxis: CN [Ruta]\n";
        return;
    }

    Node* n = fs.findNodeByPath(path);
    if (!n) {
        cout << "ERROR! - Ruta no encontrada.\n";
    } else {
        cout << "Total de nodos: " << fs.countNodes(n) << "\n";
    }
}

void Test(auto& fs, stringstream& args) {
    int N;
    string N_str;

    if (!(args >> N_str)) {
        cout << "ERROR! - Sintaxis: TEST [Num. de Nodos]\n";
        return;
    }

    try {
        N = stoi(N_str);
    } catch (...) {
        cout << "ERROR! - Numero de nodos no válido.\n";
        return;
    }

    if (N <= 0) {
        cout << "ERROR! - El numero de nodos debe ser positivo.\n";
        return;
    }

    system("cls");
    system("color 17");

    long long startTime, endTime;

    // Garantizar que /test existe
    Node* testRoot = fs.findNodeByPath("/test");
    if (!testRoot) {
        fs.mkdir("/", "test");
        testRoot = fs.findNodeByPath("/test");
    }

    if (!testRoot) {
        cout << "\nERROR CRITICO: No se pudo crear /test\n";
        return;
    }

    cout << "\n======================================================\n";
    cout << "\tINICIANDO PRUEBA DE RENDIMIENTO (N = " << N << ")\n";
    cout <<   "======================================================\n";
    Pausa(); // Pausa tras cada operación

    // FASE 1: CREACIÓN DEL ÁRBOL (mkdir/touch)
    cout << "\n[1] Creando arbol de " << N << " nodos...\n";
    startTime = Utils::getCurrentTimeMs();

    fs.createRandomTree(testRoot, N); // Manda crear los nodos
    endTime = Utils::getCurrentTimeMs();
    Guardar(fs);

    cout << "\nTiempo de Creacion: " << (endTime - startTime) << " ms\n";
    Pausa();

    cout << "\nValidando insercion (Conteos y Estructura)...";

    int count = fs.countNodes(testRoot); // Asumiendo una función de conteo O(N)

    if (count >= N) {
        cout << "\n" << count << " nodos encontrados en la ruta de prueba.\n";
    } else {
         cout << "\nERROR DE VALIDACION: Solo se encontraron " << count << " nodos.\n";
    }

    Pausa();


    // FASE 2: MOVIMIENTO A LA PAPELERA (rm)
    cout << "\n[2] Moviendo el arbol a la papelera...\n";
    startTime = Utils::getCurrentTimeMs();

    fs.rm("/test"); // Mueve toda la carpeta raiz de la prueba
    endTime = Utils::getCurrentTimeMs();
    Guardar(fs);

    cout << "\nTiempo de Eliminacion (RM): " << (endTime - startTime) << " ms\n";
    Pausa();

    // FASE 3: ELIMINACIÓN PERMANENTE (emptyTrash)
    cout << "\n[3] Eliminando permanentemente la papelera...";
    startTime = Utils::getCurrentTimeMs();

    fs.emptyTrash(); // Elimina PERMANENTEMENTE a la velocidad de O(L)
    endTime = Utils::getCurrentTimeMs();
    Guardar(fs);

    cout << "\nTiempo de Vaciado (CLB): " << (endTime - startTime) << " ms\n";

    cout << "\n======================================================\n";
    cout << "\t\tPRUEBA FINALIZADA\n";
    cout <<   "======================================================\n";
}

void Help(auto& fs) {
    system("cls");
    cout << "\n==================================== SINTAXIS DE COMANDOS ====================================\n\n";
    cout << "Todos los comandos deben separar sus argumentos por espacios.\n\n";

    cout << " [MKDIR]  'mkdir [RUTA_PADRE] [NOMBRE]'\t\tCrea una nueva carpeta.\n";
    cout << " [TOUCH]  'touch [RUTA_PADRE] [NOMBRE]'\t\tCrea un nuevo archivo.\n";
    cout << " [RN]     'rn [RUTA] [NUEVO_NOMBRE]'\t\tRenombra un archivo o carpeta.\n";
    cout << " [MV]     'mv [RUTA_ORIGEN] [RUTA_DESTINO]'\tMueve un elemento a un nuevo padre.\n";
    cout << " [RM]     'rm [RUTA]'\t\t\t\tElimina un elemento (mueve a papelera).\n";
    cout << " [SAVE]   'save'\t\t\t\tGuarda el sistema de archivos a JSON.\n\n";

    cout << " [SR]     'sr [PREFIJO/RUTA]'\t\t\tBusca nodos que coincidan con el prefijo.\n";
    cout << " [PRD]    'prd'\t\t\t\tMuestra el árbol completo en preorden.\n";
    cout << " [FR]     'fr [ID]'\t\t\t\tMuestra la ruta completa de un nodo por ID.\n";
    cout << " [LS]     'ls [RUTA]'\t\t\t\tLista los hijos directos de una carpeta.\n";
    cout << " [CN]     'cn [RUTA]'\t\tCuenta nodos desde una ruta como raíz.\n\n";

    cout << " [CKB]    'ckb'\t\t\t\tLista elementos en la papelera.\n";
    cout << " [RS]     'rs [ID]'\t\t\t\tRestaura un elemento de la papelera por ID.\n";
    cout << " [DLB]    'dlb [ID]'\t\t\t\tElimina permanentemente un elemento por ID.\n";
    cout << " [CLB]    'clb'\t\t\t\tVacía permanentemente la papelera.\n\n";

    cout << " [TEST]   'test'\t\t\t\tInicia las pruebas de rendimiento.\n\n";

    cout << " [HELP]   'help'\t\t\t\tMuestra esta ayuda.\n";
    cout << " [EXIT]   'exit'\t\t\t\tCierra el programa.\n\n";
    cout << "==============================================================================================\n";
}

/*---------------
    VISUALES
---------------*/
void MenuSelect() {
    system("cls");
    cout << "\n====================== MENU ======================\n\n";
    cout <<   "[MKDIR] Crear carpeta\t[TOUCH] Crear archivo\n";
    cout <<   "[RN] Renombrar\t\t[MV] Mover\n";
    cout <<   "[RM] Eliminar\t\t[SAVE] Guardar\n";
    cout <<   "\n";
    cout <<   "[SR] Buscar\t\t[PRD] Preorden\n";
    cout <<   "[FR] Ruta Completa\t[LS] Ver Hijos\n";
    cout <<   "[CN] Cuenta Nodos\n";
    cout <<   "\n";
    cout <<   "[RS] Restaurar\t\t[DLB] Vaciar Elemento\n";
    cout <<   "[CKB] Ver Papelera\t[CLB] Vaciar Papelera\n";
    cout <<   "\n";
    cout <<   "[TEST] Inicia Pruebas\n";
    cout <<   "\n\n";
    cout <<   "[HELP] Ayuda\t\t[EXIT] Salir\n";
    cout << "\n==================================================\n\n";
}

/*===========================
            MAIN
===========================*/

int main() {
    system("chcp 65001"); // Caracteres especiales UTF-8
    system("cls");

    FileSystemTree fs;
    fs.load("filesystem.json"); // Carga el Arbol desde la memoria
    Pausa();

    string Command;
    string Option;

    do {
        system("color 07");
        MenuSelect();

        cout << " [" << UserName << "]: ";
        // Lee la línea completa
        getline(cin, Command);
        cout << "\n";
        // Usa un stringstream para dividir en trozos
        stringstream ss(Command);
        ss >> Option; // Extrae el primer token (MKDIR, TOUCH, etc.)
        Utils::Mayus(Option);

             if (Option == "MKDIR") {Mkdir(fs,ss);}
        else if (Option == "TOUCH") {Touch(fs,ss);}
        else if (Option == "RN") {Renombrar(fs,ss);}
        else if (Option == "MV") {Mover(fs,ss);}
        else if (Option == "RM") {Eliminar(fs,ss);}
        else if (Option == "CKB") {fs.lsTrash();}
        else if (Option == "CN") {Contar(fs,ss);}
        else if (Option == "RS") {Restore(fs,ss);}
        else if (Option == "LS") {Ls(fs,ss);}
        else if (Option == "FR") {FullRute(fs,ss);}
        else if (Option == "PRD") {fs.printPreorder();}
        else if (Option == "DLB") {DelID(fs,ss);}
        else if (Option == "CLB") {Empty(fs);}
        else if (Option == "SAVE") {Guardar(fs);}
        else if (Option == "SR") {Search(fs,ss);}
        else if (Option == "HELP") {Help(fs);}
        else if (Option == "TEST") {Test(fs,ss);}
        else if (Option == "EXIT") {cout << " [SYNE]: Adiós, " << UserName << "...\n";}
        else {cout << "\nERROR! - Usa HELP para obetner la lista de comandos.\n";}

        if (Option != "EXIT") {Pausa();}

    } while (Option != "EXIT");
    return 0;
}
