#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void insertionSort(vector<float>& bukt) {
    for (int j = 1; j < bukt.size(); j++) {
        float val = bukt[j];
        int k = j - 1;
        while (k >= 0 && bukt[k] > val) {
            bukt[k + 1] = bukt[k];
            k--;
        }
        bukt[k + 1] = val;
    }
}

void bucketSort(vector<float>& inputArr) {
    int s = inputArr.size();
    vector<vector<float>> bucketArr(s);

    for (float j : inputArr) {
        int bi = s * j;
        bucketArr[bi].push_back(j);
    }

    for (auto& bukt : bucketArr) {
        insertionSort(bukt);
    }

    int idx = 0;
    for (auto& bukt : bucketArr) {
        for (float j : bukt) {
            inputArr[idx++] = j;
        }
    }
}

int main() {
    vector<float> inputArr = {0.77, 0.16, 0.38, 0.25, 0.71, 0.93, 0.22, 0.11, 0.24, 0.67};
    cout << "Arreglo original:\n";
    for (float x : inputArr) cout << x << " ";
    cout << endl;

    bucketSort(inputArr);

    cout << "Arreglo ordenado:\n";
    for (float x : inputArr) cout << x << " ";
    cout << endl;
    return 0;
}