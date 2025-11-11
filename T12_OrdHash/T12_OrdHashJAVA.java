package T12_OrdHash;
import java.util.Arrays;

public class T12_OrdHashJAVA {
    static void hashSort(int[] arr, int maxVal) {
        int size = maxVal + 1;
        int EMPTY = -1;
        int[] hashTable = new int[size];
        Arrays.fill(hashTable, EMPTY);

        for (int key : arr) {
            int index = key % size;
            while (hashTable[index] != EMPTY)
                index = (index + 1) % size;
            hashTable[index] = key;
        }

        int k = 0;
        for (int i = 0; i < size; i++)
            if (hashTable[i] != EMPTY)
                arr[k++] = hashTable[i];
    }

    public static void main(String[] args) {
        int[] data = {15, 3, 9, 20, 12, 5};
        hashSort(data, 20);
        System.out.println(Arrays.toString(data));
    }
}