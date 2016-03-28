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
    CreateSafeArray(&res); // Create the safe array

	pICalc->InitialiseArray(&res);
	
	printSAFEARRAY(res); 
   SafeArrayDestroy(res);
   res = NULL;

 // http://stackoverflow.com/questions/3730840/how-to-create-and-initialize-safearray-of-doubles-in-c-to-pass-to-c-sharp

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