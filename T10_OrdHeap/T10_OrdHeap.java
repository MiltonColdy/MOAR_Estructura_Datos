package T10_OrdHeap;
public class T10_OrdHeap {

    static void heap(int[] arr, int n, int i) {
        int max;
        while (true) {
            max = i;
            int l = 2 * i + 1;
            int r = 2 * i + 2;

            if (l < n && arr[l] > arr[max]) max = l;
            if (r < n && arr[r] > arr[max]) max = r;

            if (max != i) {
                int temp = arr[i];
                arr[i] = arr[max];
                arr[max] = temp;
                i = max;
            } else {
                break;
            }
        }
    }

    static void heapSort(int[] arr) {
        int n = arr.length;

        for (int i = n / 2 - 1; i >= 0; i--)
            heap(arr, n, i);

        for (int i = n - 1; i > 0; i--) {
            int temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;
            heap(arr, i, 0);
        }
    }

    public static void main(String[] args) {
        int[] arr = {12, 11, 13, 5, 6, 7};
        heapSort(arr);

        System.out.print("Arreglo ordenado: [ ");
        for (int x : arr) System.out.print(x + " ");
        System.out.println("]");
    }
}