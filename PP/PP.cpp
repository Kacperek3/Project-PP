#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"conio2.h"

void printN2() {
	int x = 8;

	for (int i = 1; i <= 6; i++) {
		gotoxy(x, 4);
		printf("%d", i);
		x += 5;
	}
	x += 12;
	for (int i = 7; i <= 12; i++) {
		gotoxy(x, 4);
		printf("%d", i);
		x += 5;
	}
	x = 50;
	for (int i = 18; i >= 13; i--) {
		gotoxy(x, 28);
		printf("%d", i);
		x += 5;
	}
	x = 8;
	for (int i = 24; i >= 19; i--) {
		gotoxy(x, 28);
		printf("%d", i);
		x += 5;
	}
}//344


void printN1() {
	int x = 8;

	for (int i = 13; i <= 18; i++) {
		gotoxy(x, 4);
		printf("%d", i);
		x += 5;
	}
	x += 12;
	for (int i = 19; i <= 24; i++) {
		gotoxy(x, 4);
		printf("%d", i);
		x += 5;
	}
	x = 51;
	for (int i = 6; i >= 1; i--) {
		gotoxy(x, 28);
		printf("%d", i);
		x += 5;
	}
	x = 8;
	for (int i = 12; i >= 7; i--) {
		gotoxy(x, 28);
		printf("%d", i);
		x += 5;
	}
}//344

void printB(int swap) {
	gotoxy(8, 2);
	cputs("Game of BACKGAMMON");
	gotoxy(56, 2);
	cputs("SCORE: ");

	for (int i = 4; i <= 80; i++) {
		gotoxy(i, 5);
		putch('=');
	}

	for (int i = 6; i <= 26; i++) {
		gotoxy(4, i);
		putch('|');
		gotoxy(5, i);
		putch('|');

		gotoxy(37, i);
		putch('|');
		gotoxy(38, i);
		putch('|');

		gotoxy(46, i);
		putch('|');
		gotoxy(47, i);
		putch('|');

		gotoxy(79, i);
		putch('|');
		gotoxy(80, i);
		putch('|');

		gotoxy(41, 16);
		printf("BAR");
	}

	for (int i = 4; i <= 80; i++) {
		gotoxy(i, 27);
		putch('=');
	}
	if(swap)
		printN2();
	else
		printN1();
	
}//362

int main() {
	settitle("Kacper,Sztuka,197918");
	char zn;
	int swap = 0;

	do {
		zn = getch();

		if (zn == 's') {
			swap++;
			swap = swap % 2;
			clrscr();  // Czyszczenie ekranu, zakładam, że masz funkcję clrscr zdefiniowaną gdzieś indziej
			zn = ' ';
			printB(swap);  // Wywołanie funkcji printB z aktualną wartością swap
		}

	} while (zn != 'q');

	return 0;
}
