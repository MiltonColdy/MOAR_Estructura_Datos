#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <windows.h>
using namespace std;

short leerC(const string & mensaje){
    short valor;
    string lin;
    do {
        cout << mensaje;
        getline(cin,lin);
        stringstream ss(lin);

        if (ss >> valor and ss.eof() and valor >= 1 and valor <= 3) {
        return valor;
        } else {
            cout << "Ingrese un número ENTERO entre 1 y 3." << endl;
        }
    } while (true);
}

int main() {
    SetConsoleOutputCP(1252);
    string gatito[3][3], fig, eq = "0";
    short columna, fila, turno = 1;
    bool ganar = false;
    cout << "Juego del Gatito." << endl;
    cout << "__________________" << endl;

    for (int fil = 0; fil <3; fil++)
        {
        for (int col = 0; col<3; col++)
            {
            gatito[fil][col] = " ";
            }
        }


    do {
    system("cls");
    for (short fil = 0; fil <3; fil++) {
        for (short col = 0; col<3; col++) {
            cout << "[" << gatito[fil][col] << "]";
        }
        cout << " " << endl;
    }
do {
    if (turno % 2 != 0) {

    fig = "X";
    cout << "¿En dónde colocará la X?"<< endl;
    } else {
    fig = "O";
    cout << "¿En dónde colocará el O?"<< endl;
    }
    fila = leerC("Fila (1-3): ");
    columna = leerC("Columna (1-3): ");

    if (gatito[fila-1][columna-1] == " ") {
        gatito[fila-1][columna-1] = fig;
        eq = "0";
    } else {
        cout << "Escoja unas coordenadas vacías." << endl;
        eq = "1";
    }
        } while (eq != "0");
    turno++;

    if (turno >= 6) {
        for (short i = 0; i < 3; i++){
        if  (gatito[0][i] == gatito[1][i] and gatito[1][i] == gatito[2][i] and gatito[0][i] != " ") {
            ganar = true;
            cout << "¡El jugador de la figura " << gatito[0][i] << " ha ganado! :" << endl;
        }
        if  (gatito[i][0] == gatito[i][1] and gatito[i][1] == gatito[i][2] and gatito[i][0] != " ") {
            ganar = true;
            cout << "¡El jugador de la figura " << gatito[i][0] << " ha ganado! :"<< endl;

                }
            }
        if  (gatito[0][0] == gatito[1][1] and gatito[1][1] == gatito[2][2] and gatito[0][0] != " ") {
            ganar = true;
            cout << "¡El jugador de la figura " << gatito[1][1] << " ha ganado! :"<< endl;
            }
        if  (gatito[0][2] == gatito[1][1] and gatito[1][1] == gatito[2][0] and gatito[0][2] != " ") {
            ganar = true;
            cout << "¡El jugador de la figura " << gatito[1][1] << " ha ganado! :"<< endl;

                }
        }
        if (ganar == true ){
    for (short fil = 0; fil <3; fil++) {
        for (short col = 0; col<3; col++) {
            cout << "[" << gatito[fil][col] << "]";
        }
        cout << " " << endl;
    }
        }
    } while (ganar == false);
}