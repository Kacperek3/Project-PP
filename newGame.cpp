#include "Libraries.h"

void iniT(int t[][15]);
void menuNewGame() {
	gotoxy(10, 30);
	printf("m - move,  r - reverse the board, s - save the game, b - back to menu \n");
	printf(": ");
}

void menuGame() {
	gotoxy(10, 30);
	printf("m - next move,  r - reverse the board, s - save the game, b - back to menu \n");
	printf(": ");
}

void iniT(int t[][15]) {
	for (int i = 0; i < 24; i++) {
		for (int j = 0; j < 15; j++) {
			t[i][j] = 0;
		}
	}
	t[0][0] = t[0][1] = t[11][0] = t[11][1] = t[11][2] = t[11][3] = t[11][4] = t[16][0] = t[16][1] = t[16][2] = t[18][0] = t[18][1] = t[18][2] = t[18][3] = t[18][4] = Team1;
	t[23][0] = t[23][1] = t[12][0] = t[12][1] = t[12][2] = t[12][3] = t[12][4] = t[7][0] = t[7][1] = t[7][2] = t[5][0] = t[5][1] = t[5][2] = t[5][3] = t[5][4] = Team2;
}// Initialize tab

void newGame() {
	clrscr();
	char zn;
	int t[24][15];
	int reverse = 0;
	iniT(t);
	printB(0, t);
	menuNewGame();
	do {
		zn = getch();

		if (zn == 'm') {
			clrscr();
			playNewGame(t);
		}
		if (zn == 'r') {
			reverse++;
			reverse = reverse % 2;
			clrscr();
			zn = ' ';
			printB(reverse, t);
			menuNewGame();
		}
	} while (zn != 'q');
	return;
}

void Game(int t[][15], int team) {
	clrscr();
	char zn;
	int reverse = 0;
	printB(0, t);
	menuGame();
	do {
		zn = getch();
		if (zn == 'm') {
			playGame(t, (team % 2)+1);
		}
		if (zn == 'r') {
			reverse++;
			reverse = reverse % 2;
			clrscr();
			zn = ' ';
			printB(reverse, t);
			menuGame();
		}
	} while (zn != 'q');
	return;
}