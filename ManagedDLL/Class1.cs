using System;
using System.Collections.Generic;
using System.Text;

// Class1.cs
// A simple managed DLL that contains two methods

namespace ManagedDLL
{
	// Interface declaration.
    public interface ICalculator
    {
        int Add(int Number1, int Number2);
        int Subtract(int Num1, int Num2);
        double ArrayTest(double[] ar);
        void InitialiseArray(ref double[] arr);
    };


    // Interface implementation.
    public class ManagedClass : ICalculator
    {
        public int Add(int Number1, int Number2)
        {
            return Number1 + Number2;
        }

        public int Subtract(int Num1, int Num2)
        {

            return Num1 - Num2;
        }


        public double ArrayTest(double[] ar){


            return ar[1];
        }

        // receive 1D array from c++ and return a 1D array to c++
        public void InitialiseArray(ref double[] arr) //double[] ar)
        {

            //arr = new double[4];
            for (int i = 0; i < 10 ; i++ )
            {
                arr[i] = i + 2;
                //arr[0] = 0;
                //arr[1] = 1;
                //arr[2] = 2;
                //arr[3] = 5;
            }
        }

    }
}