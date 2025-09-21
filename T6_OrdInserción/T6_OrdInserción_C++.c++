# include <iostream>
using namespace std;

int main() {
    int arr[] = {10,5,20,35,25,45,50};
    int temp, j;
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << "Arreglo original: ";
     for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
     }
    
    for (int i = 0; i < n; i++) {
        temp = arr[i];
        j = i-1;

        while (j>=0 and temp < arr[j]) {
            arr[j+1] = arr[j];
            j -= 1;
        }
        arr[j + 1] = temp;
    }
    cout << "\nArreglo ordenado: ";
     for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
     }
}