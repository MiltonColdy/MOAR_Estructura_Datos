using System;
using System.Collections.Generic;

class T12_OrdBucketCS
{
    static void InsertionSort(List<double> bukt)
    {
        for (int j = 1; j < bukt.Count; j++)
        {
            double val = bukt[j];
            int k = j - 1;
            while (k >= 0 && bukt[k] > val)
            {
                bukt[k + 1] = bukt[k];
                k--;
            }
            bukt[k + 1] = val;
        }
    }

    static void BucketSort(double[] inputArr)
    {
        int s = inputArr.Length;
        List<double>[] bucketArr = new List<double>[s];
        for (int i = 0; i < s; i++)
            bucketArr[i] = new List<double>();

        foreach (double j in inputArr)
        {
            int bi = (int)(s * j);
            bucketArr[bi].Add(j);
        }

        foreach (var bukt in bucketArr)
        {
            InsertionSort(bukt);
        }

        int idx = 0;
        foreach (var bukt in bucketArr)
        {
            foreach (double j in bukt)
            {
                inputArr[idx++] = j;
            }
        }
    }

    static void Main()
    {
        double[] inputArr = { 0.77, 0.16, 0.38, 0.25, 0.71, 0.93, 0.22, 0.11, 0.24, 0.67 };
        Console.WriteLine("Arreglo original:");
        Console.WriteLine(string.Join(" ", inputArr));
        BucketSort(inputArr);
        Console.WriteLine("Arreglo ordenado:");
        Console.WriteLine(string.Join(" ", inputArr));
    }
}