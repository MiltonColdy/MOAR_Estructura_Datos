using System;

class HeapSortDemo
{
    static void Heap(int[] arr, int n, int i)
    {
        while (true)
        {
            int max = i;
            int l = 2 * i + 1;
            int r = 2 * i + 2;

            if (l < n && arr[l] > arr[max]) max = l;
            if (r < n && arr[r] > arr[max]) max = r;

            if (max != i)
            {
                int temp = arr[i];
                arr[i] = arr[max];
                arr[max] = temp;
                i = max;
            }
            else break;
        }
    }

    static void HeapSort(int[] arr)
    {
        int n = arr.Length;

        for (int i = n / 2 - 1; i >= 0; i--)
            Heap(arr, n, i);

        for (int i = n - 1; i > 0; i--)
        {
            int temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;
            Heap(arr, i, 0);
        }
    }

    static void Main()
    {
        int[] arr = { 12, 11, 13, 5, 6, 7 };

        HeapSort(arr);

        Console.Write("Arreglo ordenado: [ ");
        foreach (int x in arr) Console.Write(x + " ");
        Console.WriteLine("]");
    }
}