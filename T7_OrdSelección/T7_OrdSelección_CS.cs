using System;
class T7_OrdSelección_CS
{
    static void Main(string[] args)
    {
        int[] arr = { 10, 30, 5, 25, 35, 50, 45 };
        int min, temp;
        Console.Write("Arreglo original: \n");
        for (int i = 0; i < arr.Length; i++)
        {
            Console.Write(arr[i] + " ");
        }
        for (int i = 0; i < arr.Length; i++)
        {
            min = i;
            for (int j = i + 1; j < arr.Length; j++)
            {
                if (arr[min] > arr[j])
                {
                    min = j;
                }


            }
            temp = arr[i];
            arr[i] = arr[min];
            arr[min] = temp;
        }
    Console.Write("\n");
    Console.Write("Arreglo ordenado: \n");
    for (int i = 0; i < arr.Length; i++) {
        Console.Write(arr[i] + " ");
        }
    }
}