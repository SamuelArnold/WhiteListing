// WhiteListing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <strsafe.h>

using namespace std; 

int RegEdit()
{
	//system("echo Let's Read Some Registry Keys");
	//system("REG QUERY HKLM\Software\Microsoft\ResKit / v Version");
	//system("REG QUERY HKLM\Software\Microsoft");
	

	//cout << "Hello my friend";
	//char value[1024];
	//DWORD value_length = 1024;
	//RegQueryValueEx("HKEY_LOCAL_MACHINE\SOFTWARE\Policies\Microsoft\TPM", "OSManagedAuthLevel", NULL, REG_SZ, (LPBYTE)&value, value_length);
	//cout << "the value read from the registry is: " << value << endl;




	return 0;
}//end function 


int main()
{
	cout << "Hello my friend";
	RegEdit();
    return 0;
}

