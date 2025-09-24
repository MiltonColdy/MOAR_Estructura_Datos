# include <iostream>
using namespace std;

int main() {
    int arr[] = {10,30,5,25,35,50,45};
    int min, temp;
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << "Arreglo original: \n";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    for (int i = 0; i < n; i++) {
        min = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[min] > arr [j]) {
                min = j;
            }
        temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
        
        }
    }
    cout << "\n";
    cout << "Arreglo ordenado: \n";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
}