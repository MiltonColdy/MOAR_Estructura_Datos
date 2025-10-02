package T9_OrdMerge;
public class T9_OrdMerge_JAVA {
    public static void merge(int[] a, int l, int m, int r) {
        int a1 = m - l + 1;
        int a2 = r - m;
        int[] L = new int[a1];
        int[] R = new int[a2];
        for (int j = 0; j < a1; j++)
            L[j] = a[l + j];
        for (int k = 0; k < a2; k++)
            R[k] = a[m + 1 + k];
        int i = 0, j2 = 0, k2 = l;
        while (i < a1 && j2 < a2) {
            if (L[i] <= R[j2]) {
                a[k2] = L[i];
                i++;
            } else {
                a[k2] = R[j2];
                j2++;
            }
            k2++;
        }
        while (i < a1) {
            a[k2++] = L[i++];
        }
        while (j2 < a2) {
            a[k2++] = R[j2++];
        }
    }
    public static void mergeSort(int[] a, int l, int r) {
        if (l < r) {
            int m = l + (r - l) / 2;
            mergeSort(a, l, m);
            mergeSort(a, m + 1, r);
            merge(a, l, m, r);
        }
    }
    public static void main(String[] args) {
        int[] a = {39, 28, 44, 11};
        System.out.println("Arreglo original:");
        for (int x : a) System.out.print(x + " ");
        mergeSort(a, 0, a.length - 1);
        System.out.println("\nArreglo ordenado:");
        for (int x : a) System.out.print(x + " ");
    }
}