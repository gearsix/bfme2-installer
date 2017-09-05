/*
	File:		bfme2-installer.h
	Author:		GeaR_SiX
	Created:	May, 2017
	Updated:	September, 2017
*/
//================
// PRE-PROCESSORS
//=================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "libs\G6_lib.h"
#include "libs\G6_console.h"

#define GAME_TITLE				"Lord of the Rings: The Battle for Middle-Earth 2"

#define WINDOW_HEIGHT			24
#define WINDOW_WIDTH			69

#define MAX_MENU_ITEMS			5

#define BACKGROUND_COLOR		"black"
#define TEXT_COLOR				"dark yellow"
#define HIGHLIGHT_TEXT_COLOR	"bright yellow"

#define	EXIT					0		//regular return
#define EXIT_MENU				1		//return to previous menu
#define EXIT_PROGRAM			2		//exit program
#define EXIT_WAIT				3		//wait for user input before return

struct MENU {
	char *id;						//menu id
	int num_items;					//number of menu items
	char *items[MAX_MENU_ITEMS];	//actual menu items
};

//=====================
// FUNCTION PROTOTYPES
//=====================
int run_menu(struct MENU target_menu);
int run_script(char *game, char *script);
int about();
int help();

//==================
// GLOBAL VARIABLES
//==================
//different menus
struct MENU root;
struct MENU sub1;
struct MENU sub2;
//different menus data
void menu_data()
{	
	root.id = "main";
	root.num_items = 4;
	root.items[0] = "Battle For Middle-Earth 2  (base game)";
	root.items[1] = "The Rise of the Witch-King (expansion)";
	root.items[2] = "About\n";
	root.items[3] = "Exit";
	
	sub1.id = "sub1";
	sub1.num_items = 4;
	sub1.items[0] = "Install game";
	sub1.items[1] = "Apply crack";
	sub1.items[2] = "Uninstall\n";
	sub1.items[3] = "Back";
	
	sub2.id = "sub2";
	sub2.num_items = 4;
	sub2.items[0] = "Install expansion";
	sub2.items[1] = "Apply crack";
	sub2.items[2] = "Uninstall\n";
	sub2.items[3] = "Back";
}
//different menus functionality
int menu_functions(char *menu_id, int selection)
{
	if (strcmp(menu_id, "main") == 0)
	{
		switch(selection)
		{
			case 0:	return run_menu(sub1);		break;
			case 1: return run_menu(sub2);		break;
			case 2: return about();				break;
			case 3: return EXIT_PROGRAM;		break;
		}
	}
	else if (strcmp(menu_id, "sub1") == 0)
	{
		switch(selection)
		{
			case 0:	return run_script("bfme2", "install");		break;
			case 1: return run_script("bfme2", "crack");		break;
			case 2:	return run_script("bfme2", "uninstall");	break;
			case 3: return EXIT_MENU;							break;
		}
	}
	else if (strcmp(menu_id, "sub2") == 0)
	{
		switch(selection)
		{
			case 0:	return run_script("rotwk", "install");		break;
			case 1: return run_script("rotwk", "crack");		break;
			case 2:	return run_script("rotwk", "uninstall");	break;
			case 3: return EXIT_MENU;							break;
		}
	}
}

//===========
// FUNCTIONS
//===========
//runs a script from the scripts/ folder
int run_script(char *game, char *script)
{
	char *call_script = NULL;
	char curr_dir[MAX_DIR_LENGTH];
	GetCurrentDirectory(sizeof(curr_dir), curr_dir);
	
	call_script = (char *)malloc(250);
	
	//run powershell script
	sprintf(call_script, "PowerShell -NoLogo -ExecutionPolicy Bypass %s\\scripts\\%s.ps1 -target %s", curr_dir, script, game);
	system(call_script);
	
	free(call_script);
	
	sleep(2);
	return EXIT;
}

int about()
{
	printf("\t So this all started when two friends mentioned an\n");
	printf("\t old game they couldn't play anymore while we were\n");
	printf("\t at a pub.\n");
	printf("\t I had ISO files of said game but these friends aren't\n");
	printf("\t tech-savvy, so I decided I'd write an installation\n");
	printf("\t wrapper for them.\n");
	printf("\t AND DON'T ASK ABOUT THE PIRATE THEME :)\n");
	/*
	printf("\t So this all started when you two mentioned it\n");
	printf("\t in The Apple and I looked it up to see if there\n");
	printf("\t was a pirate version.\n");
	printf("\t I found one but it provided the game in .iso disk\n");
	printf("\t images and you had to copy over crack files to\n");
	printf("\t appdata, etc. I figured I'd save you guys the\n");
	printf("\t struggle and write a program to do it all for you.\n");
	printf("\n");
	printf("\t Happy 24th Nick\t\t~Alex");
	*/
	return EXIT_WAIT;
}