#include <iostream>
#include <string>
using namespace std;

class Alumnos {

public:
    string nombre1;
    string nombre2;
    string apell1;
    string apell2;
    short edad;

public:
 Alumnos(string nom1, string nom2,string ap1,string ap2, short ed) {
    nombre1 = nom1;
    nombre2 = nom2;
    apell1 = ap1; 
    apell2 = ap2;
    edad = ed;
    }
    
};

int main() {
Alumnos Estudiantes[] = {
    Alumnos("Milton","Omar","Apodaca","Romero",19), 
    Alumnos("Flérida","Romina","Alcaraz","Pérez",19),
    Alumnos("Ximena","","López","Medina",19),
    Alumnos("Jesús","Alfredo","Rodríguez","Quiros",19)
};

for (short i = 0; i < 4; i++) {
    if (Estudiantes[i].nombre2 == "") {
        cout << Estudiantes[i].nombre1 +" "+ Estudiantes[i].apell1 + " "+ Estudiantes[i].apell2 << "\n";
    } else {
        cout << Estudiantes[i].nombre1 +" "+ Estudiantes[i].nombre2 +" "+ Estudiantes[i].apell1 + " "+ Estudiantes[i].apell2 << "\n";
    }

}
    return 0;
}
