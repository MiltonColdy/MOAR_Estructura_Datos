#include <iostream>
#include <vector>
using namespace std;

class ShellSort {
public:
    static void displayArr(const vector<int>& inputArr) {
        for (int k : inputArr)
            cout << k << " ";
        cout << endl;
    }

    void sort(vector<int>& inputArr) {
        int size = inputArr.size();
        int gapSize = size / 2;

        while (gapSize > 0) {
            for (int j = gapSize; j < size; j++) {
                int val = inputArr[j];
                int k = j;
                while (k >= gapSize && inputArr[k - gapSize] > val) {
                    inputArr[k] = inputArr[k - gapSize];
                    k -= gapSize;
                }
                inputArr[k] = val;
            }
            gapSize /= 2;
        }
    }
};

int main() {
    vector<int> inputArr = {36, 34, 43, 11, 15, 20, 28, 45};

    cout << "Arreglo original:" << endl;
    ShellSort::displayArr(inputArr);

    ShellSort obj;
    obj.sort(inputArr);

    cout << "Arreglo ordenado:" << endl;
    ShellSort::displayArr(inputArr);

    return 0;
}