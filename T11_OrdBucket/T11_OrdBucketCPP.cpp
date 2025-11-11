#include <iostream>
#include <algorithm>
using namespace std;

void insertionSort(double arr[], int n) {
    for (int i = 1; i < n; i++) {
        double key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void bucketSort(double arr[], int n, int bucketCount) {
    if (n <= 1) return;

    double minVal = arr[0], maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < minVal) minVal = arr[i];
        if (arr[i] > maxVal) maxVal = arr[i];
    }
    if (minVal == maxVal) return;

    // buckets
    const int MAX_BUCKET_SIZE = 100; // tamaño máximo por bucket
    double buckets[100][MAX_BUCKET_SIZE];
    int bucketSizes[100] = {0};

    double range = maxVal - minVal;
    for (int i = 0; i < n; i++) {
        int index = int(((arr[i] - minVal) / range) * (bucketCount - 1));
        int pos = bucketSizes[index]++;
        buckets[index][pos] = arr[i];
    }

    int k = 0;
    for (int i = 0; i < bucketCount; i++) {
        if (bucketSizes[i] > 0) {
            insertionSort(buckets[i], bucketSizes[i]);
            for (int j = 0; j < bucketSizes[i]; j++) {
                arr[k++] = buckets[i][j];
            }
        }
    }
}

int main() {
    double data[] = {0.42, 0.32, 0.23, 0.52, 0.25, 0.47, 0.51};
    int n = sizeof(data) / sizeof(data[0]);

    bucketSort(data, n, 5);

    for (int i = 0; i < n; i++) cout << data[i] << " ";
    cout << endl;
}