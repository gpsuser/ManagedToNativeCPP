// CPPClient.cpp: Defines the entry point for the console application.
// C++ client that calls a managed DLL.

#include "stdafx.h"
#include "tchar.h"
// Import the type library.
//#import "..\ManagedDLL\bin\Debug\ManagedDLL.tlb" raw_interfaces_only
#import "C:\Users\grant\Desktop\dev\gitProjects\CsharpInsideCpp2005\ManagedDLL\bin\Debug\ManagedDLL.tlb" raw_interfaces_only

#include <atlbase.h>
#include <atlsafe.h>

// TO DO :
// Try CComSafeArray in 2D 
 
using namespace ManagedDLL;

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
    SAFEARRAY** res = NULL;
	pICalc->ReturnArrayTest(res);
	//wprintf(L"The result is %f\n", res[1]);

	// STILL NEED TO DEFINE TEH SAFEARRAY** 

	// Uninitialize COM.
    CoUninitialize();
    return 0;
}
