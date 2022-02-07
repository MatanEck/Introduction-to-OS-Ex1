
//  SonSource.c  //
/// Description: This is the functions module for the project Son. Contains the different functions that main module uses.

#define _CRT_SECURE_NO_WARNINGS
#pragma once

// Includes:
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <Windows.h>
#include "SonSource.h"


void xor_cipher(char* data, char* key, char* output, int offset) {
	/// Description: This function ciphers an input text with key text
	/// Parameters:
	///		data - pointer to the input text to cipher
	///		key - pointer to the input key for encryption
	///		output - pointer to the encrypted segment
	///		offset - the offset in bytes from the begining of the text, to get from data the 16 bytes ciphered
	///	Returns: void. no return value (the encrypted segment is saved to output pointer)

	int i;

	for (i = 0; i < LINE_LEN; ++i) {
		output[i] = data[i + offset] ^ key[i % 16];
	}
	output[LINE_LEN] = '\0';
}