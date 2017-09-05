/*
	File:		libs\G6_lib.h
	Author:		GeaR_SiX
	Created:	2014
	Updated:	May, 2017
	C Version:	ANSI/C89
*/
/*	Notes:
	General library of functions I use when writing programs in C.
	See G6_lib.c for function-specific documentation.
	Currently windows-only (I think, haven't really tested on unix yet)
*/

#ifndef G6_GENERIC_LIB
#define G6_GENERIC_LIB

//================
// PRE-PROCESSORS
//================
//windows only
#ifdef _WIN32
	#include <Windows.h>
	
	#define sleep(x)	Sleep(1000*x)
//unix only
#elif __unix__
	#include <unistd.h>
#endif
//generic
#include <time.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_DIR_LENGTH	255
#define ISODD(x)		(x % 2)
#define ARRAYSIZE(x)	(sizeof(x) / sizeof((x)[0]))
#define INIT_ELEMENTS(x)

//===========
// FUNCTIONS
//===========
// Numbers

// Strings
void 		G6_chompString(char* string);

// Printing
void 		G6_printError(char *errorType, char* errorMessage);
void		G6_printDots(int pause, int numDots);
void 		G6_clearLine(int length);
void		G6_printTitle(char *title, char *version);

// 3. Input
void 		G6_clearStdin();
char 		G6_waitInput();
//
int			G6_getConfirmation(char* message);

//File Handling
bool 		G6_checkFileExists(char *filePath);
long 		G6_getFileLength(char *fileName);
char* 		G6_getFileData(char *fileName);
char*		G6_getTmpFileName();
//int			G6_countFiles(char *directory);
int			G6_getFileList(char *directory, char *filetype, char **bufferArray);

// Date & Time
struct tm* 	G6_getLocalDate();

#endif
