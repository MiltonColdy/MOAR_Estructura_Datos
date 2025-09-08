package T3_Recorridos;
public class T3_Recorridos_JAVA
{
    public static void main(String[] args)
    {
        int[][] numeros = {{4,5,6},{1,2,3},{7,8,9}}; int c = 0;
        
        
        for (int[] fila : numeros) {
            for (int n : fila) {
                System.out.print("[" + n + "]");
            }
            System.out.println();
        }
    }
}