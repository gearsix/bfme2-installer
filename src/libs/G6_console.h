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

#ifndef G6_CONSOLE_LIB
#define G6_CONSOLE_LIB

//================
// PRE-PROCESSORS
//================
//windows only
#ifdef	_WIN32
	#include <Windows.h>
	#include <limits.h>
	
	#define sleep(x)	Sleep(1000*x)
//unix only
#elif	__unix__
	#include <unistd.h>
#endif
//generic
#include <stdio.h>
#include <stdlib.h>

//===========
// FUNCTIONS
//===========
// General
int G6c_clearScreen();

// Color
int G6c_color_setBackground(char *color);
int G6c_color_setText(char *color);
int G6c_color_invert();
int G6c_color_setDEFAULT(char *background, char *text);
int G6c_color_DEFAULT();
int G6c_color_hideText();
int G6c_color_unhideText();

// Window
int G6c_window_setTitle(char *TITLE);
int G6c_window_setSize(int height, int width);

#endif	//G6_CONSOLE_LIB