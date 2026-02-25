using System;
using System.Diagnostics;

class Program
{
    static void Main()
    {
        int N = 50_000_000;
        float[] A = new float[N];
        float[] B = new float[N];
        float[] C = new float[N];

        Random rmd = new Random();

        for(int i = 0; i < N; i++)
        {
            A[i] = (float)rmd.NextDouble();
            B[i] = (float)rmd.NextDouble();
        }

        Stopwatch sw = Stopwatch.StartNew();

        for(int i = 0; i < N; i++)
        {
            C[i] = A[i] + B[i];
        }
        sw.Stop();

        Console.WriteLine("Tiempo CPU: " + sw.ElapsedMilliseconds + " es");
    }
}
