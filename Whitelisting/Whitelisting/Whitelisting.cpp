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

using namespace std; 
using namespace winreg;

#define TOTALBYTES    8192
#define BYTEINCREMENT 4096

int main()
{

	//string key1 = "SYSTEM\\CurrentControlSet\\Control\\Terminal Server\\WinStations\\RDP-Tcp";
	//string key2 = "PortNumber";
	//cout << "Test Key Value";

	//OpenKeyEx();

	constexpr int kExitOk = 0;
	constexpr int kExitError = 1;
	try
	{
		wcout << L"=========================================\n";
		wcout << L"*** Trying to read  HKEY_CURRENT_USER \ SOFTWARE\\7 - Zip \n";
		wcout << L"=========================================\n\n";

		//
		// Test subkey and value enumeration
		//
		
		const wstring testSubKey = L"SOFTWARE\\7-Zip";
		RegKey key{ HKEY_CURRENT_USER, testSubKey };


		/*
		/////////////////////////////////////////////////////////
		// Enumerate through subkeys and print them 
		////////////////////////////////////////////////////////
		vector<wstring> subKeyNames = key.EnumSubKeys();
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

		// Open the key
		key.Open(HKEY_CURRENT_USER, testSubKey);

		const wstring testSz = L"C:"; // Test Path 
		wstring testSZ1 = key.GetStringValue(L"Path"); // Value of 7 zips Path

		if (testSZ1 != testSz) // If they dont equel
		{
			//wcout << L"RegKey::QueryValueType failed for REG_SZ.\n";
			wcout << L"RegKey::Not Equal Values... \n";
			wcout << testSZ1 << L"   Should Be   " << testSz;
			wcout << L"\nDo you wish to over right? ";
			string test; 
			cin >> test;
			//key.SetStringValue(L"TestValueString", testSz); // Set values 
		}
		else 
			wcout << L"Pass.\n";
		key.Close();

	}

	// Catch exceptions 
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


	// Break Main 
	return kExitOk;
}
