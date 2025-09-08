package T4_RecorridosFilas;
public class T4_RecorridosFilas_JAVA
{
    public static void main(String[] args)
    {
        int[][] numeros = {{4,5,6},{1,2,3},{7,8,9}};
        int c = -1;
        
        for (int[] fila : numeros) {
            c = c + 1;
            System.out.print("Fila de índice "+c+": [ ");
            for (int n : fila) {
                System.out.print(n+" ");
            }
            System.out.println("]");
        }
    }
}