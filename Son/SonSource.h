
//  SonSource.h  //
/// Description: This is the declarations module for the project Son. 
///              Header file that contains the functions declarations for the main module to use.

#define _CRT_SECURE_NO_WARNINGS
#pragma once

// Includes:
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <Windows.h>

// Constants:
#define STATUS_SUCCESS  0
#define STATUS_FAILURE  1
#define LINE_LEN 16

// Declarations:
void xor_cipher(char* data, char* key, char* output, int offset);

// Note: see descriptions for the function in SonSource.c