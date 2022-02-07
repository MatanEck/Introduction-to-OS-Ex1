/* *********************************************

	Authors:
	Dvir Katz
	Matan Eckhaus Moyal

	Project: Son

   ********************************************* */
   /// Description: This is the main module for the project Son.
   ///				 The program will read 16 bytes from the input file to cypher, 
   ///				 and according to a key file will encrypt it by using XOR between the characters.

#define _CRT_SECURE_NO_WARNINGS

// Includes:
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <Windows.h>
#include"SonSource.h"


/**************************************** Main Function Summary: ****************************************
/// Description: The function will read 16 bytes from the input file to cypher,
///				 and according to a key file will encrypt it by using XOR between the characters.
/// Parameters:
///		argc - int. the number of input arguments - should accept 3 arguments.
///		argv - char pointer to a list of input arguments - plaintext file, offset, key file
///	Returns: int value - 0 if succeeded, 1 if failed
*********************************************************************************************************/
int main(int argc, char* argv[])
{
	if (4 != argc) { 	// Check if the input is correct (3  arguments)
		printf("Error: Wrong number of input arguments!\n");
		return STATUS_FAILURE;
	}
	char* p;
	int offset;
	// calculate offset of second argument
	errno = 0;
	long conv = strtol(argv[2], &p, 10);
	// Check for errors: e.g., the string does not represent an integer or the integer is larger than int
	if (errno != 0 || *p != '\0' || conv > INT_MAX || conv < INT_MIN) {
		printf("Error: Invalid offset value\n");
		return STATUS_FAILURE;;
	}
	else { offset = conv; } // No error

	// Open plain file and read it
	HANDLE h_plain = CreateFileA(argv[1], GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (h_plain == INVALID_HANDLE_VALUE) { 		// If failed to open file
		printf("Error: Failed to open plain file! The error code is %d\n", GetLastError());
		return STATUS_FAILURE;
	}
	DWORD dw_bytes_2_read, dw_bytes_read = 0;
	dw_bytes_2_read = GetFileSize(h_plain, NULL);
	char* plain_arr = (char*)malloc(dw_bytes_2_read * sizeof(char) + 1);
	if (plain_arr == NULL) {
		printf("Error: Failed to allocate memory\n");
		return STATUS_FAILURE;
	}

	BOOL read_plain = ReadFile(h_plain, (void*)plain_arr, dw_bytes_2_read, &dw_bytes_read, NULL);
	if (read_plain == 0) {		// If failed to read file
		printf("Error: Failed to Read plain file! The error code is %d\n", GetLastError());
		return STATUS_FAILURE;
	}
	if (dw_bytes_read > 0)
		plain_arr[dw_bytes_read] = '\0';

	// Open key file and read it
	HANDLE h_key = CreateFileA(argv[3], GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (h_key == INVALID_HANDLE_VALUE) {		// If failed to open file
		printf("Error: Failed to open key file! The error code is %d\n", GetLastError());
		return STATUS_FAILURE;
	}
	DWORD dw_bytes_2_read_1, dw_bytes_read_1 = 0;
	dw_bytes_2_read_1 = GetFileSize(h_key, NULL);
	char* key_arr = (char*)malloc(dw_bytes_2_read_1 * sizeof(char) + 1);
	if (key_arr == NULL) {
		printf("Error: Failed to allocate memory\n");
		return STATUS_FAILURE;
	}

	BOOL read_key = ReadFile(h_key, (void*)key_arr, dw_bytes_2_read_1, &dw_bytes_read_1, NULL);
	if (read_key == 0) {		// If failed to read file
		printf("Error: Failed to Read key file! The error code is %d\n", GetLastError());
		return STATUS_FAILURE;
	}
	if (dw_bytes_read_1 > 0)
		key_arr[dw_bytes_read_1] = '\0';

	if (offset == 0) {	// in case we at the begining of plain file - we want to create new file for Encrypted_message
		HANDLE h_crypt = CreateFileA("Encrypted_message.txt", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (h_crypt == INVALID_HANDLE_VALUE) {	// If failed to open file
			printf("Error: Failed to open encrypted file! The error code is %d\n", GetLastError());
			return STATUS_FAILURE;
		}
		DWORD dw_bytes_2_write = LINE_LEN, dw_bytes_written = 0;
		char* crypt_arr = (char*)malloc(dw_bytes_2_write * sizeof(char) + 1);
		if (crypt_arr == NULL) {
			printf("Error: Failed to allocate memory\n");
			return STATUS_FAILURE;
		}

		xor_cipher(plain_arr, key_arr, crypt_arr, offset);

		BOOL write_status = WriteFile(h_crypt, (void*)crypt_arr, dw_bytes_2_write, &dw_bytes_written, NULL);
		if (write_status == 0 && dw_bytes_2_write != dw_bytes_written) {
			printf("Error: File write partially or failed. The error code is %d\n", GetLastError());
			return STATUS_FAILURE;
		}
		CloseHandle(h_crypt);
		free(crypt_arr);
	}
	else {			// if we want to append to existing Encrypted_message
		HANDLE h_crypt = CreateFileA("Encrypted_message.txt", FILE_APPEND_DATA, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);							// attribute template
		if (h_crypt == INVALID_HANDLE_VALUE) {	// If failed to open file
			printf("Error: Failed to open encrypted file! The error code is %d\n", GetLastError());
			return STATUS_FAILURE;
		}
		DWORD dw_bytes_2_write = LINE_LEN, dw_bytes_written = 0;
		char* crypt_arr = (char*)malloc(dw_bytes_2_write * sizeof(char) + 1);
		if (crypt_arr == NULL) {
			printf("Error: Failed to allocate memory\n");
			return STATUS_FAILURE;
		}
		xor_cipher(plain_arr, key_arr, crypt_arr, offset);

		DWORD dw_moved = SetFilePointer(h_crypt, 0l, NULL, FILE_END);
		if (dw_moved == INVALID_SET_FILE_POINTER) {
			printf("Terminal failure: Unable to set file pointer to end-of-file. The error code is %d\n", GetLastError());
			return STATUS_FAILURE;
		}

		BOOL write_status = WriteFile(h_crypt, (void*)crypt_arr, dw_bytes_2_write, &dw_bytes_written, NULL);
		if (write_status == 0 && dw_bytes_2_write != dw_bytes_written) {
			printf("Error: File write partially or failed. The error code is %d\n", GetLastError());
			return STATUS_FAILURE;
		}
		CloseHandle(h_crypt);
		free(crypt_arr);
	}
	// Closing all handles and freeing memory cllocated
	CloseHandle(h_plain);
	CloseHandle(h_key);
	free(plain_arr);
	free(key_arr);
	return STATUS_SUCCESS;
}