package T11_OrdBucket;
import java.util.Arrays;

public class T11_OrdBucketJAVA {
    static void insertionSort(double[] arr, int n) {
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

    static void bucketSort(double[] arr, int bucketCount) {
        int n = arr.length;
        if (n <= 1) return;

        double minVal = arr[0], maxVal = arr[0];
        for (int i = 1; i < n; i++) {
            if (arr[i] < minVal) minVal = arr[i];
            if (arr[i] > maxVal) maxVal = arr[i];
        }
        if (minVal == maxVal) return;

        double[][] buckets = new double[bucketCount][n];
        int[] bucketSizes = new int[bucketCount];
        double range = maxVal - minVal;

        for (double v : arr) {
            int index = (int) (((v - minVal) / range) * (bucketCount - 1));
            buckets[index][bucketSizes[index]++] = v;
        }

        int k = 0;
        for (int i = 0; i < bucketCount; i++) {
            if (bucketSizes[i] > 0) {
                double[] bucket = Arrays.copyOf(buckets[i], bucketSizes[i]);
                insertionSort(bucket, bucketSizes[i]);
                for (double val : bucket) arr[k++] = val;
            }
        }
    }

    public static void main(String[] args) {
        double[] data = {0.42, 0.32, 0.23, 0.52, 0.25, 0.47, 0.51};
        bucketSort(data, 5);
        System.out.println(Arrays.toString(data));
    }
}