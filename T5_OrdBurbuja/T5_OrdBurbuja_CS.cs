using System;
class T5_OrdBurbuja_CS
{
    static void Main(string[] args)
    {
        int[] arr = { 97, 3, 7, 1, 11, 17, 13, };
        Console.Write("El arreglo original es: ");
        for (int i = 0; i < arr.Length; i++)
        {
            Console.Write(arr[i] + " ");
        }

        for (int i = 0; i < arr.Length; i++)
        {
            for (int j = 0; j < arr.Length - i - 1; j++)
            {
                if (arr[j] > arr[j + 1])
                {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
        Console.WriteLine(" ");
        Console.Write("El arreglo ordenado es: ");
        for (int i = 0; i < arr.Length; i++)
        {
            Console.Write(arr[i] + " ");
        }
    }
}