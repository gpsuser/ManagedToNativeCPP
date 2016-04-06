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

static void print_1D_SAFEARRAY(SAFEARRAY*);
void Create_1D_SafeArray(SAFEARRAY**);
void Fill2DSafeArray(LPSAFEARRAY, long); 
void print_2D_SAFEARRAY(LPSAFEARRAY, int, int);

int _tmain(int argc, _TCHAR* argv[])
{
    // Initialize COM.
    HRESULT hr = CoInitialize(NULL);

	// Create the interface pointer.
    ICalculatorPtr pICalc(__uuidof(ManagedClass));
    long lResult = 0;

	// instantiate andinitialise CCOMSAFEARRAY
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

    
	SAFEARRAY* res = NULL;

	// try redo this with the old verson of the initialisation (now that the print issue was resolved (i.e. float not int)
    Create_1D_SafeArray(&res); // Create the safe array

	pICalc->InitialiseArray(&res);
	
	print_1D_SAFEARRAY(res); 
    SafeArrayDestroy(res);
    res = NULL;

 
// Create 2D array of long integers. Similar to... 
   // long Array[20][10]; 
	int numCols = 10;
	int numRows = 20;

   SAFEARRAYBOUND sabdBounds[2] = { {10, 0}, {20, 0}}; // gps: {num cols ,col start}{num rows, row start}
   LPSAFEARRAY lpsaArray = SafeArrayCreate(VT_I4, 2, sabdBounds);

   
   Fill2DSafeArray(lpsaArray, 5);

   print_2D_SAFEARRAY(lpsaArray,numRows,numCols);

int k = 10;

   // Destroy array 
   SafeArrayDestroy(lpsaArray); 

    // Uninitialize COM.
     CoUninitialize();

	 return 0;
}


// First pass at printing contents of 2D safearray
void print_2D_SAFEARRAY(LPSAFEARRAY lpsaArray, int rows, int cols){

  int counter = 0;

   for (int i = 0; i < rows; i++)   // gps: rows 
{
	for (int j = 0; j < cols; j++) // gps: cols
	{
			long	rgIndices[2];
			int		value;

			// The indices of the array are specified using "rgIndices". Here the specificatio indicates that we want to access the item at array location : [i][j]
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
	}
}


}

// print the contents of the SAFEARRAY after it has been initialised in the managed .dll
static void print_1D_SAFEARRAY(SAFEARRAY* res){

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

// initialises 1D safearray
void Create_1D_SafeArray(SAFEARRAY** saData)        
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

// initialise 2D safearray
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