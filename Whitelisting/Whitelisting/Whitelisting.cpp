// Whitelisting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include <iostream>
#include <tchar.h>
#include <malloc.h>
#include <winreg.h>
#include <stdio.h>

using namespace std; 


#define TOTALBYTES    8192
#define BYTEINCREMENT 4096



void OpenKeyEx() {
	char i;
	string samkey = "";
	HKEY hKey;
	DWORD port;
	RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		TEXT("SYSTEM\\CurrentControlSet\\Control\\Terminal Server\\WinStations\\RDP-Tcp"), NULL, KEY_READ, &hKey);
	DWORD size = sizeof(DWORD);
	RegQueryValueEx(
		hKey,
		TEXT("PortNumber"),
		NULL,
		NULL,
		(BYTE *)&port,
		&size
	);
	cout << "Port number = " << port << '\n';
	//cout << "Type \'c\' to change the port: ";
//	cin >> i;
//	if (i == 'c') {
	//	cout << "Type the port number: ";
	//	cin >> x;//what is the variable?
		//RegReplaceKey // or 'RegSetKeyValue'?
	//	(HKEY_LOCAL_MACHINE,
		//	TEXT("SYSTEM\\CurrentControlSet\\Control\\Terminal Server\\WinStations\\RDP-Tcp"), TEXT("PortNumber") /*...?*/);

	//	RegSaveKey( //where and how to use this one?
			//HKEY hKey,
		//	"PortNumber",
		//	NULL
		//)
			//cout << "Port has been changed to: " << port << '\n
//	RegSetValueEx(
	//	hKey,
		//TEXT("PortNumber"), //This was right, but it's better to add the TEXT macro.
		//0, //OK
		//REG_DWORD, // OK
		//(BYTE*)&port,
		//size //This had been set to sizeof(DWORD), remember?
	//);
		system("pause");
	//}
	RegCloseKey(hKey);
}



void  seven(){

	cout << "Hello";
}

void main()
{
	
	//string key1 = "SYSTEM\\CurrentControlSet\\Control\\Terminal Server\\WinStations\\RDP-Tcp";
	//string key2 = "PortNumber";
	cout << "Test Key Value";
	
	OpenKeyEx();
}

