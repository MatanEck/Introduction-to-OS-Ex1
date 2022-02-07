
//  FatherSource.c  //
/// Description: This is the functions module for the project Son. Contains the different functions that main module uses.

#define _CRT_SECURE_NO_WARNINGS

// Includes:
#include <stdio.h>
#include <stdlib.h>  
#include <string.h>
#include <windows.h>
#include "FatherSource.h"


int create_process_2_write_file(CHAR* FileName)
{
	/// Description: This function creates a file using notepad so that the user can insert his own text
	/// Parameters:
	///		FileName - CHAR pointer to the FileName string
	///	Returns: int value - 0 if succeeded, 1 if failed

	HANDLE hProcess = 0;	// Handle for process
	HANDLE hThread = 0;		// Handle for Thread
	STARTUPINFO	si;			// Startinfo Structure
	PROCESS_INFORMATION pi; // Startinfo Structure
	DWORD ProcessID = 0, ThreadID = 0;
	BOOL bProcess;
	CHAR func[] = "notepad.exe ";
	CHAR* command_line = (CHAR*)malloc(strlen(FileName) + strlen(func) + 1);
	if (command_line) {
		strcpy(command_line, func);
		strcat(command_line, FileName);
		command_line[strlen(command_line)] = '\0';
	}
	else {
		printf("Error: Failed to allocate memory\n");
		return STATUS_FAILURE;
	}

	// Step 1 - Filling the memory block of STARTUPINFO & PROCESS_INFORMATION with ZERO
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));

	// Step 2 - Create Process Function

	bProcess = CreateProcessA(
		NULL, /*  No module name (use command line). */
		command_line,			/*  Command line. */
		NULL,					/*  Process handle not inheritable. */
		NULL,					/*  Thread handle not inheritable. */
		FALSE,					/*  Set handle inheritance to FALSE. */
		NORMAL_PRIORITY_CLASS,	/*  creation/priority flags. */
		NULL,					/*  Use parent's environment block. */
		NULL,					/*  Use parent's starting directory. */
		&si,					/*  Pointer to STARTUPINFO structure. */
		&pi						/*  Pointer to PROCESS_INFORMATION structure. */
	);

	// Step 3 - Checking Process has created or not

	if (bProcess == FALSE)
	{
		printf("Error: Failed to create process! The error code is %d\n", GetLastError());
		return STATUS_FAILURE;
	}
	// Step 4 - Printing Process ID and Thread ID
	//printf("Process ID = %d \n", pi.dwProcessId);
	//printf("Thread ID = %d", pi.dwThreadId);

	// Step 5 - WaitForSingleObject

	WaitForSingleObject(pi.hProcess, INFINITE);

	// Step 6 - Closing the Handle of Primary Process and Primary Thread

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	free(command_line);

	return STATUS_SUCCESS;
}

int create_process_4_son(CHAR* arguments)
{
	/// Description: This process creates a child process according to the instructions
	/// Parameters:
	///		arguments - CHAR pointer to the Command line string
	///	Returns: int value - 0 if succeeded, 1 if failed

	HANDLE hProcess = 0;	// Handle for process
	HANDLE hThread = 0;		// Handle for Thread
	STARTUPINFO	si;			// Startinfo Structure
	PROCESS_INFORMATION pi; // Startinfo Structure
	DWORD ProcessID = 0;
	DWORD ThreadID = 0;
	BOOL bProcess;

	// Step 1 - Filling the memory block of STARTUPINFO & PROCESS_INFORMATION with ZERO
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));

	// Step 2 - Create Process Function

	bProcess = CreateProcessA(
		NULL, /*  No module name (use command line). */
		arguments,				/*  Command line. */
		NULL,					/*  Process handle not inheritable. */
		NULL,					/*  Thread handle not inheritable. */
		FALSE,					/*  Set handle inheritance to FALSE. */
		NORMAL_PRIORITY_CLASS,	/*  creation/priority flags. */
		NULL,					/*  Use parent's environment block. */
		NULL,					/*  Use parent's starting directory. */
		&si,					/*  Pointer to STARTUPINFO structure. */
		&pi						/*  Pointer to PROCESS_INFORMATION structure. */
	);

	// Step 3 - Checking Process has created or not

	if (bProcess == FALSE)
	{
		printf("Error: Failed to create process! The error code is %d\n", GetLastError());
		return STATUS_FAILURE;
	}
	// Step 4 - Printing Process ID and Thread ID
	//printf("Process ID = %d \n", pi.dwProcessId);
	//printf("Thread ID = %d", pi.dwThreadId);

	// Step 5 - WaitForSingleObject

	WaitForSingleObject(pi.hProcess, INFINITE);

	// Step 6 - Closing the Handle of Primary Process and Primary Thread

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	free(arguments);

	return STATUS_SUCCESS;
}

void concatenate(char* args, char* path, char* a, char* b, char* c) {
	/// Description: This function concatenates 4 strings - path,a,b,c and saves them to string args (to create command line for creating proccess)
	/// Parameters:
	///		args - char pointer to the output string
	///		path - char pointer to the path string
	///		a -	char pointer to string a
	///		b - char pointer to string b
	///		c -	char pointer to string c
	///	Returns: void. no return value (the concatenated string is saved to args pointer)

	if (args) {
		strcpy(args, path);
		strcat(args, a);
		strcat(args, " ");
		strcat(args, b);
		strcat(args, " ");
		strcat(args, c);
		args[strlen(args)] = '\0';
	}
}
