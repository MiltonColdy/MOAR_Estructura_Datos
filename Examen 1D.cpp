#include <iostream>

using namespace std;
void swap(int a[], int j, int k) {
    int temp = a[j];
    a[j] = a[k];
    a[k] = temp;
}
int main()
{

    cout << "| 1D, ORDENAR Y BUSCAR |" << endl;
    cout << "-------------------------" << endl;
    int arr[] = {50,25,45,70,80,15,5,20,30,10};
    int temp;
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << "Arreglo original: ";
        for (int i = 0; i < n; i++) {
            cout << arr[i] << " ";
        }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
            temp = arr[j];
            arr[j] = arr[j+1];
            arr[j + 1] = temp;
            }
        }
    }
    cout << "\n";
    cout << "Arreglo ordenado: ";
    for (int i = 0; i < n; i++) {
            cout << arr[i] << " ";
        }
    int b = 25, t = 0;
    cout << "\n-----------------------------------------\nVamos a buscar el numero " << b << " en el arreglo ordenado\n";
    for (int i = 0; i < n; i++) {
       if (b == arr[i]) {
        temp = i;
        cout << "El numero " << b << " fue encontrado en el indice : " << i << "\n";
       }
    }

    return 0;
}
