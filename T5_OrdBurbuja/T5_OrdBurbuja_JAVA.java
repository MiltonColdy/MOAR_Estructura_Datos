package T5_OrdBurbuja;
public class T5_OrdBurbuja_JAVA {
    public static void main(String[] args) {
        int[] arr = {1000,10,10000,100,100000,1000000};
        System.out.print("Arreglo Original: ");
        for (int i = 0; i < arr.length; i++) {
            System.out.print(arr[i] + " ");
        }
        
        for (int i = 0; i < arr.length;i++) {
            for (int j = 0; j < arr.length - i - 1;j++) {
                if (arr[j] > arr[j+1]) {
                    int temp = arr[j];
                        arr[j] = arr[j + 1];
                        arr[j + 1] = temp;
                }
            }
        }
        System.out.println(" ");
        System.out.print("Arreglo Ordenado: ");
        for (int i = 0; i < arr.length; i++) {
            System.out.print(arr[i] + " ");
        }
        
    }
}
