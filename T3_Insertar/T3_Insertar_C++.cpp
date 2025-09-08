#include <iostream>

using namespace std;

int main ()
{
    int numeros[]  = {4,5,6,1,2,3,7,8,9};
    int tam = sizeof(numeros) / sizeof(numeros[0]);
    int val = 9;
    int pos = 0;

    cout << "Arreglo antes de la inserción:   ";
    for (int i = 0; i < tam; i++) {
        cout << numeros[i] << " ";
    }
    cout << endl;

    for (int i = tam - 1; i > pos ; i--) 
    {
            numeros[i] = numeros[i-1];
    }   
    numeros[pos] = val;
cout << "---------------------------------------------------" << endl;
    cout << "Arreglo después de la inserción: ";
    for (int i = 0; i < tam; i++) {
        cout << numeros[i] << " ";
    }
    cout << endl;

    return 0;
}