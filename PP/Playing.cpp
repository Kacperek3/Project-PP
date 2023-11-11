#include "Libraries.h"


void aToSpace(int [][15], int, int );
void rFSpace(int [][15], int);
int WhoStart(int);

void aToSpace(int t[][15], int index, int team) {
	for (int i = 0; i < 15; i++) {
		if (t[index][i] != 0) continue;
		else {
			t[index][i] = team;
			return;
		}
	}
} //add to space

void rFSpace(int t[][15], int index) {
	for (int i = 0; i < 14; i++) {
		if ((t[index][i] != 0) and (t[index][i + 1] == 0)) {
			t[index][i] = 0;
			return;
		}
	}
} // remove from space

int WhoStart() {
	srand((unsigned int)time(NULL));
	int number = rand() % 2;
	return number;
}
int randNumber() {
	static int initialized = 0;
	if (!initialized) {
		srand((unsigned int)time(NULL));
		initialized = 1;
	}
	int number = (rand() % 6) + 1;
	return number;
}
void play(int t[][15]){
	char b[4640];
	char n; char w;
	gettext(1, 1, 80, 27, b);
	clrscr();
	puttext(1, 1, 80, 27, b);
	gotoxy(35, 28);
	if (WhoStart() == 0) {
		cputs("Starts player 1 ");
	}
	if (WhoStart() == 1) {
		cputs("Starts player 2 ");
	}
	gotoxy(20, 29);
	printf("first dice: %d", randNumber());
	gotoxy(50, 29);
	printf("second dice: %d", randNumber());
	gotoxy(20, 30);
	printf("Which pawn to move:");
	n = getch();
	gotoxy(50, 30);
	printf("Where:");
	w = getch();

	rFSpace(t, int(int(n) - int('0') - 1));
	aToSpace(t, int(int(w) - int('0') - 1),1);
	Game(t);
}
