#include <iostream>
#include <windows.h>
#include <conio.h>
#include <thread>
#include <chrono>
#include <random>
using namespace std;
//Definición del nodo para la lista enlazada.
struct SnakeSegment {
    int x, y; // Coordinates of the segment
    struct SnakeSegment* next; // Pointer to the next segment in the snake's body
};
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dist(0, 24);
int num1 = dist(gen);
int num2 = dist(gen);
int num3 = dist(gen);
int num4 = dist(gen);
string ola;
int level = 0;
int points = 0;
int bodyparts = 5;
bool lose = false;
bool win = true;
bool vertical = false;
bool horizontal = true;
short movement = -1;
char key;
struct SnakeSegment *head; //Esta es la variable global que apunta al primer nodo de la lista.
string tablero[25][25];
float speed = 125;
void hideCursor() {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 1;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(out, &info);
}

void moveCursorToTop() {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {0, 0};
    SetConsoleCursorPosition(out, pos);
}
void randomizeApple() {
    num1 = dist(gen);
    num2 = dist(gen);
    tablero[num1][num2] = "A";
}
void randomizeTrap() {
    num3 = dist(gen);
    num4 = dist(gen);
    tablero[num3][num4] = "T";
}
void growSize() {
    SnakeSegment *nuevo = new SnakeSegment;
    if (vertical) {
        nuevo->y = head->y+movement;
        nuevo->x = head->x;
    } else {
        nuevo->y = head->y;
        nuevo->x = head->x+movement;
    }
    // --- AQUI EL FIX ---
    if (nuevo->x < 0) nuevo->x = 24;
    else if (nuevo->x > 24) nuevo->x = 0;

    if (nuevo->y < 0) nuevo->y = 24;
    else if (nuevo->y > 24) nuevo->y = 0;

    nuevo->next = head;
    head = nuevo;
}

void takeDamage() {

    for (int i = 0; i < 2; i++) {

        if (head == nullptr || head->next == nullptr)
            return;

        SnakeSegment *prev = head;
        SnakeSegment *curr = head->next;

        while (curr->next != nullptr) {
            prev = curr;
            curr = curr->next;
        }

        prev->next = nullptr;
        delete curr;
    }

}
void clearSnake() {
    // Borrar toda la serpiente
    SnakeSegment* temp = head;
    while (temp != nullptr) {
        SnakeSegment* next = temp->next;
        delete temp;
        temp = next;
    }
    head = nullptr;
    horizontal = true;
    vertical = false;
    movement = -1;
    // Reiniciar contador de partes
    bodyparts = 5;

    // Crear nueva serpiente igual que al inicio
    for (int i = 0; i < 5; i++) {
        SnakeSegment *nuevo = new SnakeSegment;
        nuevo->x = 23 - i;
        nuevo->y = 1;
        nuevo->next = head;
        head = nuevo;
    }
}
int main() {
    hideCursor();
    cout << "Estas son las reglas:\n-No choques contigo.\n";
    cout <<"-COMIDA = " << char(224) << endl;
    cout <<"-TRAMPA = " << char(227) << endl;
    cout <<"\nSi usted se\nencuentra listo/a...\n\nPulse enter para comenzar\n";
    getline(cin, ola);
    while (true) {
        if (win) {
        speed = speed/1.1;
        level++;
        if (level > 1) {
            points+= 1000;
        }
        for (int i = 0; i < 5; i++) {
        SnakeSegment *nuevo = new SnakeSegment;
        nuevo->x = 23-i;
        nuevo->y = 1;
        nuevo->next = head;
        head = nuevo;
        }
        clearSnake();
        randomizeApple();
        randomizeTrap();

        win = false;
        }

        SnakeSegment* temp = head;
        int prevX = temp->x;
        int prevY = temp->y;

        // Mover la cabeza
        if (horizontal) {
            temp->x += movement;
        } else {
            temp->y += movement;
        }
    if (temp->x < 0) temp->x = 24;
            else if (temp->x > 24) temp->x = 0;

    // Wrap vertical
    if (temp->y < 0) temp->y = 24;
        else if (temp->y > 24) temp->y = 0;
        // Mover el resto del cuerpo
        temp = temp->next;
        while (temp != nullptr) {
            int currentX = temp->x;
            int currentY = temp->y;

            temp->x = prevX;
            temp->y = prevY;

            prevX = currentX;
            prevY = currentY;

            temp = temp->next;
        }
        moveCursorToTop();
        cout << "LEVEL " << level << " SIZE: " << bodyparts << " | SCORE: " << points << endl;
        for (int y = 0; y < sizeof(tablero)/sizeof(tablero[0]); y++) {
            for (int x = 0; x < sizeof(tablero[0])/sizeof(tablero[0][0]); x++) {
                tablero[x][y] = "-";
            }
        }
        temp = head;
        while (temp != nullptr) {
            tablero[temp->x][temp->y] = char(254); //■
            tablero[num1][num2] = char(224); //Ó
            tablero[num3][num4] = char(227);

            if (head->x == num1 && head->y == num2) {
                growSize();
                points += 10;
                if (bodyparts >= 14) {

                    win = true;
                } else {
                    bodyparts++;
                    randomizeApple();
                    randomizeTrap();
                }
            }
            if (head->x == num3 && head->y == num4) {
                takeDamage();
                if (points > 0) {
                    points -= 10;
                }
                bodyparts -= 2;
                if (bodyparts <= 1) {
                    lose = true;
                }
                randomizeApple();
                randomizeTrap();
            }
            // choque contra cuerpo
            if (head != temp) {
                if (head->x == temp->x && head->y == temp->y) {
                        lose = true;
                }
            }
            temp = temp->next;
            tablero[head->x][head->y] = char(254);

        }
        for (int y = 0; y < sizeof(tablero)/sizeof(tablero[0]); y++) {
            for (int x = 0; x < sizeof(tablero[0])/sizeof(tablero[0][0]); x++) {
                cout << tablero[x][y];
            }
            cout << "\n";
        }
        if (_kbhit()) {        // ¿hay una tecla presionada?
                key = _getch();  // la lee sin necesidad de Enter
                if (key == 'd' && !horizontal) {
                    vertical = false;
                    horizontal = true;
                    movement = 1;
                }  else if (key == 'a' && !horizontal){
                    vertical = false;
                    horizontal = true;
                    movement = -1;
                } else if (key == 's' && !vertical){
                    vertical = true;
                    horizontal = false;
                    movement = 1;
                } else if (key == 'w' && !vertical){
                    vertical = true;
                    horizontal = false;
                    movement = -1;
                }

            }
            if (lose) break;
        Sleep(speed);
    }

    return 0;
}
