using System;

class T3_Recorridos_CS
{
    static void Main(string[] args)
    {
        int[,] numeros = { { 4, 5, 6 }, { 1, 2, 3 }, { 7, 8, 9 } };
        int filas = numeros.GetLength(0);
        int columnas = numeros.GetLength(1);
        for (int i = 0; i < filas; i++)
        {
            for (int j = 0; j < columnas; j++)
            {
                Console.Write("[" + numeros[i, j] + "]");
            }
            Console.WriteLine(" ");
        }
    }
}
