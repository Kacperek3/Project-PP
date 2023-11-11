#define _CRT_SECURE_NO_WARNINGS
#include "Libraries.h"



void menu();
void firstChoice();

void menu() {
	clrscr();
	printf("1 - New Game\n");
	printf("2 - Load Game\n");
	printf("3 - Hall of fame\n");
	printf("4 - Exit\n");
	printf(": ");
}

void firstChoice() {
	char zn;
	zn = getch();

	switch (zn)
	{
	case '1':
		newGame();
	default:
		break;
	}
}


int main() {
	settitle("Kacper,Sztuka,197918");

	menu();
	firstChoice();

	return 0;
}
