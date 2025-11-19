#include <iostream>
#include <cstdlib>
using namespace std;

struct node {
    int data;
    struct node *next;
    struct node *prev;
};

struct node* head;

void beginsert();
void lastinsert();
void randominsert();
void begdelete();
void lastdelete();
void randelete();
void display();
void search();

int main() {
    int choice = 0;
    while (choice != 9) {
        cout << "\n\n******MENÚ PRINCIPAL******\n";
        cout << "\nELIGE UNA OPCIÓN DE LA SIGUIENTE LISTA...\n";
        cout << "\n===========================================\n";

        cout << "\n1. Insertar al principio\n2. Insertar al final\n3. Insertar\n4. Eliminar del principio\n"
        << "5. Eliminar desde el último\n6. Eliminar nodo después de la ubicación especificada\n7. Buscar un elemento\n8. Mostrar\n9. Salir";
        cout << "\nIngrese su opción:\n";
        cin >> choice;
        switch (choice)
        {
            case 1: beginsert();
                    break;
            case 2: lastinsert();
                    break;
            case 3: randominsert();
                    break;
            case 4: begdelete();
                    break;
            case 5: lastdelete();
                    break;
            case 6: randominsert();
                    break;
            case 7: randelete();
                    break;
            case 8: display();
                    break;
            case 9: exit(0);
                    break;
            default:cout << "Introduzca una opción válida...";
        }
    }
    return 0;
}

void beginsert() {
    struct node *ptr;
    int item;

    ptr = (struct node *)malloc(sizeof(struct node*));

    if (ptr == NULL) {
        cout << "\nOVERFLOW";
    }
    else {
        cout << "\nIngrese valor\n";
        cin >> item;

        ptr -> data = item;
        ptr -> next = head;
        ptr -> prev = nullptr;
        if (head != nullptr) {
            head->prev = ptr;  // ← conectar hacia atrás
        }
        head = ptr;
        cout << "\nNodo insertado";
    }
}

void lastinsert() {
    node *ptr = new node;
    cout << "Ingrese valor: ";
    cin >> ptr->data;
    ptr->next = nullptr;

    if (head == nullptr) {
        ptr->prev = nullptr;
        head = ptr;
        return;
    }

    node *temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }

    temp->next = ptr;
    ptr->prev = temp;  // ← nuevo enlace hacia atrás
}

void randominsert() {
    int loc, item;
    cout << "Valor: ";
    cin >> item;

    node *ptr = new node;
    ptr->data = item;

    cout << "Ubicación: ";
    cin >> loc;

    node *temp = head;
    for (int i = 0; i < loc; i++) {
        temp = temp->next;
        if (temp == nullptr) {
            cout << "No se puede insertar\n";
            return;
        }
    }

    ptr->next = temp->next;
    ptr->prev = temp;

    if (temp->next != nullptr)
        temp->next->prev = ptr;

    temp->next = ptr;
}

void begdelete() {
    if (!head) {
        cout << "Lista vacía\n";
        return;
    }

    node *ptr = head;
    head = head->next;

    if (head)
        head->prev = nullptr;

    delete ptr;
    cout << "Nodo eliminado desde el principio\n";
}
void lastdelete() {
    if (!head) {
        cout << "Lista vacía\n";
        return;
    }
    if (!head->next) {
        delete head;
        head = nullptr;
        return;
    }

    node *temp = head;
    while (temp->next != nullptr)
        temp = temp->next;

    temp->prev->next = nullptr;  
    delete temp;
}


void randelete() {
    int loc;
    cout << "Ubicación: ";
    cin >> loc;

    node *ptr = head;

    for (int i = 0; i < loc; i++) {
        ptr = ptr->next;
        if (!ptr) {
            cout << "No se puede eliminar\n";
            return;
        }
    }

    if (ptr->prev)
        ptr->prev->next = ptr->next;

    if (ptr->next)
        ptr->next->prev = ptr->prev;

    delete ptr;
}
void search() {
    struct node *ptr;
    int item;
    int i = 0;
    int flag;
    ptr = head;
    if (ptr == NULL) {
        cout << "\nLista vacía\n";
    } else {
        cout << "\nIntroduce el elemento que deseas buscar:\n"; cin >> item;
        while (ptr != NULL) {
            if (ptr ->data == item) {
                cout << "Elemento encontrado en la ubicación " << i + 1;
                flag = 0;
            } else {
                flag = 1;
            }
            i++;
            ptr = ptr->next;
        }
        if (flag == 1) {
            cout << "Elemento no encontrado\n";
        }
    }
}

void display () {
    struct node *ptr;
    ptr = head;

    if (ptr == NULL) {
        cout << "Nada que imprimir";
    } else {
        cout << "\nImprimiendo valores...\n";
        while (ptr!= NULL) {
            cout << "\n" << ptr->data;
            ptr = ptr->next;
        }
    }
}