#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"conio2.h"

/* Comment: in the final program declare appropriate constants, e.g.,
   to eliminate from your program numerical values by replacing them
   with well defined identifiers */

int main() {
	settitle("Kacper,Sztuka,197918");

	// hide the blinking cursor
	_setcursortype(_NOCURSOR);
	gotoxy(2, 2);
	cputs("Game of GAMMON");
	clrscr();
	gotoxy(2, 3);
	cputs("Game of GAMMON");
	return 0;
}
