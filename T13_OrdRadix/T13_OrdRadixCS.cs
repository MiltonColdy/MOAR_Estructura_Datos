using System;

class RadixSortArray {
    static void CountingSort(int[] arr, int exp) {
        int n = arr.Length;
        int[] output = new int[n];
        int[] count = new int[10];

        for (int i = 0; i < n; i++)
            count[(arr[i] / exp) % 10]++;

        for (int i = 1; i < 10; i++)
            count[i] += count[i - 1];

        for (int i = n - 1; i >= 0; i--) {
            int index = (arr[i] / exp) % 10;
            output[count[index] - 1] = arr[i];
            count[index]--;
        }

        for (int i = 0; i < n; i++)
            arr[i] = output[i];
    }

    static void RadixSort(int[] arr) {
        int maxVal = arr[0];
        for (int i = 1; i < arr.Length; i++)
            if (arr[i] > maxVal) maxVal = arr[i];

        for (int exp = 1; maxVal / exp > 0; exp *= 10)
            CountingSort(arr, exp);
    }

    static void Main() {
        int[] data = {170, 45, 75, 90, 802, 24, 2, 66};
        RadixSort(data);
        Console.WriteLine(string.Join(", ", data));
    }
}