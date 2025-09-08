package T3_Insertar;
import java.util.Arrays;
public class T3_Insertar_JAVA
{
    public static void main(String[] args)
    {
        int[] numeros = {4,5,6,1,2,3,7,8,9};
        
        System.out.println("Arreglo antes de insertar: " + Arrays.toString(numeros));

        int val = 9;
        int pos = 0;

        for (int i = numeros.length - 1; i > pos; i--) {
            numeros[i] = numeros[i - 1];
        }
        numeros[pos] = val;
        System.out.print("Arreglo después de la inserción: " + Arrays.toString(numeros));
    }
    
}