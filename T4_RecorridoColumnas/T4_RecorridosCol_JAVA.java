package T4_RecorridoColumnas;
public class T4_RecorridosCol_JAVA
{
    public static void main(String[] args)
    {
        int[][] numeros = {{4,5,6},{1,2,3},{7,8,9}};
        
        int filas = numeros.length;       // Número de filas.
        int columnas = numeros[0].length; // Número de columnas.

        for (int j = 0; j < columnas; j++) { // Recorrer las columnas.
            System.out.print("Columna de índice " + j + ": [ ");
            for (int i = 0; i < filas; i++) { // Recorrer las filas para esa columna.
                System.out.print(numeros[i][j] + " ");
            }
            System.out.println("]");
        }
    }
}
//aita