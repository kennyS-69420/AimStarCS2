#pragma once
#include <Windows.h>
#include <iostream>
#include <TlHelp32.h> 
#include <comdef.h>
using namespace std;

namespace VAC
{
	long GetProcessIdFromName(const char* name)
	{
		HANDLE hsnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (hsnapshot == INVALID_HANDLE_VALUE)
		{
			cout << "Create TlHelp32 Error!" << endl;
			return -1;
		}

		PROCESSENTRY32 processer;
		processer.dwSize = sizeof(PROCESSENTRY32);

		int flag = Process32First(hsnapshot, &processer);
		while (flag != 0)
		{
			_bstr_t processName(processer.szExeFile);  
			if (strcmp(processName, name) == 0)
			{
				return processer.th32ProcessID;        
			}
			flag = Process32Next(hsnapshot, &processer);
		}

		CloseHandle(hsnapshot);
		return -2;
	}

	int GetHandle()
	{
		long pid = GetProcessIdFromName("steam.exe");
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
		if (hProcess == NULL)
		{
			cout << "Open process failed: " << GetLastError() << endl;
			return 1;
		}
	}
}

