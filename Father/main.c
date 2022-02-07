/* *********************************************

	Authors:
	Matan Eckhaus Moyal
	Dvir Katz

	Project: Father

   ********************************************* */

   /// Description: This is the main module for the project Father
   ///				 The program will create son processes - one for each 16 bytes. The program will wait until every 
   ///				 son process will encrypt the text and then will create the next son - until the file is fully encrypted.

#define _CRT_SECURE_NO_WARNINGS

// Includes:
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include "FatherSource.h"


/**************************************** Main Function Summary: ****************************************
/// Description: The program will create son processes - one for each 16 bytes. The program will wait until every
///				 son process will encrypt the text and then will create the next son - until the file is fully encrypted.
/// Parameters:
///		argc - int. the number of input arguments - should accept 2 arguments.
///		argv - char pointer to a list of input arguments - plaintext file, key file
///	Returns: int value - 0 if succeeded, 1 if failed
*********************************************************************************************************/
int main(int argc, char* argv[])
{
	// Check if the input is correct (2  arguments)
	if (3 != argc)
	{
		printf("Error: Wrong number of input arguments!\n");
		return STATUS_FAILURE;
	}

	int offset = 0, proccess_status = 0;
	char offset_val[5];
	char* arguments;
	char* path2debug = "Son.exe ";
	DWORD offset_max;

	//create_process_2_write_file(argv[1]); // additional option - creates a file using notepad so that the user can insert his own text to cypher
	//create_process_2_write_file(argv[2]);	// additional option - creates a file using notepad so that the user can insert his own key

	// Open input plain file
	HANDLE h_plain = CreateFileA(
		argv[1],				// file name
		GENERIC_READ,			// access mode
		FILE_SHARE_READ,		// share read
		NULL,					// defualt security
		OPEN_EXISTING,			// open when file exist
		FILE_ATTRIBUTE_NORMAL,	// normal
		NULL);

	// If failed to open file
	if (h_plain == INVALID_HANDLE_VALUE)
	{
		printf("Error: Failed to open plain file! The error code is %d\n", GetLastError());
		return STATUS_FAILURE;
	}

	offset_max = GetFileSize(h_plain, NULL);

	CloseHandle(h_plain);

	// creating son processes and sending the relevant arguments - to encrypt the plain file
	for (offset; offset < offset_max; offset += 16)
	{
		_itoa(offset, offset_val, 10);
		arguments = (CHAR*)malloc(strlen(path2debug) + strlen(argv[1]) + strlen(offset_val) + strlen(argv[2]) + 3);
		if (arguments == NULL) {
			printf("Error: Failed to allocate memory\n");
			return STATUS_FAILURE;
		}
		concatenate(arguments, path2debug, argv[1], offset_val, argv[2]);
		proccess_status = create_process_4_son(arguments);
		if (proccess_status != 0)
			return STATUS_FAILURE; //handeling failure in the function create_process_4_son
	}
	return STATUS_SUCCESS;
}