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

    ptr = (struct node *)malloc(sizeof(struct node*));

    if (ptr == NULL) {
        cout << "\nOVERFLOW";
    }
    else {
        cout << "\nIngrese valor\n";
        cin >> item;

        ptr -> data = item;
        ptr -> next = head;
        head = ptr;
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
        cout << "\nIngrese valor:\n"; cin >> item;
        ptr->data = item;

        if (head == NULL) {
            ptr->next = NULL;
            head = ptr;
            cout << "\nNodo insertado";
        } else {
            temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = ptr;
            ptr->next = NULL;
            cout << "\nNodo insertado";
        }
    }
}

void randominsert() {
    int i, loc, item;
    struct node *ptr, *temp;
    ptr = (struct node *)malloc(sizeof(struct node));
    if (ptr = NULL) {
        cout << "\nOVERFLOW";
    } else {
        cout << "\nIntroduzca el valor del elemento";
        cin >> item;
        ptr->data = item;

        cout << "\nIntroduce la ubicación después de la cual deseas insertar "; cin >> loc;
        temp = head;

        for (int i = 0; i < loc; i++) {
            temp = temp -> next;
            if (temp == NULL) {
                cout << "\nNo se puede insertar\n";
                return;
            }    
        }
        ptr -> next = temp -> next;
        temp -> next = ptr;
        cout << "\nNodo insertado";
    }
}

void begdelete() {
    struct node *ptr;

    if (head == NULL) {
        cout << "\nLa lista está vacía\n";
    } else {
        ptr = head;
        head = ptr -> next;
        delete ptr;
        cout << "\nNodo eliminado desde el principio...\n";
    }
}
void lastdelete() {
    struct node *ptr, *ptr1;

    if (head ==NULL) {
        cout << "\nLa lista está vacía";
    } else if (head->next == NULL) {
        delete head;
        head = NULL;
        cout << "\nSolo se eliminó un nodo de la lista...\n";
    } else {
        ptr = head;
        while (ptr->next != NULL) {
            ptr1 = ptr;
            ptr = ptr->next;
        }
        ptr1->next = NULL;
        delete ptr;
        cout << "\nNodo eliminado del último...\n";
    }
}

void randelete(){
    struct node *ptr, *ptr1;
    int loc, i;

    cout << "\nIntroduzca la ubicación del nodo después del cual desea realizar la eiliminación. \n";
    cin >> loc;

    ptr = head;

    for (i = 0; i < loc; i++) {
        ptr1 = ptr;
        ptr = ptr -> next;

        if (ptr == NULL) {
            cout << "\nNo se puede eliminar";
            return;
        }
    }
    ptr1 -> next = ptr -> next;
    delete ptr;
    cout << "\nNodo eliminado " << loc + 1;
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