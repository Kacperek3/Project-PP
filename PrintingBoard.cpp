#include "Libraries.h"


void printN2(); //344 Funkcja z wygladem planszy (nie domyslna)
void printN1(); //344 Funkcja z wygladem planszy (domyslna)
void printP2(int t[][15]); // print Pawns 2 - wyswietl pionki (nie domyslna)
void printP1(int t[][15]); // print Pawns 1 - wyswietl pionki (domyslna)

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
}
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

}


void printP2(int t[][15]){
	int Fx =8; // First x
	int Fy =6; // First y
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 8; j++) {
			gotoxy(Fx, Fy);
			if (t[i][j] == 1)	putch('1');
			else if (t[i][j] == 2)	putch('2');
			else	putch('^');
			Fy++;
		}
		if (i == 5) {
			Fx += 13;
		}
		Fx+=5;
		Fy = 6;
	}
	Fx = 8;
	Fy = 26;
	for (int i = 23; i >= 12; i--) {
		for (int j = 0; j < 8; j++) {
			gotoxy(Fx, Fy);
			if (t[i][j] == 1)	putch('1');
			else if (t[i][j] == 2)	putch('2');
			else	putch('^');
			Fy--;
		}
		if (i == 18) {
			Fx += 13;
		}
		Fx += 5;
		Fy = 26;
	}
}

void printP1(int t[][15]){
	int Fx = 8; // First x
	int Fy = 6; // First y
	
	for (int i = 12; i < 24; i++) {
		for (int j = 0; j < 8; j++) {
			gotoxy(Fx, Fy);
			if (t[i][j] == 1) {
				textcolor(RED);
				putch('1');
				textcolor(WHITE);
			}
			else if (t[i][j] == 2) {
				textcolor(BLUE);
				putch('2');
				textcolor(WHITE);
			}
			else	putch('^');
			Fy++;
		}
		if (i == 17) {
			Fx += 13;
		}
		Fx += 5;
		Fy = 6;
	}
	Fx = 8;
	Fy = 26;
	for (int i = 11; i >= 0; i--) {
		for (int j = 0; j < 8; j++) {
			gotoxy(Fx, Fy);
			if (t[i][j] == 1) {
				textcolor(RED);
				putch('1');
				textcolor(WHITE);
			}
			else if (t[i][j] == 2) {
				textcolor(BLUE);
				putch('2');
				textcolor(WHITE);
			}
			else	putch('^');
			Fy--;
		}
		if (i == 6) {
			Fx += 13;
		}
		Fx += 5;
		Fy = 26;
	}
	textcolor(WHITE);
}

void printHittedPawns(int t[][15]) {
	int y = 18;
	
	for (int i = 0; i < 8; i++) {
		gotoxy(42, y);
		if (t[24][i] == Team2) {
			textcolor(BLUE);
			cputs("2");
			textcolor(WHITE);
		}
		y++;
	}

	y = 14;

	for (int i = 0; i < 8; i++) {
		gotoxy(42, y);
		if (t[25][i] == Team1) {
			textcolor(RED);
			cputs("1");
			textcolor(WHITE);
		}
		y--;
	}
}


void printB(int swap, int t[][15]) {
	gotoxy(1, 2);
	cputs("Game of BACKGAMMON");

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

	printHittedPawns(t);

	if (swap){
		printN2();
		printP2(t);
	}
		
	else {
		printN1();
		printP1(t);
	}
		

}//542 zmiana wygladu planszy