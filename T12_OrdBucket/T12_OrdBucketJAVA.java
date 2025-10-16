package T12_OrdBucket;


import java.util.*;

public class T12_OrdBucketJAVA {
    static void insertionSort(List<Double> bukt) {
        for (int j = 1; j < bukt.size(); j++) {
            double val = bukt.get(j);
            int k = j - 1;
            while (k >= 0 && bukt.get(k) > val) {
                bukt.set(k + 1, bukt.get(k));
                k--;
            }
            bukt.set(k + 1, val);
        }
    }

    static void bucketSort(double[] inputArr) {
        int s = inputArr.length;
        List<Double>[] bucketArr = new List[s];
        for (int i = 0; i < s; i++) {
            bucketArr[i] = new ArrayList<>();
        }

        for (double j : inputArr) {
            int bi = (int) (s * j);
            bucketArr[bi].add(j);
        }

        for (List<Double> bukt : bucketArr) {
            insertionSort(bukt);
        }

        int idx = 0;
        for (List<Double> bukt : bucketArr) {
            for (double j : bukt) {
                inputArr[idx++] = j;
            }
        }
    }

    public static void main(String[] args) {
        double[] inputArr = {0.77, 0.16, 0.38, 0.25, 0.71, 0.93, 0.22, 0.11, 0.24, 0.67};
        System.out.println("Arreglo original:");
        System.out.println(Arrays.toString(inputArr));
        bucketSort(inputArr);
        System.out.println("Arreglo ordenado:");
        System.out.println(Arrays.toString(inputArr));
    }
}
