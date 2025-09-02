#include <iostream>
using namespace std; // Para evitar escribir std:: cada vez.
 
int main() {
    short arr[] = {6,7,8,9,10};
    cout << "El arreglo contiene: " << endl;
    for (short i = 0; i < 5; i++) {
        cout << arr[i] << endl;
    } 
    cout << "El cuarto elemento de la matriz (del 0 al 4) es: "; cout << arr[3]; 
    return 0; // Indica que el programa terminó correctamente.
}
