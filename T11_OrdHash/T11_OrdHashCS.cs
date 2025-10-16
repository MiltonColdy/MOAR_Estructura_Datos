using System;

class T11_OrdHashCS
{
    public static void DisplayArr(int[] inputArr)
    {
        foreach (int k in inputArr)
            Console.Write(k + " ");
        Console.WriteLine();
    }

    public void Sort(int[] inputArr)
    {
        int size = inputArr.Length;
        int gapSize = size / 2;

        while (gapSize > 0)
        {
            for (int j = gapSize; j < size; j++)
            {
                int val = inputArr[j];
                int k = j;
                while (k >= gapSize && inputArr[k - gapSize] > val)
                {
                    inputArr[k] = inputArr[k - gapSize];
                    k -= gapSize;
                }
                inputArr[k] = val;
            }
            gapSize /= 2;
        }
    }

    static void Main()
    {
        int[] inputArr = { 36, 34, 43, 11, 15, 20, 28, 45 };
        Console.WriteLine("Arreglo original:");
        DisplayArr(inputArr);

        ShellSort obj = new ShellSort();
        obj.Sort(inputArr);

        Console.WriteLine("Arreglo ordenado:");
        DisplayArr(inputArr);
    }
}