#pragma once
#ifndef INCLUDE_STIGH_H
#define INCLUDE_STIGH_H

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

using namespace winreg;
using namespace std; 

namespace saX
{
	class StigScore
	{
	public:
		void PrintScore() {

			int ScoreNumber=0;
			cout << "\n*****************\nSTIG SCORE IS\n*********************\n";
	
			try {
				///////////////////////////////////////////////////////////////
				// Checks keys to see if they follow stig requirments  
				// Example 
				//[HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\RDR\Parameters]
				//"EnablePlainTextPassword" = dword:00000000
				///////////////////////////////////////////////////////////////

				cout << "\n------------\nWill ERROR CODE 5 if NOT Running As ADMIN: \n------------\n";
				cout << "\n------------\nTEST EnablePlainTextPassword: \n------------\n";

				// Create key
				const wstring testSubKey = L"SYSTEM\\CurrentControlSet\\Services\\RDR\\Parameters";
				RegKey key{ HKEY_LOCAL_MACHINE, testSubKey };


				DWORD testStatus = 0x00000000; // Data that you want you are testing 
				DWORD testDw11 = key.GetDwordValue(L"EnablePlainTextPassword"); // Value you want

				// Open the key 
				key.Open(HKEY_LOCAL_MACHINE, testSubKey);
				wcout << "Key: SYSTEM\\CurrentControlSet\\Services\\RDR\\Parameters" << "Value: EnablePlainTextPassword ";
				wcout << "\n Recomended Value: " << testStatus << " Actual Value: " << testDw11;
				
				// Test if Test Values are reccommend
				if (testStatus != testDw11)
				{
					wcout << L"\nStatus: OFF\n";
				}
				else {
					wcout << L"\nStatus: ON\n";
					ScoreNumber += 1;
					}
				key.Close();
				cout << "\n------------\nScore: "<< ScoreNumber<<"\n------------\n";
		}
		////////////////////////////////////////////////////////////////////
		// Catch exceptions  of everything
		////////////////////////////////////////////////////////////////////
		catch (const RegException& e)
		{
			cout << "\n*** Registry Exception: " << e.what();
			cout << "\n*** [Windows API error code = " << e.ErrorCode() << "\n\n";
			
		}
		catch (const exception& e)
		{
			cout << "\n*** ERROR: " << e.what() << '\n';
			
		}

		}
	}StigObj;
}



#endif // INCLUDE_STIGH_H