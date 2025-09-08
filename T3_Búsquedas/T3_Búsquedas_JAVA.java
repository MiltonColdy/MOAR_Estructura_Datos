package T3_Búsquedas;

public class T3_Búsquedas_JAVA 
    {
    public static void main(String[] args)
    {
        int[] numeros = {4,5,6,1,2,3,7,8,9};
        int buscar = 4;
        int tru = 0;
        
        for (int i = 0; i < numeros.length; i++ ) 
        {
                if(numeros[i] == buscar) 
                {
                    tru = 1;
                    System.out.print("El número [" + buscar + "] fue encontrado en el índice: " + i +" :D");
                }

        }
            if (tru != 1)
            {
               System.out.print("El número [" + buscar + "] NO fue encontrado D:");
            }
                
    }
    
}

//aita