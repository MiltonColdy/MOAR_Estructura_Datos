using System;

class BucketSortArray {
    static void InsertionSort(double[] arr, int n) {
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

    static void BucketSort(double[] arr, int bucketCount) {
        int n = arr.Length;
        if (n <= 1) return;

        double minVal = arr[0], maxVal = arr[0];
        for (int i = 1; i < n; i++) {
            if (arr[i] < minVal) minVal = arr[i];
            if (arr[i] > maxVal) maxVal = arr[i];
        }
        if (minVal == maxVal) return;

        double[,] buckets = new double[bucketCount, n];
        int[] bucketSizes = new int[bucketCount];
        double range = maxVal - minVal;

        for (int i = 0; i < n; i++) {
            int index = (int)(((arr[i] - minVal) / range) * (bucketCount - 1));
            buckets[index, bucketSizes[index]++] = arr[i];
        }

        int k = 0;
        for (int i = 0; i < bucketCount; i++) {
            if (bucketSizes[i] > 0) {
                double[] temp = new double[bucketSizes[i]];
                for (int j = 0; j < bucketSizes[i]; j++)
                    temp[j] = buckets[i, j];
                InsertionSort(temp, temp.Length);
                for (int j = 0; j < temp.Length; j++)
                    arr[k++] = temp[j];
            }
        }
    }

    static void Main() {
        double[] data = {0.42, 0.32, 0.23, 0.52, 0.25, 0.47, 0.51};
        BucketSort(data, 5);
        Console.WriteLine(string.Join(", ", data));
    }
}