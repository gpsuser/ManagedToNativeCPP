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

    CComSafeArray<double> arr(3);
    arr[0] = 2.0;
    arr[1] = 3.0;
    arr[2] = 5.0;

    

	// Call the methods.
	pICalc->Add(5, 10, &lResult); // "raw interfaces only" allows passing the pointer to the result as an extra parameter
    wprintf(L"The result is %d\n", lResult);

	pICalc->Subtract(25, 3, &lResult); // "raw interfaces only" allows passing the pointer to the result as an extra parameter
    wprintf(L"The result is %d\n", lResult);

    double lResult1 = 0.0;

	pICalc->ArrayTest(arr, &lResult1);
	wprintf(L"The result is %f\n", lResult1);

	// Uninitialize COM.
    CoUninitialize();
    return 0;
}
