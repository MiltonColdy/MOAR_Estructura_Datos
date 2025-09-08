using System;

class T3_Insertar_CS
{
    static void Main(string[] args)
    {
        int[] numeros = { 4, 5, 6, 1, 2, 3, 7, 8, 9 };
        int val = 9;
        int pos = 0;
        Console.WriteLine("El arreglo antes de la inserción: ");
         for (int i = 0; i < numeros.Length; i++)
        {
            Console.Write("[" + numeros[i] + "] ");
        }
        for (int i = numeros.Length - 1; i > pos; i--)
        {
            numeros[i] = numeros[i - 1];
        }

        numeros[pos] = val;
        Console.WriteLine(" ");
        Console.WriteLine("___________________________________");
        Console.WriteLine("El arreglo después de la inserción: ");
        for (int i = 0; i < numeros.Length; i++)
        {
            Console.Write("[" + numeros[i] + "] ");
        }
    }
}