/*
	File:		bfme2-installer.h
	Author:		GeaR_SiX
	Created:	May, 2017
	Updated:	September, 2017
*/
//================
// PRE-PROCESSORS
//================
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bfme2-installer.h"
#include "libs\G6_lib.h"
#include "libs\G6_console.h"

//=====================
// FUNCTION PROTOTYPES
//=====================
void animate_logo(char *E);
void print_logo();
void print_menu();

//======
// MAIN
//======
int main()
{
	int exit_code;
	
	//initialise menu data
	menu_data();	//see bfme2-installer.h
	//set console window attributes
	G6c_window_setTitle(GAME_TITLE);
	G6c_window_setSize(WINDOW_HEIGHT, WINDOW_WIDTH);
	G6c_color_setDEFAULT(BACKGROUND_COLOR, TEXT_COLOR);
	//start
	animate_logo("entrance");
	//main loop
	do
	{	exit_code = run_menu(root);
	} while (exit_code != EXIT_PROGRAM);
	//exit
	animate_logo("exit");	
	
	return 0;
}

//===========
// FUNCTIONS
//===========
//int run_menu()
//prints target_menu and gets user input to make a selection
int run_menu(struct MENU target_menu)
{
	int exit_code;
	bool selected;
	int selection;
	
	START:
	//init values
	selection = 0;
	selected = false;
	//reset VK_RETURN keystate
	GetAsyncKeyState(VK_RETURN);
	//get user selection
	print_menu(selection, target_menu);
	while (!selected)
	{
		if (GetAsyncKeyState(VK_RETURN) & SHRT_MAX)
		{
			selected = true;
		}
		else if (GetAsyncKeyState(VK_UP) & SHRT_MAX)
		{
			if (selection > 0)
				selection--;
			print_menu(selection, target_menu);
		}
		else if (GetAsyncKeyState(VK_DOWN) & SHRT_MAX)
		{
			if (selection < target_menu.num_items-1)
				selection++;
			print_menu(selection, target_menu);
		}
	}
		
	print_logo();
	G6c_color_setText(HIGHLIGHT_TEXT_COLOR);
	
	exit_code = menu_functions(target_menu.id, selection);	//see bfme2-installer.h
	G6c_color_DEFAULT();
	
	switch (exit_code)
	{
		case EXIT_MENU:
			G6_clearStdin();
		case EXIT_PROGRAM:
			return exit_code;
		case EXIT_WAIT:
			G6c_color_hideText();
			G6_waitInput();
			G6c_color_unhideText();
			goto START;
		case EXIT:
			G6_clearStdin();
		default:
			goto START;
	}
}

//print functions
void print_menu(int selected, struct MENU target_menu)
{
	print_logo();
	printf("\t  <UP/DOWN ARROW> = Navigate\t<ENTER> = Select\n");
	printf("\n");
	
	int i;
	for (i = 0; i < target_menu.num_items; i++)
	{
		if (i == selected)
		{
			printf("\t  ");
			G6c_color_setText(HIGHLIGHT_TEXT_COLOR);
			printf("%s\n", target_menu.items[selected]);
			G6c_color_DEFAULT();
		}
		else
			printf("\t  %s\n", target_menu.items[i]);
	}
}

void print_logo()
{
	G6c_clearScreen();
	printf("\n");
	
	/*
	printf("\t/==================================================\\\n");
	printf("\t| %s |\n", GAME_TITLE);
	printf("\t\\==================================================/\n");
	printf("\t|                         _~                       |\n");
	printf("\t|                     _~ )_)_~                     |\n");
	printf("\t|                     )_))_))_)                    |\n");
	printf("\t|                     _|__|__|_                    |\n");
	printf("\t|                     \\_______/                    |\n");
	printf("\t| ~~~~~~~~~~~~~~~~~~~~*********~~~~~~~~~~~~~~~~~~~ |\n");
	printf("\t|           bfme2-installer (By GeaRSiX)           |\n");
	printf("\t| ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ |\n");
	printf("\t\\==================================================/\n");
	*/
	G6c_color_DEFAULT();
	printf("\t/==================================================\\\n");
	printf("\t| ");
	G6c_color_setText(HIGHLIGHT_TEXT_COLOR);
	printf("%s", GAME_TITLE);
	G6c_color_DEFAULT();
	printf(" |\n");
	printf("\t\\==================================================/\n");
	printf("\t|                         ");
	G6c_color_setText("white");
	printf("_~");
	G6c_color_DEFAULT();
	printf("                       |\n");
	printf("\t|                     ");
	G6c_color_setText("white");
	printf("_~ )_)_~");
	G6c_color_DEFAULT();
	printf("                     |\n");
	printf("\t|                     ");
	G6c_color_setText("white");
	printf(")_))_))_)");
	G6c_color_DEFAULT();
	printf("                    |\n");
	printf("\t|                     ");
	G6c_color_setText("dark yellow");
	printf("_|__|__|_");
	G6c_color_DEFAULT();
	printf("                    |\n");
	printf("\t|                     ");
	G6c_color_setText("dark yellow");
	printf("\\_______/");
	G6c_color_DEFAULT();
	printf("                    |\n");
	printf("\t| ");
	G6c_color_setText("dark cyan");
	printf("~~~~~~~~~~~~~~~~~~~~");
	G6c_color_setText("bright cyan");
	printf("*********");
	G6c_color_setText("dark cyan");
	printf("~~~~~~~~~~~~~~~~~~~");
	G6c_color_DEFAULT();
	printf(" |\n");
	printf("\t| ");
	G6c_color_setBackground("dark blue");
	G6c_color_setText("bright cyan");
	printf("          bfme2-installer (By GeaRSiX)          ");
	G6c_color_DEFAULT();
	printf(" |\n");
	printf("\t| ");
	G6c_color_setBackground("dark blue");
	G6c_color_setText("dark cyan");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	G6c_color_DEFAULT();
	printf(" |\n");
	printf("\t\\==================================================/\n");
	
	printf("\n");
}

void animate_logo(char* E)
{
	int frame = 0, row, i;
	int max_frames = 37;
	int animated_rows = 6;
	
	if (E == "entrance")
	{
		max_frames /= 2;
	}
	else if (E == "exit")
	{
		frame += (max_frames / 2);
	}
	
	for (; frame <= max_frames; frame++)
	{
		G6c_clearScreen();
		printf("\n");
		printf("\t/==================================================\\\n");
		printf("\t| ");
		G6c_color_setText(HIGHLIGHT_TEXT_COLOR);
		printf("%s", GAME_TITLE);
		G6c_color_DEFAULT();
		printf(" |\n");
		printf("\t\\==================================================/\n");
			
		for (row = 0; row < animated_rows; row++)
		{
			printf("\t| ");
			switch (row)
			{
				case 0:
					for (i = 0; i < (5 + frame); i++)
						printf(" ");
					G6c_color_setText("white");
					printf ("_~");
					G6c_color_DEFAULT();
					for (i = 0; i < (41 - frame); i++)
						printf(" ");
					break;
				case 1:
					for (i = 0; i < (1 + frame); i++)
						printf(" ");
					G6c_color_setText("white");
					printf("_~ )_)_~");
					G6c_color_DEFAULT();
					for (i = 0; i < (39 - frame); i++)
						printf(" ");
					break;
				case 2:
					for (i = 0; i < (1 + frame); i++)
						printf(" ");
					G6c_color_setText("white");
					printf(")_))_))_)");
					G6c_color_DEFAULT();
					for (i = 0; i < (38 - frame); i++)
						printf(" ");
					break;
				case 3:
					for (i = 0; i < (1 + frame); i++)
						printf(" ");
					G6c_color_setText("dark yellow");
					printf("_|__|__|_");
					G6c_color_DEFAULT();
					for (i = 0; i < (38 - frame); i++)
						printf(" ");	
					break;
				case 4:
					for (i = 0; i < (1 + frame); i++)
						printf(" ");
					G6c_color_setText("dark yellow");
					printf("\\_______/");
					G6c_color_DEFAULT();
					for (i = 0; i < (38 - frame); i++)
						printf(" ");
					break;
				case 5:
					G6c_color_setText("dark cyan");
					for (i = 0; i < (1 + frame); i++)
						printf("~");
					G6c_color_setText("bright cyan");
					printf("*********");
					G6c_color_setText("dark cyan");
					for (i = 0; i < (38 - frame); i++)
						printf("~");
					G6c_color_DEFAULT();
					break;
			}
			printf(" |\n");
		}
		printf("\t| ");
		G6c_color_setBackground("dark blue");
		G6c_color_setText("bright cyan");
		printf("          bfme2-installer (By GeaRSiX)          ");
		G6c_color_DEFAULT();
		printf(" |\n");
		printf("\t| ");
		G6c_color_setBackground("dark blue");
		G6c_color_setText("dark cyan");
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		G6c_color_DEFAULT();
		printf(" |\n");
		printf("\t\\==================================================/\n");
		printf("\n");
	}
}
