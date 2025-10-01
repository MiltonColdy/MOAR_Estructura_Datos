using System;

class Program
{
    static void Swap(int[] a, int j, int k)
    {
        int temp = a[j];
        a[j] = a[k];
        a[k] = temp;
    }

    static int Part(int[] a, int l, int h)
    {
        int pvt = a[h];
        int j = l - 1;
        for (int k = l; k < h; k++)
        {
            if (a[k] < pvt)
            {
                j++;
                Swap(a, j, k);
            }
        }
        Swap(a, j + 1, h);
        return j + 1;
    }

    static void QckSort(int[] a, int l, int h)
    {
        if (l < h)
        {
            int pi = Part(a, l, h);
            QckSort(a, l, pi - 1);
            QckSort(a, pi + 1, h);
        }
    }

    static void Main()
    {
        int[] a = { 10, 7, 8, 9, 1, 5 };
        int size = a.Length;

        Console.WriteLine("Arreglo original:");
        foreach (int v in a)
            Console.Write(v + " ");
        Console.WriteLine();

        QckSort(a, 0, size - 1);

        Console.WriteLine("Arreglo ordenado:");
        foreach (int v in a)
            Console.Write(v + " ");
        Console.WriteLine();
    }
}
