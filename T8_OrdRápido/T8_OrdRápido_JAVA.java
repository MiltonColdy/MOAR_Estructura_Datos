package T8_OrdRápido;

public class T8_OrdRápido_JAVA {
    static void swap(int[] a, int j, int k) {
        int temp = a[j];
        a[j] = a[k];
        a[k] = temp;
    }

    static int part(int[] a, int l, int h) {
        int pvt = a[h];
        int j = l - 1;
        for (int k = l; k < h; k++) {
            if (a[k] < pvt) {
                j++;
                swap(a, j, k);
            }
        }
        swap(a, j + 1, h);
        return j + 1;
    }

    static void qckSort(int[] a, int l, int h) {
        if (l < h) {
            int pi = part(a, l, h);
            qckSort(a, l, pi - 1);
            qckSort(a, pi + 1, h);
        }
    }

    public static void main(String[] args) {
        int[] a = {10, 7, 8, 9, 1, 5};
        int size = a.length;

        System.out.println("Arreglo original:");
        for (int v : a)
            System.out.print(v + " ");
        System.out.println();

        qckSort(a, 0, size - 1);

        System.out.println("Arreglo ordenado:");
        for (int v : a)
            System.out.print(v + " ");
        System.out.println();
    }
}

