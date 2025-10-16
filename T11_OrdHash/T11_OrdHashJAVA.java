package T11_OrdHash;


public class T11_OrdHashJAVA {
    public static void displayArr(int[] inputArr) {
        for (int k : inputArr) {
            System.out.print(k + " ");
        }
        System.out.println();
    }

    public void sort(int[] inputArr) {
        int size = inputArr.length;
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

    public static void main(String[] args) {
        int[] inputArr = {36, 34, 43, 11, 15, 20, 28, 45};
        System.out.println("Arreglo original:");
        displayArr(inputArr);

        ShellSort obj = new ShellSort();
        obj.sort(inputArr);

        System.out.println("Arreglo ordenado:");
        displayArr(inputArr);
    }
}
