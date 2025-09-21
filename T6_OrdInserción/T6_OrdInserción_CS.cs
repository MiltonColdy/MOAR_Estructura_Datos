using System;
class T5_OrdBurbuja_CS
{
    static void Main(string[] args)
    {
        int[] arr = { 10, 5, 20, 35, 25, 45, 50 };
        int temp, j;

        Console.WriteLine("Arreglo original: ");
        for (int i = 0; i < arr.Length; i++)
        {
            Console.Write(arr[i] + " ");
        }
        for (int i = 0; i < arr.Length; i++)
        {
            temp = arr[i];
            j = i - 1;

            while (j >= 0 && temp < arr[j])
            {
                arr[j + 1] = arr[j];
                j -= 1;
            }
            arr[j + 1] = temp;
        }
    Console.WriteLine(" ");
    Console.WriteLine("\nArreglo ordenado: ");
    for (int i = 0; i < arr.Length; i++) {
        Console.Write(arr[i] + " ");
     }
    }
}