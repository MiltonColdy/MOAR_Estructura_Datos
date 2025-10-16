#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int main() {
    cout << "ORDENAMIENTO DE SUBARREGLOS 3D \n";
    int arr[5][5][5];
    srand(time(0));
    cout << "Arreglo original: " << endl;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << "[ ";
            for (int k = 0; k < 5; k++) {
                arr[i][j][k] = rand() % 100;
                cout << arr[i][j][k] << " ";
            }
            cout << "]" << endl;
        }
        cout << "------------------------" << endl;
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 4; k++) {
                for (int m = k + 1; m < 5; m++) {
                    if (arr[i][j][k] > arr[i][j][m]) {
                        int tmp = arr[i][j][k];
                        arr[i][j][k] = arr[i][j][m];
                        arr[i][j][m] = tmp;
                    }
                }
            }
        }
    }
    cout << "\nArreglo ordenado (cada subarreglo de 5 elementos): " << endl;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << "[ ";
            for (int k = 0; k < 5; k++) {
                cout << arr[i][j][k] << " ";
            }
            cout << "]" << endl;
        }
        cout << "------------------------" << endl;
    }
    return 0;
}
