
//  FatherSource.h  //
/// Description: This is the declarations module for the project Father. 
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
int create_process_2_write_file(CHAR* FileName);
int create_process_4_son(CHAR* arguments);
void concatenate(char* args, char* path, char* a, char* b, char* c);

// Note: see descriptions for the functions in FatherSource.c