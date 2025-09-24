package T7_OrdSelección;
public class T7_OrdSelección_JAVA {
    public static void main (String[] args) {
    int arr[] = {10,5,20,35,25,50,45};
    int min, temp;
    System.out.print("Arreglo original: \n");
    for (int i = 0; i < arr.length; i++) {
        System.out.print(arr[i] + " ");
    }
    for (int i = 0; i < arr.length; i++) {
        min = i;
        for (int j = i + 1; j < arr.length; j++) {
            if (arr[min] > arr [j]) {
                min = j;
            }
        }
        temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
    System.out.print( "\n");
    System.out.print("Arreglo ordenado: \n");
    for (int i = 0; i < arr.length; i++) {
        System.out.print(arr[i] + " ");
        }
    }
}