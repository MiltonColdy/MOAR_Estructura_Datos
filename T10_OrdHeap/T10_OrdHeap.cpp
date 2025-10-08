#include <iostream>
using namespace std;

void heap(int arr[], int n, int i) 
{
    while (true) 
    {
        int max = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;

       if (l < n && arr[l] > arr[max]) max = l;
       if (r < n && arr[r] > arr[max]) max = r;

        if (max != i) {
            swap(arr[i], arr[max]);
            i = max;
        } else break;
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heap(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heap(arr, i, 0);
    }
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    heapSort(arr, n);

    cout << "Arreglo ordenado: [ ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << "]\n";

    return 0;
}