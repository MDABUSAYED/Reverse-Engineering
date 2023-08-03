#include <windows.h>
#include <fstream>
#include <tchar.h>
#include <stdio.h>
#include <iostream>
#include <TlHelp32.h>

int testIfFileExists(LPSTR dllToInject)
{
	std::ifstream dllfile(dllToInject, std::ios::binary);
    if (!dllfile)
    {
    	printf("%s could not be found!",dllToInject);
		exit(-1);
    }
	
	return 0;
}

int getProcIDByName(LPSTR victimProcessName)
{
	PROCESSENTRY32 pe32 = {sizeof(PROCESSENTRY32)};
	HANDLE hProcSnap;
	int procID = 0;
	printf("Searching for %s\r\n",victimProcessName);
    fflush(stdout);
	hProcSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if(Process32First(hProcSnap, &pe32))
	{
		do
		{
			if(!strcmp(pe32.szExeFile, victimProcessName))
			{
				procID = pe32.th32ProcessID;
				return procID;
			}
		}
		while(Process32Next(hProcSnap, &pe32));
	}
	printf("Process not found, ensure you have run the victim process");
	return -1;
}

void forceProcessToLoadDLL(LPSTR dllToInject, int procID)
{
	/*
	* Get process handle passing in the process ID.
	*/
	HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
		/*
	*TODO: Complete this part of the code!!!!!!!!!
	*  Include detailed comments!
	*/

	if(!process){
		std::cout << "Error: the specified process couldn't be found";
	}

	/* GetModuleHandleA gets handle of kernel32.dll*/
	HMODULE handle_32dll = GetModuleHandleA("kernel32.dll");

	/* GetProcAddress retrieves the address of "LoadLibraryA"*/
    FARPROC addr_loadlibA = GetProcAddress(handle_32dll, "LoadLibraryA");

    if(!addr_loadlibA){
		std::cout << "Error: the LoadLibraryA function was not found inside kernel32.dll lib";
	}

    /* VirtualAllocEx allocates memory space for dll which will be injected*/
	LPVOID addr_alloc = VirtualAllocEx(process, 0, strlen(dllToInject), 12288, 4);

	if(!addr_alloc){
		std::cout << "Error: the memory could not be allocated inside the chosen process";
	}

	/* WriteProcessMemory*/
	if(!WriteProcessMemory(process, addr_alloc, dllToInject, strlen(dllToInject), 0)){
		std::cout << "Error: there was no bytes written to the process's address space.";
	}

	/* CreateRemoteThread*/
	HANDLE thread = CreateRemoteThread(process, 0,0, (LPTHREAD_START_ROUTINE)addr_loadlibA, addr_alloc, 0,0);

	if(!thread){
		std::cout << "Error: the remote thread could not be created.";
	}else {
		std::cout << "Success: the remote thread was successfully created.";
	}

	/*
	* Close the handle to the process, because we've already injected the DLL.
	*/
	CloseHandle(process);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
    LPWSTR *szArgList;
    int argCount;

	szArgList = CommandLineToArgvW(GetCommandLineW(), &argCount);
     if (szArgList == NULL || argCount < 3)
     {
        MessageBox(NULL, "Missing or invalid input provided.", "Error", MB_OK);
		printf("Usage: Injector.exe <full-path-to-dll> <victimProcessName>\r\n\r\n<pathToDLL> is the location where the dll exists (e.g., \"C:\\Users\\IEUser\\Documents\\Injectee\\DLLInject.dll\")\r\n\r\n<victimProcessName> is the name of the victim process into which the dll will be injected (e.g., myfile.exe).");
        return -1;
     }

	LPSTR pathToDLL = (LPSTR)malloc(1024); 
	wcstombs(pathToDLL, szArgList[1], 1024);
	LPSTR victimProcessName = (LPSTR)malloc(1024);
	wcstombs(victimProcessName, szArgList[2], 1024);
	int procID = -1;
	printf("Checking DLL Path...");
    fflush(stdout);
	testIfFileExists(pathToDLL);		
	printf("DLL Found: %s", pathToDLL);
	fflush(stdout);
	procID = getProcIDByName(victimProcessName);
	if (procID == -1)
		return -1;
	
	printf("Attempting to load dll into process...%s", victimProcessName);
    fflush(stdout);
	forceProcessToLoadDLL(pathToDLL, procID);
    fflush(stdout);
	return 0;
}

