# ManagedToNativeCPP

Consider calling managed methods (C#) from native C++.

An initial example is shown where a pointer to a SAFEARRAY is sent from C++ to a managed method in a C# dll.

The managed method changes the contents of the SAFEARRAY. 

The C++ application is able to see these changes and can continue working with this SAFEARRAY - and its updated content.


reference: [https://support.microsoft.com/en-us/kb/828736](https://support.microsoft.com/en-us/kb/828736).