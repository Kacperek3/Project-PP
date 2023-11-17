#include "Libraries.h"






void aToSpace(int [][15], int, int );
void rFSpace(int [][15], int);
int isEmpty(int t[][15], int);
void intro(int, int);
int WhoStart();
void howManyMovesW(int t[][15], int team, int index, int dice1, int dice2, int w, int number, int secret = 0);
//-------------------------------------------------------
void aToSpace(int t[][15], int index, int team) {
	index--;
	for (int i = 0; i < 15; i++) {
		if (t[index][i] != 0) continue;
		else {
			t[index][i] = team;
			return;
		}
	}
} //add to space

void rFSpace(int t[][15], int index) {
	index--;
	for (int i = 0; i < 14; i++) {
		if ((t[index][i] != 0) and (t[index][i + 1] == 0)) {
			t[index][i] = 0;
			return;
		}
	}
} // remove from space

int isEmpty(int t[][15], int index) {
	for (int i = 0; i < 15; i++) {
		if (t[index][i] != 0) return 0;
	}
	return 1;
} // is empty, if it return 1

int isAttacking(int t[][15], int w, int team) {
	
	int sumInCol = 0;
	int teamInColumn = 0;
	for (int i = 0; i < 15; i++) {
		if (t[w][i] != 0) {
			sumInCol++;
			teamInColumn = t[w][i];
		}
	}
	//std::cout << std::endl <<w << sumInCol << " " << teamInColumn;
	if (sumInCol == 1 and teamInColumn != team) return 1;
	return 0;
}

int isTeam(int t[][15], int index, int team) {
	
	for (int i = 0; i < 15; i++) {
		if ((t[index][i] != 0 and t[index][i] != team) or isEmpty(t,index)) return 0;
	}
	return 1;
} // is team on the field, if it return 1, if a column is empty it return 0

int isTeamW(int t[][15], int index, int team) {

	for (int i = 0; i < 15; i++) {
		if ((t[index][i] != 0 and t[index][i] != team)) return 0;
	}
	return 1;
} // is team on the field, if it return 1, if a column is empty it return 0

//-------------------------------------------------------
int correctMoveW(int team, int index, int dice1, int dice2, int w, int banned) {
	if (w-index == banned or index - w == banned) return 0;
	// zapobiegniêcie pojechania na zsumowane pole dwóch kostek je¿eli ju¿ wczeœniej wykonana zosta³a operacja przeniesienia pionka o dan¹ kostkê
	if (dice1 == banned) dice1 = 0;
	else if (dice2 == banned) dice2 = 0;
	//
	if (team == 1) {
		if (index + dice1 == w or index + dice2 == w or index + dice1 + dice2 == w) return 1;
		else return 0;
	}
	else {
		if (index - dice1 == w or index - dice2 == w or index -(dice1 + dice2) == w) return 1;
		else return 0;
	}
}

int countingW(int team, int index, int dice1, int dice2, int w) {
	if (team == 1) {
		if (index + dice1 == w) return dice1;
		if (index + dice2 == w) return dice2;
		if (index + dice1 + dice2 == w) return dice1 + dice2;
	}
	else {
		if (index - dice1 == w) return dice1;
		if (index - dice2 == w) return dice2;
		if (index - dice1 - dice2 == w) return dice1 + dice2;
	}
} 


int WhoStart() {
	srand((unsigned int)time(NULL));
	int number = (rand() % 2) +1;
	
	if (number == 1) {
		cputs("Starts player 1 ");
	}
	if (number == 2) {
		cputs("Starts player 2 ");
	}
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
void menuBoard(int t[][15], int team, int sum, int number, int dice1, int dice2) {
	clrscr();
	printB(0, t);
	gotoxy(95, 14);
	if (team == 1) {
		cputs("Player 1 move");
	}
	if (team == 2) {
		cputs("Player 2 move");
	}
	gotoxy(96, 16);
	printf("moves left: %d", sum - number);
	gotoxy(85, 18);
	printf("Type 'u' to undo the entered move");
	intro(dice1, dice2);
	gotoxy(56, 30);
}

int cinN() {
	char a[2];
	int convertedInt = 25;
	int t = 0;
	do {
		gotoxy(39, 30);
		printf("__");
		gotoxy(39, 30);
		a[0] = getch();
		printf("%c", a[0]);
		if (isdigit(a[0])) {
			a[1] = getch();
			printf("%c", a[1]);
			if (!isdigit(a[1])) {
				a[1] = 'x';
			}
		}
		else {
			return 0;
		}
		convertedInt = int(a[0] - '0');

		if (isdigit(a[1])) {
			convertedInt = ((a[0] - '0') * 10) + (a[1] - '0');
		}
	} while (convertedInt > 24);
	return convertedInt;
}
void validateN(int t[][15], int team, int *n) {
	do {
		printf("__");
		*n = cinN();
		gotoxy(39, 30);
	} while (n == 0 or isTeam(t, *n - 1, team) == 0);
	printf("%d", *n);
}

int cinW() {
	char a[2];
	int convertedInt = 25;
	int t = 0;
	do {
		gotoxy(56, 30);
		printf("__");
		gotoxy(56, 30);
		a[0] = getch();
		if (a[0] == 'u') {
			return 30;
		}
		printf("%c", a[0]);
		if (isdigit(a[0])) {
			a[1] = getch();
			if (a[1] == 'u') {
				return 30;
			}
			printf("%c", a[1]);
			if (!isdigit(a[1])) {
				a[1] = 'x';
			}
		}
		else {
			return 0;
		}
		convertedInt = int(a[0] - '0');

		if (isdigit(a[1])) {
			convertedInt = ((a[0] - '0') * 10) + (a[1] - '0');
		}
	} while (convertedInt > 24);
	return convertedInt;
}

int validateW(int t[][15], int team, int* w, int index, int dice1, int dice2,int number, int banned = 0) {
	int ban = 0;
	do {
		*w = cinW();
		if (*w == 30) {
			if (banned == dice1) {
				howManyMovesW(t, team, index, 0, dice2, *w, 0);
				Game(t, team);
				return 0;
			}
			else if (banned == dice2) {
				howManyMovesW(t, team, index, dice1, 0, *w, 0);
				Game(t, team);
				return 0;
			}
			else {
				howManyMovesW(t, team, index, dice1, dice2, *w, number , sameDice); // last parametr is only when the 2 dices are equal, set to 1
				Game(t, team);
				return 0;
			}
		}
		if (team == 1) {
			if (index + dice1 == *w) ban = dice1;
			else if (index + dice2 == *w) ban = dice2;
		}
		else {
			if (index - dice1 == *w) ban = dice1;
			else if (index - dice2 == *w) ban = dice2;
		}
		
		gotoxy(56, 30);
		if (isAttacking(t, *w - 1, team) == 1 and correctMoveW(team, index, dice1, dice2, *w, banned) == 1){
			rFSpace(t, *w);
			break;
		}

	} while (w == 0 or isTeamW(t, *w - 1, team) == 0 or correctMoveW(team, index, dice1, dice2, *w, banned) == 0);
	return ban;
}


void howManyMovesW(int t[][15], int team, int index, int dice1, int dice2, int w, int number, int secret) {
	int banned = 0;
	int sum = dice1 + dice2;

	if (dice1 == dice2) sum *= 2;
	
	menuBoard(t, team, sum, number, dice1, dice2);
	do {
		validateN(t, team, &index);
		if (dice1 == dice2)	validateW(t, team, &w, index, dice1, dice2, number);
		else banned = validateW(t, team, &w, index, dice1, dice2,number, banned);
		number += countingW(team, index, dice1, dice2, w);
		rFSpace(t, index);
		aToSpace(t, w, team);
		menuBoard(t, team, sum, number, dice1, dice2);
	} while (number != sum);
}

void intro(int rand1, int rand2) {
	gotoxy(20, 29);
	printf("first dice: %d", rand1);
	gotoxy(50, 29);
	printf("second dice: %d", rand2);
	gotoxy(20, 30);
	printf("Which pawn to move:");
	gotoxy(50, 30);
	printf("Where:");
}

void playNewGame(int t[][15]){
	int number = 0;
	int n = 0; int w = 0;
	int rand1 = randNumber();
	int rand2 = randNumber();
	printB(0, t);
	gotoxy(35, 28);
	int whoStarts = WhoStart();
	intro(rand1,rand2);
	howManyMovesW(t, whoStarts, n, rand1, rand2, w, number);
	Game(t, whoStarts);
}

void playGame(int t[][15], int team) {
	int number = 0;
	int n = 0; int w = 0;
	int rand1 = randNumber();
	int rand2 = randNumber();
	clrscr();
	printB(0, t);
	gotoxy(35, 28);
	intro(rand1, rand2);
	howManyMovesW(t, team, n, rand1, rand2, w, number);
	Game(t, team);
}
