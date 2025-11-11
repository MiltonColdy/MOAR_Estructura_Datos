using System;

class HashSortArray {
    static void HashSort(int[] arr, int maxVal) {
        int size = maxVal + 1;
        int EMPTY = -1;
        int[] hashTable = new int[size];
        for (int i = 0; i < size; i++) hashTable[i] = EMPTY;

        foreach (int key in arr) {
            int index = key % size;
            while (hashTable[index] != EMPTY)
                index = (index + 1) % size;
            hashTable[index] = key;
        }

        int k = 0;
        for (int i = 0; i < size; i++) {
            if (hashTable[i] != EMPTY)
                arr[k++] = hashTable[i];
        }
    }

    static void Main() {
        int[] data = {15, 3, 9, 20, 12, 5};
        HashSort(data, 20);
        Console.WriteLine(string.Join(", ", data));
    }
}