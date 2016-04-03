using System;
using System.Collections.Generic;
using System.Text;

// Class1.cs
// A simple managed DLL that contains two methods

// RegAsm.exe ManagedDLL.dll /tlb:ManagedDLL.tlb /codebase

namespace ManagedDLL
{
	// Interface declaration.
    public interface ICalculator
    {
        int Add(int Number1, int Number2);
        int Subtract(int Num1, int Num2);
        double ArrayTest(double[] ar);
      //  int CommSafe2D(int[,] arr);
        void InitialiseArray(ref double[] arr);
        void Initialise2DArray(ref int[,] arrInt);
        
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

        // http://climserv.ipsl.polytechnique.fr/documentation/idl_help/2D_Array_Examples.html
        // receive a 2D commsafe array
     //   public int CommSafe2D(int[,] arr)
       // {

         //   return arr[1, 1];
        //}

        // receive 1D array from c++ and return a 1D array to c++
        public void InitialiseArray(ref double[] arr) //double[] ar)
        {
           // **** try redo this using "new" given that the print 'f' as introduced
            /*
            arr = new double[4];
            arr[0] = 0;
            arr[1] = 1;
            arr[2] = 2;
            arr[3] = 5;
            */
            
            for (int i = 0; i < 10 ; i++ )
            {
                arr[i] = i + 2;
                
            }
        }

        // https://limbioliong.wordpress.com/2011/06/22/passing-multi-dimensional-managed-array-to-c-part-2/
        // receive 2D array from c++ and return a 2D array to c++
        public void Initialise2DArray(ref int[,] arrInt)
        {
            

          //  int d1 = arrInt.Length;
           // int d2 = arrInt.GetUpperBound();

            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    arrInt[i,j] = i + j;
                }
            }

          //  int k = 10;
         //   Console.WriteLine(arrInt[0, 0]);

        }
        

    }  // classs
} // namespace