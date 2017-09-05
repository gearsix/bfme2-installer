/*
	File:		libs\G6_console.h
	Author:		GeaR_SiX
	Created:	May, 2017
	Updated:	-
	C Version:	ANSI
*/
/*
	Notes:
		Found myself writing these functions while I was creating a install wrapper	for a
		friend (Lord of the Rings: The Battle For Middle-Earth 2). Decided that I should
		just write a library for it since most C programs I write have some kind of console
		interface.
*/


//================
// PRE-PROCESSORS
//================
#include "G6_console.h"

//============
// PROTOTYPES (INTERNAL)
//============
int setColor();
int convert_ColorStringToCode(char *color_string);

//===========
// VARIABLES
//===========
//color codes
enum COLOR_CODES {
	BLACK,			// 0
	DARK_BLUE,		// 1
	DARK_GREEN,		// 2
	DARK_CYAN,		// 3
	DARK_RED,		// 4
	DARK_PINK,		// 5
	DARK_YELLOW,	// 6
	BRIGHT_GREY,	// 7
	DARK_GREY,		// 8
	BRIGHT_BLUE,	// 9
	BRIGHT_GREEN,	//10
	BRIGHT_CYAN,	//11
	BRIGHT_RED,		//12
	BRIGHT_PINK,	//13
	BRIGHT_YELLOW,	//14
	WHITE			//15
};
//colors used when DEFAULT is called
int G6c_DEFAULT_TEXT = BRIGHT_GREY;
int G6c_DEFAULT_BACKGROUND = BLACK;
//text color
int G6c_PREV_TEXT_COLOR;
int G6c_TEXT_COLOR;
//background color
int G6c_BACKGROUND_COLOR;
//current color code of the console
int G6c_CONSOLE_COLOR = BRIGHT_GREY;

//====================
// EXTERNAL FUNCTIONS 
//====================
// General
int G6c_clearScreen()
{
#ifdef	_WIN32
	system("cls");
#elif	__unix__
	system("clear");
#endif
}

//Color
//set the text color
int G6c_color_setText(char *color)
{
	G6c_PREV_TEXT_COLOR = G6c_TEXT_COLOR;
	
	if (color != NULL)
		G6c_TEXT_COLOR = convert_ColorStringToCode(color);
	
	if (G6c_BACKGROUND_COLOR == BLACK)
		G6c_CONSOLE_COLOR = G6c_TEXT_COLOR;
	else
		G6c_CONSOLE_COLOR = G6c_TEXT_COLOR + ((15 * G6c_BACKGROUND_COLOR) + G6c_BACKGROUND_COLOR);
	
	setColor();
}
//set the background color
int G6c_color_setBackground(char *color)
{	
	if (color != NULL)
		G6c_BACKGROUND_COLOR = convert_ColorStringToCode(color);
	
	if (G6c_BACKGROUND_COLOR == BLACK)
		G6c_CONSOLE_COLOR = G6c_BACKGROUND_COLOR;
	else
		G6c_CONSOLE_COLOR = G6c_TEXT_COLOR + ((15 * G6c_BACKGROUND_COLOR) + G6c_BACKGROUND_COLOR);
	
	setColor();
}
//reverse the backround and text colors
int G6c_color_invert()
{
	int text = G6c_BACKGROUND_COLOR;
	int background = G6c_TEXT_COLOR;
	
	G6c_TEXT_COLOR = text;
	G6c_BACKGROUND_COLOR = background;
	
	G6c_color_setBackground(NULL);
	G6c_color_setText(NULL);
}
//
int G6c_color_setDEFAULT(char *background, char *text)
{
	G6c_DEFAULT_BACKGROUND = convert_ColorStringToCode(background);
	G6c_DEFAULT_TEXT = convert_ColorStringToCode(text);
}
//
int G6c_color_DEFAULT()
{
	G6c_BACKGROUND_COLOR = G6c_DEFAULT_BACKGROUND;
	G6c_PREV_TEXT_COLOR = G6c_TEXT_COLOR;
	G6c_TEXT_COLOR = G6c_DEFAULT_TEXT;
	G6c_color_setBackground(NULL);
	G6c_color_setText(NULL);
}

int G6c_color_hideText()
{
	G6c_PREV_TEXT_COLOR = G6c_TEXT_COLOR;
	G6c_TEXT_COLOR = G6c_BACKGROUND_COLOR;
	G6c_color_setText(NULL);
}

int G6c_color_unhideText()
{
	G6c_TEXT_COLOR = G6c_PREV_TEXT_COLOR;
	G6c_color_setText(NULL);
}

// Window
int G6c_window_setTitle(char *TITLE)
{
	char set_title[100];
	
	sprintf(set_title, "title %s", TITLE);
	
	system(set_title);
}
int G6c_window_setSize(int height, int width)
{
	char *setSize = malloc(30);
#ifdef _WIN32
	sprintf(setSize, "mode con: cols=%i lines=%i", width, height);
#elif __unix__
#endif
	system(setSize);
}

//====================
// INTERNAL FUNCTIONS 
//====================
int setColor()
{
#ifdef _WIN32
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(consoleHandle, G6c_CONSOLE_COLOR);
#elif __unix__
	//?
#endif
}

int convert_ColorStringToCode(char *color_string)
{
	int color_code;
		
	if (strcmp(color_string, "black") == 0)
		color_code = BLACK;
	else if (strcmp(color_string, "dark blue") == 0)
		color_code = DARK_BLUE;
	else if (strcmp(color_string, "dark green") == 0)
		color_code = DARK_GREEN;
	else if (strcmp(color_string, "dark cyan") == 0)
		color_code = DARK_CYAN;
	else if (strcmp(color_string, "dark red") == 0)
		color_code = DARK_RED;
	else if (strcmp(color_string, "dark pink") == 0)
		color_code = DARK_PINK;
	else if (strcmp(color_string, "dark yellow") == 0)
		color_code = DARK_YELLOW;
	else if (strcmp(color_string, "dark grey") == 0)
		color_code = DARK_GREY;
	else if (strcmp(color_string, "bright grey") == 0)
		color_code = BRIGHT_GREY;
	else if (strcmp(color_string, "bright blue") == 0)
		color_code = BRIGHT_BLUE;
	else if (strcmp(color_string, "bright green") == 0)
		color_code = BRIGHT_GREEN;
	else if (strcmp(color_string, "bright cyan") == 0)
		color_code = BRIGHT_CYAN;
	else if (strcmp(color_string, "bright red") == 0)
		color_code = BRIGHT_RED;
	else if (strcmp(color_string, "bright pink") == 0)
		color_code = BRIGHT_PINK;
	else if (strcmp(color_string, "bright yellow") == 0)
		color_code = BRIGHT_YELLOW;
	else if (strcmp(color_string, "white") == 0)
		color_code = WHITE;

	
	return color_code;
}
