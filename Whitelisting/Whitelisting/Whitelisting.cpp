// Whitelisting.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include "windows.h"
#include <iostream>
#include <tchar.h>
#include <malloc.h>
#include <winreg.h>
#include <stdio.h>
#include "WinReg.hpp"   // Module to test
#include <exception>
#include <iostream>
#include <vector>
#include "STIGh.h"  

using namespace std; 
using namespace winreg;
using namespace saX;
#define TOTALBYTES    8192
#define BYTEINCREMENT 4096





void statusCheck () {
/////////////////////////////////////////////
// Checks to see if the whitelisting is on.
// WILL RETURN ERROR 5 if NOT RUNNING AS ADMIN
//////////////////////////////////////////
	const wstring testSubKey = L"SOFTWARE\\Policies\\Microsoft\\Windows\\Safer\\CodeIdentifiers";
	DWORD testStatus = 0x00000000;
	RegKey key{ HKEY_LOCAL_MACHINE, testSubKey };
		DWORD testDw11 = key.GetDwordValue(L"DefaultLevel");
	key.Open(HKEY_LOCAL_MACHINE, testSubKey);

	if (testStatus != testDw11)
	{
		wcout << L"\nStatus: OFF\n";
	}
	else
		wcout << L"\nStatus: ON\n";

	cout << "SOFTWARE\\Policies\\Microsoft\\Windows\\Safer\\CodeIdentifiers" << "key DefaultLevel " << "\n Recomended Value: " << testStatus << " Actual Value: " << testDw11;
	key.Close();

}




void GPOForceUpdate() {
	/////////////////////////////////////////////////////////////////////////////////////////
	// Every time you change a key you have to update the Group policy simply run GPOForceUpdate();
	//////////////////////////////////////////////////////////////////////
	cout << "\nLaunching Force update";
	// additional information
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	// set the size of the structures
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	// start the program up
	CreateProcess(_T("C:\\Windows\\System32\\gpupdate.exe"),   // the path
		_T("force") ,        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi             // Pointer to PROCESS_INFORMATION structure (removed extra parentheses)
	);

	//send process to sleep so more code doesnt run
	Sleep(10000);
	// Close process and thread handles. 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

int main()
{    ///////////////////////////////////////////
	// Main loop of the program
	////////////////////////////////////////////
	constexpr int kExitOk = 0;
	constexpr int kExitError = 1;
	try
	{
		StigObj.PrintScore();
		wcout << L"\n=========================================\n";
		wcout << L"Trying to read  HKEY_CURRENT_USER | SOFTWARE| 7 - Zip";
		wcout << L"\n=========================================\n\n";

		//
		// Test subkey and value enumeration
		//
		
		const wstring testSubKey = L"SOFTWARE\\7-Zip";
		RegKey key{ HKEY_CURRENT_USER, testSubKey };


		/*
		/////////////////////////////////////////////////////////
		// Enumerate through subkeys and print them 
		////////////////////////////////////////////////////////
		
		svector<wstring> subKeyNames = key.EnumSubKeys();
		wcout << L"Subkeys:\n";
		for (const auto& s : subKeyNames)
		{
			wcout << L"  [" << s << L"]\n";
		}
		wcout << L'\n';

		/////////////////////////////////////
		// Enumerate through values  *does not get data*
		//////////////////////////////////////
		vector<pair<wstring, DWORD>> values = key.EnumValues();
		wcout << L"Values bugga :\n";
		for (const auto& v : values)
		{
			wcout << L"  [" << v.first << L"](" << RegKey::RegTypeToString(v.second) << L")\n";
		}
		wcout << L'\n';
		*/



		////////////////////////////////////////////////
		// Test stupid key (Gets data unlike above)
		////////////////////////////////////////////////

		key.Open(HKEY_CURRENT_USER, testSubKey);
		const wstring testSz = L"C:"; // Test Path 
		wstring testSZ1 = key.GetStringValue(L"Path"); // Value of 7 zips Path
		if (testSZ1 != testSz) // If they dont equel
		{
			//wcout << L"RegKey::QueryValueType failed for REG_SZ.\n";
			wcout << L"RegKey::Not Equal Values... \n";
			wcout << testSZ1 << L"   Should Be   " << testSz <<endl;
			//wcout << L"\nDo you wish to over right? ";
			//string test; 
			//cin >> test;
			//key.SetStringValue(L"TestValueString", testSz); // Set values 
		}
		else 
			wcout << L"Pass.\n";
		key.Close();



		////////////////////////////////////////////////////////////////////////
		// Checks to See if white listing is turned on 
		///////////////////////////////////////////////////////////////////////
		cout << "\n*************\nIs whitelisting on?\n********************\n";
		statusCheck();
		cout << "\n****************\nOf course\n******************* \n";
	}
	////////////////////////////////////////////////////////////////////
	// Catch exceptions  of everything
	////////////////////////////////////////////////////////////////////
	catch (const RegException& e)
	{
		cout << "\n*** Registry Exception: " << e.what();
		cout << "\n*** [Windows API error code = " << e.ErrorCode() << "\n\n";
		return kExitError;
	}
	catch (const exception& e)
	{
		cout << "\n*** ERROR: " << e.what() << '\n';
		return kExitError;
	}

	//////////////////////////////////////
	// Exit the porgram
	//////////////////////////////////////
	string exit; 
	cin >> exit; 
	// Break Main 
	return kExitOk;
}
