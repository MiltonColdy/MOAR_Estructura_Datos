#include <iostream>
#include <cstdlib>
using namespace std;

struct node {
    int data;
    struct node *next;
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

    ptr = (struct node *)malloc(sizeof(struct node));

    if (ptr == NULL) {
        cout << "\nOVERFLOW";
    }
    else {
        cout << "\nIngrese valor\n";
        cin >> item;

        ptr->data = item;

        if (head == NULL) {
            head = ptr;
            ptr->next = head;    // circular
        }
        else {
            struct node* temp = head;

            while (temp->next != head) {
                temp = temp->next;
            }

            ptr->next = head;
            head = ptr;
            temp->next = head;   // apuntar al nuevo head
        }

        cout << "\nNodo insertado";
    }
}

void lastinsert() {
    struct node *ptr, *temp;
    int item;

    ptr = (struct node *)malloc(sizeof(struct node));

    if (ptr == NULL) {
        cout << "\nOVERFLOW";
    }
    else {
        cout << "\nIngrese valor:\n";
        cin >> item;
        ptr->data = item;

        if (head == NULL) {
            head = ptr;
            ptr->next = head;  // circular
        }
        else {
            temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = ptr;
            ptr->next = head;  // circular
        }

        cout << "\nNodo insertado";
    }
}

void randominsert() {
    int i, loc, item;
    struct node *ptr, *temp;

    ptr = (struct node *)malloc(sizeof(struct node));
    if (ptr == NULL) {
        cout << "\nOVERFLOW";
        return;
    }

    cout << "\nIntroduzca el valor del elemento";
    cin >> item;
    ptr->data = item;

    cout << "\nIntroduce la ubicación después de la cual deseas insertar ";
    cin >> loc;

    temp = head;

    for (i = 0; i < loc; i++) {
        temp = temp->next;

        if (temp == head) {
            cout << "\nNo se puede insertar\n";
            return;
        }
    }

    ptr->next = temp->next;
    temp->next = ptr;

    cout << "\nNodo insertado";
}

void begdelete() {
    struct node *ptr;

    if (head == NULL) {
        cout << "\nLa lista está vacía\n";
        return;
    }

    // caso de nodo único
    if (head->next == head) {
        delete head;
        head = NULL;
        cout << "\nNodo eliminado desde el principio...\n";
        return;
    }

    struct node *last = head;

    while (last->next != head) {
        last = last->next;
    }

    ptr = head;
    head = head->next;

    last->next = head;  // cerrar círculo

    delete ptr;

    cout << "\nNodo eliminado desde el principio...\n";
}

void lastdelete() {
    struct node *ptr, *ptr1;

    if (head == NULL) {
        cout << "\nLa lista está vacía";
        return;
    }

    // solo un nodo
    if (head->next == head) {
        delete head;
        head = NULL;
        cout << "\nSolo se eliminó un nodo de la lista...\n";
        return;
    }

    ptr = head;

    while (ptr->next != head) {
        ptr1 = ptr;
        ptr = ptr->next;
    }

    ptr1->next = head;
    delete ptr;

    cout << "\nNodo eliminado del último...\n";
}

void randelete() {
    struct node *ptr, *ptr1;
    int loc, i;

    cout << "\nIntroduzca la ubicación del nodo después del cual desea realizar la eliminación. \n";
    cin >> loc;

    if (head == NULL) {
        cout << "\nLista vacía";
        return;
    }

    ptr = head;

    for (i = 0; i < loc; i++) {
        ptr1 = ptr;
        ptr = ptr->next;

        if (ptr == head) {
            cout << "\nNo se puede eliminar";
            return;
        }
    }

    ptr1->next = ptr->next;
    delete ptr;

    cout << "\nNodo eliminado " << loc + 1;
}

void search() {
    struct node *ptr;
    int item;
    int i = 0;
    int flag = 1;

    if (head == NULL) {
        cout << "\nLista vacía\n";
        return;
    }

    cout << "\nIntroduce el elemento que deseas buscar:\n";
    cin >> item;

    ptr = head;

    do {
        if (ptr->data == item) {
            cout << "Elemento encontrado en la ubicación " << i + 1;
            flag = 0;
        }
        ptr = ptr->next;
        i++;
    } while (ptr != head);

    if (flag == 1) {
        cout << "Elemento no encontrado\n";
    }
}

void display() {
    struct node *ptr;
    ptr = head;

    if (ptr == NULL) {
        cout << "Nada que imprimir";
    }
    else {
        cout << "\nImprimiendo valores...\n";
        do {
            cout << "\n" << ptr->data;
            ptr = ptr->next;
        } while (ptr != head);
    }
}