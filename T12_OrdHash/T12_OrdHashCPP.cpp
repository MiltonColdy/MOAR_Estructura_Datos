#include <iostream>
#include <cmath>
using namespace std;

void hashSort(int arr[], int n, int maxVal) {
    const int EMPTY = -1;
    int hashTable[1000];  // tamaño máximo permitido
    int size = maxVal + 1;

    // inicializar en -1 (vacío)
    for (int i = 0; i < size; i++) hashTable[i] = EMPTY;

    // insertar con sondeo lineal
    for (int i = 0; i < n; i++) {
        int key = arr[i];
        int index = key % size;
        while (hashTable[index] != EMPTY)
            index = (index + 1) % size;
        hashTable[index] = key;
    }

    // reconstruir arreglo ordenado
    int k = 0;
    for (int i = 0; i < size; i++) {
        if (hashTable[i] != EMPTY)
            arr[k++] = hashTable[i];
    }
}

int main() {
    int arr[] = {15, 3, 9, 20, 12, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int maxVal = 20;

    hashSort(arr, n, maxVal);

    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
}