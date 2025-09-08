using System;

class T3_Insertar_CS
{
    static void Main(string[] args)
    {
        int[] numeros = { 4, 5, 6 ,  1, 2, 3 , 7, 8, 9 };
        int tam = numeros.GetLength(0);
        for (int i = 0; i < tam; i++)
        {
            
                Console.Write("[" + numeros[i] + "] ");
            
        }
    }
}
