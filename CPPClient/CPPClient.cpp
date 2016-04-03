// CPPClient.cpp: Defines the entry point for the console application.
// C++ client that calls a managed DLL.

//#include <iostream>
#include "stdafx.h"
#include "tchar.h"
#include <atlbase.h>
#include <atlsafe.h>
#import "C:\Users\grant\Desktop\dev\gitProjects\CsharpInsideCpp2005\ManagedDLL\bin\Debug\ManagedDLL.tlb" raw_interfaces_only


// TO DO :
// Try CComSafeArray in 2D 
 
using namespace ManagedDLL;

// to print the contents of the SAFEARAY once initialised inside managed dll
static void printSAFEARRAY(SAFEARRAY*);

void Fill2DSafeArray(LPSAFEARRAY lpsaArray, long Value) 
{ 
   int lower0 = lpsaArray->rgsabound[0].lLbound; 
   int upper0 = lpsaArray->rgsabound[0].cElements + lower0; 
   long* pData = (long*)lpsaArray->pvData; 
   for(int i = lower0; i < upper0; i++) { 
      int lower1 = lpsaArray->rgsabound[1].lLbound; 
      int upper1 = lpsaArray->rgsabound[1].cElements + lower1; 
      for(int j = lower1; j < upper1; j++) { 
         *pData = i + j; 
         pData++; 
      } 
   }
}

void CreateSafeArray(SAFEARRAY** saData)        
{
    //double data[10]; // some sample data to write into the created safearray
    SAFEARRAYBOUND  Bound;
    Bound.lLbound   = 0;
    Bound.cElements = 10;

    *saData = SafeArrayCreate(VT_R8, 1, &Bound);

    double HUGEP *pdFreq;
    HRESULT hr = SafeArrayAccessData(*saData, (void HUGEP* FAR*)&pdFreq);
    if (SUCCEEDED(hr))
    {
            // copy sample values from data[] to this safearray
        for (DWORD i = 0; i < 10; i++)
        {
            *pdFreq++ = (double)i; //data[i];
        }
        SafeArrayUnaccessData(*saData);
    }
}


int _tmain(int argc, _TCHAR* argv[])
{
    // Initialize COM.
    HRESULT hr = CoInitialize(NULL);

	// Create the interface pointer.
    ICalculatorPtr pICalc(__uuidof(ManagedClass));
    long lResult = 0;

    CComSafeArray<double> arr(4);
    arr[0] = 2.0;
    arr[1] = 3.0;
    arr[2] = 5.0;
	arr[3] = 6.4;

    

	// Call the methods.
	pICalc->Add(5, 10, &lResult); // "raw interfaces only" allows passing the pointer to the result as an extra parameter
    wprintf(L"The result is %d\n", lResult);

	pICalc->Subtract(25, 3, &lResult); // "raw interfaces only" allows passing the pointer to the result as an extra parameter
    wprintf(L"The result is %d\n", lResult);


    // send in an array to c#, get single result back
    double lResult1 = 0.0;
	pICalc->ArrayTest(arr, &lResult1);
	wprintf(L"The result is %f\n", lResult1);



	// send in array to C#, try to receive an array result from c#
	// http://www.codeproject.com/Questions/322206/CComSafeArray-ways-of-use
    //CComSafeArray<double> lResult2(4);
	//  SAFEARRAY(VARIANT) res; //[4];
	//int res[4]; // = NULL; //[4];
	// http://www.codeproject.com/Articles/16206/Call-C-code-from-C-and-read-an-array-of-struct-whi
	//pICalc->ReturnArrayTest(arr, &lResult2);
	//wprintf(L"The result is %f\n", lResult2[1]);
	// CComSafeArray<double> res(4);
    
	SAFEARRAY* res = NULL;

	// try redo this with the old verson of the initialisation (now that the print issue was resolved (i.e. float not int)
    CreateSafeArray(&res); // Create the safe array

	pICalc->InitialiseArray(&res);
	
	printSAFEARRAY(res); 
    SafeArrayDestroy(res);
    res = NULL;

 // http://stackoverflow.com/questions/3730840/how-to-create-and-initialize-safearray-of-doubles-in-c-to-pass-to-c-sharp


	// *********** CONSIDER SENDING IN A 2D ARAY OF INTEGERS *************
	// http://edn.embarcadero.com/cs/article/22016 NBNBNBNBNBNB ***

// Create 2D array of long integers. Similar to... 
   // long Array[20][10]; 
   SAFEARRAYBOUND sabdBounds[2] = { {10, 0}, {20, 0}}; // gps: {num cols ,col start}{num rows, row start}
   LPSAFEARRAY lpsaArray = SafeArrayCreate(VT_I4, 2, sabdBounds);

   // Fill array with values 
   Fill2DSafeArray(lpsaArray, 5);

  // long lDim1Size = lUbound - lLbound + 1;

// Get elements of the array and display the value.
//https://limbioliong.wordpress.com/2011/06/22/passing-multi-dimensional-managed-array-to-c-part-2
   int counter = 0;

   for (int i = 0; i < 20; i++)   // gps: rows 
{
	for (int j = 0; j < 10; j++) // gps: cols
	{
	//	for (int k = 0; k < lDim3Size; k++)
	//	{
			long	rgIndices[2];
			int		value;
			// The indices of the array are specified
			// using "rgIndices".
			// Here the specificatio indicates that
			// we want to access the item at array
			// location : [i][j][k].
			//rgIndices[0] = k;
			rgIndices[0] = j;
			rgIndices[1] = i;
			SafeArrayGetElement
			(
				lpsaArray,
				rgIndices,
				(void FAR*)&value
			);
			printf (" counter %d : %d\r\n", counter ,value);
			counter ++;
		//}
	}
}



int k = 10;

  // printSAFEARRAY(lpsaArray); 

   // Destroy array 
   SafeArrayDestroy(lpsaArray); 




/*
	 SAFEARRAY*	pSafeArray = NULL;
    
	 // Array of 2 SAFEARRAYBOUND structs. One for each dimension.
     SAFEARRAYBOUND	rgsabound[2];
      // Set the bounds information FOR array with the following dimensions :[2][3]
  
      // 6 elemenst in total. All elements laid out in memory sequentially and contiguously.
      rgsabound[0].lLbound = 0;        
      rgsabound[0].cElements = 3;      // cols
      rgsabound[1].lLbound = 0;
      rgsabound[1].cElements = 3;      // rows
      
	  // Create the SAFEARRAY: VT_I4, // This signifies the integer type.: 2,  // This signifies 2 dimensions,  rgsabound:  // Bounds information.
      pSafeArray = SafeArrayCreate (VT_I4,2,rgsabound);
*/

// first initialise 2d safearray

	  /* for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    pSafeArray[i,j] = i + j;
                }
            }
*/
     //CreateSafeArray(&res); // Create the safe array

	 
//	pICalc->Initialise2DArray(&pSafeArray);
	
//	printSAFEARRAY(res); 
 //  SafeArrayDestroy(pSafeArray);
  // pSafeArray = NULL;

   // TESTING COMSAFE ARRAY MANIPULATION
      // send in an array to c#, get single result back
   //double tmp[4] = NULL; // lResult1 = 0.0;
   //pICalc->TestCommSafeArray(arr,&tmp); //    ArrayTest(arr, &lResult1);
	//wprintf(L"The result is %f\n", lResult1);

    


	// Uninitialize COM.
     CoUninitialize();

	 return 0;
}



// print the contents of the SAFEARRAY after it has been initialised in the managed .dll
static void printSAFEARRAY(SAFEARRAY* res){

	double* pVals;
    HRESULT hr1 = SafeArrayAccessData(res, (void**)&pVals); // direct access to SA memory

	if (SUCCEEDED(hr1))
	{
	  long lowerBound, upperBound;  // get array bounds
	  SafeArrayGetLBound(res, 1 , &lowerBound);
	  SafeArrayGetUBound(res, 1, &upperBound);

	  long cnt_elements = upperBound - lowerBound + 1; 

	  for (int i = 0; i < cnt_elements; ++i)  // iterate through returned values
	  {                              
		double lVal = pVals[i];   
		wprintf(L"The element value is %f\n", lVal); //lVal);  // float
		//std::cout << "element " << i << ": value = " << lVal << std::endl;
	  } 
    }
}