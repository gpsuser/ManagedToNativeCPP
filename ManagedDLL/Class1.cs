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
    }
}