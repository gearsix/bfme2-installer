/*
	File:		libs\G6_lib.c
	Author:		GeaR_SiX
	Created:	2014
	Updated:	May, 2017
	C Version:	ANSI/89
*/
/*	Notes:
	See G6_lib.h for more general information on the library.
	Documentation in this file is specific to function implementation.
*/

//================
// PRE-PROCESSORS
//================
#include "G6_lib.h"

//===========
// FUNCTIONS
//===========
//	1. Numbers

//	2. Inputs
//Discard all characters waiting in the input stream (stdin)
void G6_clearStdin() {
	//DOC
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

//Removes \n or \r from the end of the specified char*
void G6_chompString(char* string) {
	//set index to the end of the string (-1 for null terminator ('\0')
	int index = strlen(string) - 1;
	//null out any '\n' or '\r' at index
	if (index >= 0 && ((string[index] == '\n') || (string[index] == '\r')))
		string[index] = '\0';
}

//Clears the input buffer & waits for user to enter any input (use to pause program)
char G6_waitInput() {
	G6_clearStdin();
	return getchar();
}

//Gets a 'y' or 'n' from user after printing message (use for generic y/n confirmations)
int	G6_getConfirmation(char* message) {
	printf ("%s", message);
	char input = G6_waitInput();
	switch (input)
	{	
		case 'n':	return false;
		case 'y':	return true;
		default:	return -1;	//invalid input
	}
}

//Returns a tmpnam() without special characters so that the filename can be used by systems
char* G6_getTmpFileName() {
	//create buffer && assign tmpnam
	char *buffer = malloc(5);
	tmpnam(buffer);
	
	//parse name & replace anything that's not alphanumerica with 'a'
	int i;
	for (i = 0; i < strlen(buffer); i++)
	{
		if (!isalnum(buffer[i]))
			buffer[i] = 'a';
	}
	
	return buffer;
}

// 3. Strings

// 4. Printing

// 5. Time & Date

// 6. File Handling

// Input


/*	--------
	Printing
	--------	*/
//Prints an error message & waits for input
void G6_printError(char *errorType, char* errorMessage) {
	printf ("\n%s Error: %s", errorType, errorMessage);
	G6_waitInput();
}
//Clears current line of text printed on the console
void G6_clearLine(int length) {
	int i;
	for (i = 0; i < length; i++)
		printf("\b \b");
}
//Prints '.'s, with a specified pause between each print
void G6_printDots(int pause, int numDots) {
	int i;
	for (i = 0; i < numDots; i++)
	{	
		putchar('.');
		sleep (pause);
	}
}
//Prints title & version in signature style
	//output e.g.:
	//	/-------------\
	//	| TITLE, v1.0 |
	//	\-------------/
/*
void G6_printTitle(char *title, char *version) {
	
	#ifdef _WIN32
		snprintf(systemCall, length, "dir %s /b > %s", directory, tmpFile);
	#elif __unix__
		snprintf(systemCall, length, "ls %s > %s", directory, tmpFile);
	#endif
	
	int titleLength = 1 + strlen(title) + 3 + strlen(version) + 1;	//<space>TITLE<,><space><v>VERSION<space>
	//G6_chompString(fullTitle);
	
	//line 1
	printf ("/");
	for (int i = 0; i < titleLength; i++)
		putchar ('-');
	printf ("\\\n");
	//line 2
	printf ("|");
	printf (" %s, v%s ", title, version);
	printf ("|\n");
	//line 3
	printf ("\\");
	for (int i = 0; i < titleLength; i++)
		putchar ('-');
	printf( "/\n");
}
*/
/*	-----------
	Date & Time
	-----------	*/
//Returns current date (using local time)
struct tm* G6_getLocalDate() {
	time_t rawtime 	= time(NULL);			//rawtime
	struct tm *date	= localtime(&rawtime);	//get local date from rawtime
	date->tm_year	+= 1900;				//add year offset
	date->tm_mon	+= 1;					//add month offset
	
	return date;
}

/*	-------------
	File Handling
	-------------	*/
//Checks if a file exists
bool G6_checkFileExists(char* filePath) {
	//try open file
	FILE* file = fopen(filePath, "r");
	//exists = did file open?
	bool exists = (!file)? false : true;
	//close file
	fclose(file);
	
	return exists;
}
//Opens file "fileName" and returns the length of the file, -1 if fileName could not be opened
long G6_getFileLength(char* fileName) {
	int length;
	
	//open file 
	FILE *file = fopen(fileName, "r");
	
	//error, file doesn't exists
	if (file == NULL)
		return -1;
	//set cursor to end of file & get position
	else
	{
		fseek(file, 0, SEEK_END);
		length = ftell(file);
	}
	
	//close file && return length (+1 for '\0')
	fclose(file);
	return length +1;
}
//Opens file "fileName" and returns it's contents as a char*
char* G6_getFileData(char* fileName) {
	//get file length, create buffer && open file
	long length = G6_getFileLength(fileName);
	char* buffer = malloc(length);
	FILE *file = fopen(fileName, "r");
	
	//if file exists
	if (G6_checkFileExists(fileName))
	{	//read file data to buffer
		if (buffer)
			fread(buffer, 1, length, file);
		//close file && terminate buffer
		fclose(file);
		buffer[length] = '\0';
	}
	else
		buffer = NULL;
		
	return buffer;
}
//fills bufferArray with the names of files in directory, filetype specified the type of files to list (all if NULL)
int G6_getFileList(char* directory, char *filetype, char **bufferArray) {
	//create tmpfile name && systemcall
	char *tmpFile = G6_getTmpFileName();
	int length = 20 + strlen(directory) + strlen(tmpFile);
	char *systemCall = malloc(length);
	
	#ifdef _WIN32
		snprintf(systemCall, length, "dir %s /b > %s", directory, tmpFile);
	#elif __unix__
		snprintf(systemCall, length, "ls %s > %s", directory, tmpFile);
	#endif
	
	//make systemcall
	system(systemCall);
	//extract systemcall data
	char *fileList = G6_getFileData(tmpFile);
	//remove tmpfile
	remove(tmpFile);
	
	//get files of filetype (NULL == get all)
	int index = 0;
	if (filetype == NULL) {
		bufferArray[index] = strtok(fileList, "\n");
		while (bufferArray[index] != NULL)
		{
			bufferArray[index] = strtok(NULL, "\n");
			index++;
		}
	}
	else
		printf("def");
	
	return index;
	/*
	//if no filetype is specified, get all files in list
	if (filetype == NULL)
	{
		while (bufferArray[index] != NULL)
		{
			bufferArray[index] = strtok(NULL, "\n");
			index++;
		}
	}
	//else only get the specified filetype files in list
	else
	{
		char *file;
		if (G6_getFiletype(bufferArray[index]) == filetype)
			index++;
		while (file != NULL)
		{
			file = strtok(NULL, "\n");
			int j = 0;
			for (int i = 0; i < strlen(file); i++)
			{
				if (file[i] == filetype[i])
					j++;
				else
					j = 0;
			}
			
			if (strlen(filetype) == j)
				bufferArray[index] = file;
			
			index++;
		}
	}
	*/
}
