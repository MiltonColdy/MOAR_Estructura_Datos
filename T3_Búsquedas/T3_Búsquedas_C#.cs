using System;

class T3_Búsquedas_CS
{
    static void Main(string[] args)
    {
        int buscar = 9;
        int enc = 0;
        int[] numeros = { 4, 5, 6, 1, 2, 3, 7, 8, 9 };
        for (int i = 0; i < numeros.Length; i++)
        {
            if (numeros[i] == buscar)
            {
                enc = 1;
                Console.WriteLine("El número " + buscar + " fue encontrado en el índice: " + i + " :D");
            }
        }
        if (enc != 1)
        {
            Console.WriteLine("El número " + buscar + " NO fue encontrado D:");
        }
    }
}
//aita