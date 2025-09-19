# include <iostream>
using namespace std;

int main() {
    int arr[] = {10,4,20,8,30,15,40};
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
return 0;
}