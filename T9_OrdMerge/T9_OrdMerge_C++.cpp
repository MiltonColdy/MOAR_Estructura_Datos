#include <iostream>
#include <vector>
using namespace std;
void merge(vector<int>& a, int l, int m, int r) {
    int a1 = m - l + 1;
    int a2 = r - m;
    vector<int> L(a1), R(a2);
    for (int j = 0; j < a1; j++)
        L[j] = a[l + j];
    for (int k = 0; k < a2; k++)
        R[k] = a[m + 1 + k];
    int i = 0, j = 0, k = l;
    while (i < a1 && j < a2) {
        if (L[i] <= R[j]) {
            a[k] = L[i];
            i++;
        } else {
            a[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < a1) {
        a[k++] = L[i++];
    }
    while (j < a2) {
        a[k++] = R[j++];
    }
}
void mergeSort(vector<int>& a, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(a, l, m);
        mergeSort(a, m + 1, r);
        merge(a, l, m, r);
    }
}
int main() {
    vector<int> a = {39, 28, 44, 11};
    cout << "Arreglo original:\n";
    for (int x : a) cout << x << " ";

    mergeSort(a, 0, a.size() - 1);

    cout << "\nArreglo ordenado:\n";
    for (int x : a) cout << x << " ";
    return 0;
}