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
#include "json.hpp"

// SIMPLIFICACIONES DE ESCRITURA
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

    // Función auxiliar para buscar IDs en un subárbol
    void findIDsByPrefix(TrieNode* node, vector<int>& results) {
        if (!node) return;

        // 1. Si este nodo marca el final de una ruta, guarda su ID.
        if (node->isEndOfWord && node->fileSystemNodeID != -1) {
            results.push_back(node->fileSystemNodeID);
        }

        // 2. Continúa buscando en todos los hijos recursivamente.
        for (auto const& [key, child] : node->children) {
            findIDsByPrefix(child, results);
        }
    }

public:
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        delete root;
    }

    // Insertar una ruta completa
    void insert(const string& path, int nodeID) {
        TrieNode* current = root;
        // La ruta 'S:' debe ser tratada como un caso especial si es necesario,
        // pero para simplificar, usaremos la ruta completa.
        string normalizedPath = path;

        // Si la ruta comienza con la raíz "S:", la omitimos para una mejor indexación.
        // Opcionalmente, puedes indexar la ruta completa. Aquí indexamos la parte
        // posterior a la raíz (ej: "Users/Data.txt")
        if (normalizedPath.rfind(rootname, 0) == 0) {
            normalizedPath = normalizedPath.substr(rootname.length());
        }
        if (normalizedPath.empty()) {
            // Caso especial: la raíz misma.
            current->fileSystemNodeID = nodeID;
            current->isEndOfWord = true;
            return;
        }

        // Iteramos sobre cada carácter de la ruta normalizada (ej: "/Users/Data.txt")
        for (char ch : normalizedPath) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = new TrieNode();
            }
            current = current->children[ch];
        }

        // Marcar el final de la ruta y almacenar el ID.
        current->isEndOfWord = true;
        current->fileSystemNodeID = nodeID;
    }

    // Función principal para autocompletar/buscar por prefijo
    vector<int> autocomplete(const string& prefix) {
        TrieNode* current = root;
        vector<int> foundIDs;
        string normalizedPrefix = prefix;

        // Si el prefijo comienza con la raíz, la omitimos (igual que en insert)
        if (normalizedPrefix.rfind(rootname, 0) == 0) {
            normalizedPrefix = normalizedPrefix.substr(rootname.length());
        }

        // 1. Recorrer hasta el final del prefijo dado
        for (char ch : normalizedPrefix) {
            if (current->children.find(ch) == current->children.end()) {
                return {}; // No hay nodos que coincidan con este prefijo.
            }
            current = current->children[ch];
        }

        // 2. Una vez en el nodo final del prefijo, buscar todos los descendientes
        findIDsByPrefix(current, foundIDs);

        return foundIDs;
    }

    // Función para limpiar y reconstruir el Trie (útil después de mover/eliminar)
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
            delete item.node; // Libera el puntero al Node*
        }
    }
    /*------------------------------------
        BUSCAR/AUTOCOMPLETAR (por prefijo)
    ------------------------------------*/
    void search(const string& prefix) {
        // 1. Usar el Trie para obtener los IDs de todos los nodos que coinciden.
        vector<int> matchingIDs = fileTrie.autocomplete(prefix);

        if (matchingIDs.empty()) {
            cout << "\tNo se encontraron rutas que coincidan con el prefijo: '" << prefix << "'\n";
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
        cout << "\tÍndice de búsqueda (Trie) reconstruido.\n";
    }
    /*---------------------------------
        GUARDAR EL ESTADO DEL ÁRBOL
    ---------------------------------*/
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
        cout << "\tSistema de archivos (root y papelera) guardado en: " << filename << "\n";
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

    if (!file.is_open()) {
        // Si no encuentra guardado, llama al repair.
        cout << "\n===================================================================================\n\n";
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
            cout << "\n\tADVERTENCIA: Archivo JSON sin clave 'root'. Creando sistema vacío.\n";
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

        cout << "\n===================================================================\n\n";
        cout << "\tSistema cargado exitosamente desde: " << filename << "\n\n";
        cout << "\tElementos Totales del Arbol: " << nextID << "\n";
        cout << "\n===================================================================";


    } catch (const nlohmann::json::parse_error& e) {

        cout << "\n=====================================================================\n\n";
        cout << "\tERROR: El archivo JSON esta corrupto o mal formado...\n\n"; repair();
        cout << "\n\tLa papelera está vacía.\n";
        cout << "\n=====================================================================";
    } catch (...) {

        cout << "\n=====================================================\n\n";
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
        cout << "\tCarpeta creada: " << name << "\n";
        rebuildTrie();
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
        cout << "\tArchivo creado: " << name << "\n";
        rebuildTrie();
    }


    /*----------------
        RENOMBRAR
    ----------------*/
    void renameNode(const string& path, const string& newName) {
        // 1. Validar la búsqueda
        Node* nodeToRename = findNodeByPath(path);

        if (!nodeToRename) {
            cout << "\tERROR: Ruta '" << path << "' no encontrada.\n";
            return;
        }

        // La raíz (id 0) no se puede renombrar
            if (nodeToRename == root) {
            cout << "\tERROR: No se puede renombrar la carpeta raíz (" << rootname << ").\n";
            return;
        }

        // Obtiene el nodo padre
        Node* parent = nodeToRename->parent;

        // Verifica si el nuevo nombre ya existe en el padre
        for (Node* sibling : parent->children) {
            // Compara con todos los hermanos, excepto consigo mismo (nodeToRename)
            if (sibling != nodeToRename && sibling->nombre == newName) {
                cout << "\tERROR: Ya existe un elemento llamado '" << newName << "' en el directorio padre.\n";
                return;
            }
        }

        // 2. Realizar el renombrado
        string oldName = nodeToRename->nombre;
        nodeToRename->nombre = newName;

        cout << "\tNodo renombrado: '" << oldName << "' -> '" << newName << "'\n";
        rebuildTrie();
    }

    /*---------------------
        MV (Mover Nodo)
    ---------------------*/
    void mv(const string& sourcePath, const string& destPath) {
        // 1. Encuentra el nodo a mover (origen)
        Node* sourceNode = findNodeByPath(sourcePath);
        if (!sourceNode) {
            cout << "\tERROR: Ruta de origen '" << sourcePath << "' no encontrada.\n";
            return;
        }

        // La raíz no puede ser movida
        if (sourceNode == root) {
            cout << "\tERROR: No se puede mover la carpeta raíz (" << rootname << ").\n";
            return;
        }

        // El padre del nodo a mover (necesario para la desconexión)
        Node* oldParent = sourceNode->parent;

        // 2. Encuentra el nodo destino
        Node* destParent = findNodeByPath(destPath);
        if (!destParent) {
            cout << "\tERROR: Ruta de destino '" << destPath << "' no encontrada.\n";
            return;
        }

        // Verifica que sea una carpeta
        if (destParent->tipo != "folder") {
             cout << "\tERROR: El destino '" << destPath << "' no es una carpeta.\n";
             return;
        }

        // Evita mover un nodo a sí mismo, a su padre o a uno de sus hijos
        Node* current = destParent;
        while (current != nullptr) {
            if (current == sourceNode) {
                cout << "\tERROR: No se puede mover un elemento a sí mismo o a un subdirectorio.\n";
                return;
            }
            current = current->parent;
        }

        // 3. Desconectar: Elimina el sourceNode del vector children de su padre original
        auto& children_list = oldParent->children;

        // Reordena y luego borra todos los punteros a nodos que son iguales a 'sourceNode' dentro de 'oldParent'
        children_list.erase(
            remove_if(children_list.begin(), children_list.end(),
            [sourceNode](Node* n) {return n == sourceNode;}),
            children_list.end()
        );

        // 4. Reconectar: Añade el sourceNode al nuevo padre
        sourceNode->parent = destParent;
        destParent->children.push_back(sourceNode);

        cout << "\tMovido exitosamente: '" << sourcePath << "' a '" << destPath << "'.\n";
        rebuildTrie();
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
        cout << "\tERROR: Ruta '" << path << "' no encontrada.\n";
        return;
        }

        // La raíz no debe ser eliminada
        if (nodeToRemove == root) {
            cout << "\tERROR: No se puede eliminar la carpeta raíz (" << rootname << ").\n";
            return;
        }

        Node* oldParent = nodeToRemove->parent;

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

        cout << "\tElemento '" << nodeToRemove->nombre << "' movido a la papelera.\n";
        rebuildTrie();
        //saveTrash();

        /* Milton, para quitar el autoguardado de la papelera,
           solo debes activar esta linea de arriba. Okei - Milton*/
    }

    /*-----------------------------------
        RESTORE-ID (Restaurar por ID)
    -----------------------------------*/
    void restoreID(int id) {
        // 1. Busca el elemento por ID en la papelera
        auto it = trash.begin();
        bool found = false;

        while (it != trash.end()) {
            if (it->node->id == id) {
                found = true;
                break;
            }
            ++it;
        }

        if (!found) {
            cout << "\tERROR: El ID " << id << " no existe en la papelera.\n";
            return;
        }

        // 2. Copia el elemento encontrado en bin y lo remueve despues de pegarlo
        TrashNode trashItem = *it;
        trash.erase(it);

        Node* nodeToRestore = trashItem.node;

        // Aquí busca el puntero en memoria del nodo padre usando el ID para reinsertarlo
        Node* originalParent = AuxNodeID(root, trashItem.originalParentID);

        string newName = nodeToRestore->nombre;
        string newParentRute = "";
        bool conflict = false;

        // OJO: El padre debe existir en la raíz del árbol principal
        if (!originalParent) {
            cout << "\tERROR: No se puede restaurar el elemento '" << nodeToRestore->nombre
            << "'. El padre original (ID: " << trashItem.originalParentID << ") ya no existe.\n\n";

            cout << "\tIngrese una NUEVA RUTA para restaurar el elemento (o escriba 'Exit' para cancelar): ";

                do {
                    conflict = false;

                    // Usa el nuevo PATH para encontrar un Nodo sustituto
                    cin >> newParentRute;
                    originalParent = findNodeByPath(newParentRute);

                    if (!originalParent) {
                        cout << "\n\tERROR: Ruta de restauracion '" << newParentRute << "' no encontrada.\n";
                        cout << "\t Intente otra vez (o escriba 'Exit' para cancelar): ";
                        conflict = true;
                    }

                    if (newParentRute == "Exit") {
                        trash.push_back(trashItem); // Devuelve el nodo a la papelera
                        cout << "\n\t Restauración cancelada. El elemento sigue en la papelera.\n";
                        return; // Regresa al Menú
                    }

                } while (conflict); // Repite mientras haya conflicto
            return;
        }

        if (originalParent) {
            do {
                conflict = false;

                // Asegura que el padre original no tenga un elemento con el mismo nombre
                for (Node* sibling : originalParent->children) {
                    if (sibling->nombre == newName) {
                        cout << "\tADVERTENCIA: Ya existe un elemento llamado '" << newName << "' en el directorio de destino.\n";
                        cout << "\tIngrese un NUEVO NOMBRE para restaurar el elemento (o escriba 'Exit' para cancelar): ";
                        cin >> newName;
                        conflict = true;
                        break;
                    }
                }

                if (newName == "Exit") {
                        trash.push_back(trashItem); // Devuelve el nodo a la papelera
                        cout << "\n\t Restauración cancelada. El elemento sigue en la papelera.\n";
                        return; // Regresa al Menú
                    }
                } while (conflict); // Repite mientras haya conflicto

            // Si el nombre se cambió, actualizar el nodo
            if (newName != nodeToRestore->nombre) {
                nodeToRestore->nombre = newName;
                cout << "\tElemento renombrado a '" << newName << "' durante la restauración.\n";
            }

            // Actualiza el nodo si el nombre se cambió durante el proceso
            if (newName != nodeToRestore->nombre) {
                nodeToRestore->nombre = newName;
                cout << "\tElemento renombrado a '" << newName << "' durante la restauración.\n";
            }

            // 3. Reconexión
            nodeToRestore->parent = originalParent;
            originalParent->children.push_back(nodeToRestore);

            cout << "\tElemento '" << nodeToRestore->nombre << "' restaurado exitosamente a: " << getFullPath(originalParent) << "\n";
            rebuildTrie();
            //saveTrash();
        }
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
            cout << "\tERROR: El ID " << id << " no existe en la papelera.\n";
            return;
        }

        // 2. Borrado: Libera el subárbol del nodo y elimina el TrashNode
        Node* nodeToDelete = it->node;
        string name = nodeToDelete->nombre;

        deleteNodes(nodeToDelete); // Libera recursivamente toda la memoria

        trash.erase(it); // Elimina el elemento de la lista 'trash'

        cout << "\tElemento '" << name << "' (ID: " << id << ") eliminado permanentemente.\n";

        //saveTrash();
    }

    /*-------------------------------------
        VACIAR TODA LA PAPELERA (EMPTY)
    -------------------------------------*/
    void emptyTrash() {
        if (trash.empty()) {
            cout << "\n\tLa papelera ya esta vacia.\n";
            return;
        }

        // 1. Libera la memoria de todos los nodos en la papelera
        for (const auto& item : trash) {
            deleteNodes(item.node);
        }

        // 2. Limpia el vector (los TrashNode)
        trash.clear();

        cout << "\n\tPapelera vaciada permanentemente.\n";
        rebuildTrie();
        //saveTrash();
    }

    /*--------------------------------
        LS-TRASH (Listar Papelera)
    --------------------------------*/
    void lsTrash() {
        if (trash.empty()) {
            cout << "\tLa papelera esta vacia.\n";
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

/*========================
    PROCESOS DEL MENÚ
========================*/

/*-----------
    FLUJO
-----------*/

void Mkdir(auto& fs) {
    string path, name;
    cout << "\tRuta del padre: ";
    cin >> path;
    cout << "\tNombre de la carpeta: ";
    cin >> name;
    fs.mkdir(path, name);

}

void Touch(auto& fs) {
    string path, name;
    cout << "\tRuta del padre: ";
    cin >> path;
    cout << "\tNombre del archivo: ";
    cin >> name;
    fs.touch(path, name);

}

void Renombrar(auto& fs) {
    string path, newName;
    cout << "\tRuta del nodo a renombrar: ";
    cin >> path;
    cout << "\tNuevo nombre: ";
    cin >> newName;
    fs.renameNode(path, newName);

}

void Mover(auto& fs) {
    string sourcePath, destPath;
    cout << "\tRuta de ORIGEN (a mover): ";
    cin >> sourcePath;
    cout << "\tRuta de DESTINO (padre): ";
    cin >> destPath;
    cout << "\n";
    fs.mv(sourcePath, destPath);

}

void Eliminar(auto& fs) {
    string path;
    cout << "\tRuta del nodo a ELIMINAR: ";
    cin >> path;
    fs.rm(path);
}

void Restore(auto& fs) {
    // 1. Muestra la papelera saber qué IDs están disponibles
    fs.lsTrash();

    if (!fs.isTrashEmpty()) {
        int id;
        cout << "\tIngrese el ID del elemento a restaurar (0 para cancelar): "; cin >> id;

        if (id != 0) {
            // 2. Comienza la consulta de restauración
            fs.restoreID(id);
        } else {
            cout << "\tRestauración cancelada.\n";
        }
    }

}

void Ls(auto& fs) {
    string path;
    cout << "\tRuta: ";
    cin >> path;
    fs.ls(path);
}

void FullRute(auto& fs) {
    int id;
    cout << "\tIngresa ID a Buscar: ";
    if (!(cin >> id)) { // Verificar entrada válida
        cout << "\n\tID invalido.\n";
        cin.clear(); // Validación temporal...
        return;
    }

    // 1. Encuentra el 'nodo' mediante un ID
    Node* nodo = fs.JmpAuxID(id);

    if (nodo) {
        // 2. Obtiene el string de la 'ruta' mediante el nodo obtenido
        cout << "\tRuta: " << fs.getFullPath(nodo) << "\n";
    } else {
        cout << "\n\tERROR: ID [ " << id << " ] no encontrado.\n";
    }
}

void DelID(auto& fs) {
    fs.lsTrash();
    if (fs.isTrashEmpty()) return;

    int id;
    cout << "\n\tIngrese el ID del elemento a ELIMINAR permanentemente (0 para cancelar): ";
    cin >> id;

    if (id != 0) {
        fs.delID(id);
    } else {
        cout << "\n\tBorrado cancelado.\n";
    }

}

void Empty(auto& fs) {
    if (fs.isTrashEmpty()) {
        cout << "\tLa papelera ya esta vacia.\n";
        return;
    }

    char confirm = '0';
    cout << "\tADVERTENCIA: ¿Desea vaciar PERMANENTEMENTE la papelera completa? (S/N): ";

    do {
        cin >> confirm;
        if (toupper(confirm) == 'S') {
            fs.emptyTrash();
        } else if (toupper(confirm) == 'N') {
            cout << "\n\tVaciado cancelado.\n";
        }
    } while (toupper(confirm) != 'S' && toupper(confirm) != 'N');

}

void Guardar(auto& fs) {
    string filename = "filesystem.json";
    fs.save(filename);
}

void Search(auto& fs) {
    string prefix;
    cout << "\tIngrese el prefijo (ruta/nombre) a buscar: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpia el buffer antes de leer la línea
    getline(cin, prefix);

    // 1. Llama al método de la clase FileSystemTree
    fs.search(prefix);
}

/*---------------
    VISUALES
---------------*/
void Pausa() {
    cout << "\n\n\tContinuar...";
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
}

void MenuSelect(string& Option) {
    system("cls");
    cout << "\n================= MENU =================\n\n";
    cout <<   "[MKDIR] Crear carpeta.\t[TOUCH] Crear archivo.\n";
    cout <<   "[RN] Renombrar\t\t[RM] Mover\n";
    cout <<   "[DEL] Eliminar\t\t[BCHECK] Ver Papelera\n";
    cout <<   "[RS] Restaurar.\t\t[LS] Ver Hijos.\n";
    cout <<   "[FR] Ruta Completa\t[PREORD] Preorden\n";
    cout <<   "[BDEL] Vaciar Elemento\t[BCLEAR] Vaciar Papelera\n";
    cout <<   "[SAVE] Guardar\t\t[SR] Buscar\n";

    cout <<   "[EXIT] Salir\n";
    cout << "\n========================================\n\n";
    cout <<   "\tIngresa una Opcion: "; cin >> Option;
    cout << "\n";
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

    string Option;

    do {
        MenuSelect(Option);

             if (Option == "MKDIR") {Mkdir(fs);}
        else if (Option == "TOUCH") {Touch(fs);}
        else if (Option == "RN") {Renombrar(fs);}
        else if (Option == "RM") {Mover(fs);}
        else if (Option == "DEL") {Eliminar(fs);}
        else if (Option == "BCHECK") {fs.lsTrash();}
        else if (Option == "RS") {Restore(fs);}
        else if (Option == "LS") {Ls(fs);}
        else if (Option == "FR") {FullRute(fs);}
        else if (Option == "PREORD") {fs.printPreorder();}
        else if (Option == "BDEL") {DelID(fs);}
        else if (Option == "BCLEAR") {Empty(fs);}
        else if (Option == "SAVE") {Guardar(fs);}
        else if (Option == "SR") {Search(fs);}
        else if (Option == "EXIT") {cout << "\tAdios :D\n";}
        else {cout << "\n\tOpcion invalida.\n";}

        if (Option != "EXIT") {Pausa(); cin.ignore();}

    } while (Option != "EXIT");
    return 0;
}
