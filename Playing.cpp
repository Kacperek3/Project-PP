#include "Libraries.h"






void aToSpace(int [][15], int, int );
void rFSpace(int [][15], int);
int isEmpty(int t[][15], int);
void intro(int, int);
int WhoStart();
void howManyMovesW(int t[][15], int team, int index, int dice1, int dice2, int w, int number,int *hitted, int secret = 0);
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
	if (sumInCol == 1 and teamInColumn != team) return 1;
	return 0;
}

int isTeam(int t[][15], int index, int team) {
	
	for (int i = 0; i < 15; i++) {
		if ((t[index][i] != 0 and t[index][i] != team) or isEmpty(t,index)) return 0;
	}
	return 1;
} // is team on the field, if it return 1, if a column is empty it return 0, dont forget when you call this function about decrease parameter

int isTeamOrEmpty(int t[][15], int index, int team) {
	index--;
	if (index == 24 or index == 25) return 0;
	if (isEmpty(t, index)) return 1;
	for (int i = 0; i < 15; i++) {
		if (t[index][i] != 0 and t[index][i] != team) return 0;
	}
	return 1;
} // is team on the field, if it return 1, if a column is empty it return also 1

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

void menuRemovingPawn() {
	gotoxy(90, 9);
	printf("in 'where' write 0 to");
	gotoxy(96, 10);
	printf("remove pawn");
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


int isAllHome1(int t[][15]) {
	int numberPawn = 0;
	int num = 0;
	for (int i = 0; i < 24; i++) {
		for (int j = 0; j < 15; j++) {
			if (t[i][j] == 1) numberPawn++;
		}
	}

	for (int i = 18; i < 24; i++) {
		for (int j = 0; j < 15; j++) {
			if (t[i][j] == 1) num++;
		}
	}
	if (num == numberPawn) return 1;
	return 0;
}
int isAllHome2(int t[][15]) {
	int numberPawn = 0;
	int num = 0;

	for (int i = 0; i < 24; i++) {
		for (int j = 0; j < 15; j++) {
			if (t[i][j] == 2) numberPawn++;
		}
	}

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 15; j++) {
			if (t[i][j] == 2) num++;
		}
	}
	if (num == numberPawn) return 1;
	return 0;
}
int closestPawn1(int t[][15], int dice, int team) {
	int nrIndex;
	for (int i = 18; i < 24;i++) {
		if (t[i][0] == team) {
			nrIndex = i;
			return nrIndex;
		}
	}
	return 0;
}
int closestPawn2(int t[][15], int dice, int team) {
	int nrIndex;
	for (int i = 5; i >= 0; i--) {
		if (t[i][0] == team) {
			nrIndex = i;
			return nrIndex;
		}
	}
	return 0;
}
int isPossibleMove1(int t[][15], int dice1, int dice2, int banned) {
	for (int i = 0; i < 24; i++) {
		if (t[i][0] == Team1) {
			if (dice1 == 0) {
				if (isTeamOrEmpty(t, i + dice2 + 1, Team1) or isAttacking(t, i + dice2, Team1)) return 1;
			}
			else if (dice2 == 0) {
				if (isTeamOrEmpty(t, i + dice1 + 1, Team1) or isAttacking(t, i + dice1, Team1)) return 1;
			}
			else {
				if (isTeamOrEmpty(t, i + dice1 + 1, Team1) or isAttacking(t, i + dice1, Team1) or isTeamOrEmpty(t, i + dice2 + 1, Team1) or isAttacking(t, i + dice2, Team1)) return 1;
				if (isAllHome1(t)) {
					if (25 - i == dice1 or 25 - i == dice2) return 1;
					if (25 - (i + 1) < dice1 and banned != dice1) return 1;
					if (25 - (i + 1) < dice2 and banned != dice2) return 1;
				}
			}
		}
	}
	return 0;
}
int isPossibleMove2(int t[][15], int dice1, int dice2, int banned) {
	for (int i = 0; i < 24; i++) {
		if (t[i][0] == Team2) {
			if (dice1 == 0) {
				if (isTeamOrEmpty(t, i - dice2 + 1, Team2) or isAttacking(t, i - dice2, Team2)) return 1;
			}
			else if (dice2 == 0) {
				if (isTeamOrEmpty(t, i - dice1 + 1, Team2) or isAttacking(t, i - dice1, Team2)) return 1;
			}
			else {
				if (isTeamOrEmpty(t, i - dice1 + 1, Team2) or isAttacking(t, i - dice1, Team2) or isTeamOrEmpty(t, i - dice2 + 1, Team2) or isAttacking(t, i - dice2, Team2)) return 1;
				if (isAllHome2(t)) {
					if (i + 1 == dice1 or i + 1 == dice2) return 1;
					if (i + 1 < dice1 and banned != dice1) return 1;
					if (i + 1 < dice2 and banned != dice2) return 1;
				}
			}
		}
	}
	return 0;
}



int validateW(int t[][15], int team, int* w, int *index, int dice1, int dice2,int number,int *hitted, int banned = 0) {
	int ban = 0;

	do {
		if (isAllHome1(t) and team == Team1) {
			menuRemovingPawn();
		}
		else if (isAllHome2(t) and team == Team2) {
			menuRemovingPawn();
		}

		*w = cinW();


		if (isAllHome1(t) and team == Team1) {
			int x = closestPawn1(t, dice1, Team1) + 1;
			if (25 - *index == dice1 and banned != dice1) {
				if (*w == 0) {
					rFSpace(t, *index);
					clrscr();
					printB(0, t);
					*w = 25;
					return dice1;
				}
			}
			else if (25 - *index < dice1 and *index == x and banned != dice1) {
				if (*w == 0) {
					rFSpace(t, x);
					clrscr();
					printB(0, t);
					*w = 25;
					*index = 25 - dice1;
					return dice1;
				}
			}
			else if (25 - *index == dice2 and banned != dice2) {
				if (*w == 0) {
					rFSpace(t, *index);
					clrscr();
					printB(0, t);
					*w = 25;
					return dice2;
				}
			}
			else if (25 - *index < dice2 and *index == x and banned != dice2) {
				if (*w == 0) {
					rFSpace(t, x);
					clrscr();
					printB(0, t);
					*index = 25 - dice2;
					*w = 25;
					return dice2;
				}
			}
		}


		else if (isAllHome2(t)) {
			int x = closestPawn2(t, dice1, Team2) + 1;
			if (*index == dice1 and banned != dice1) {
				if (*w == 0) {
					rFSpace(t, *index);
					clrscr();
					printB(0, t);
					*w = 0;
					return dice1;
				}
			}
			else if (*index < dice1 and *index == x and banned != dice1) {
				if (*w == 0) {
					rFSpace(t, x);
					clrscr();
					printB(0, t);
					*w = 0;
					*index = dice1;
					return dice1;
				}
			}
			else if (*index == dice2 and banned != dice2) {
				if (*w == 0) {
					rFSpace(t, *index);
					clrscr();
					printB(0, t);
					*w = 0;
					return dice2;
				}
			}
			else if (*index < dice2 and *index == x and banned != dice2) {
				if (*w == 0) {
					rFSpace(t, x);
					clrscr();
					printB(0, t);
					*index = dice2;
					*w = 0;
					return dice2;
				}
			}
		}






		if (*w == 30) {
			if (banned == dice1) {
				howManyMovesW(t, team, *index, 0, dice2, *w, 0, hitted);
				Game(t, team, *hitted);
				return 0;
			}
			else if (banned == dice2) {
				howManyMovesW(t, team, *index, dice1, 0, *w, 0, hitted);
				Game(t, team, *hitted);
				return 0;
			}
			else {
				howManyMovesW(t, team, *index, dice1, dice2, *w, number , hitted, sameDice); // last parametr is only when the 2 dices are equal, set to 1
				Game(t, team, *hitted);
				return 0;
			}
		}
		if (team == 1) {
			if (*index + dice1 == *w) ban = dice1;
			else if (*index + dice2 == *w) ban = dice2;
		}
		else {
			if (*index - dice1 == *w) ban = dice1;
			else if (*index - dice2 == *w) ban = dice2;
		}
		
		gotoxy(56, 30);
		if (isAttacking(t, *w - 1, team) == 1 and correctMoveW(team, *index, dice1, dice2, *w, banned) == 1){
			if (team == Team1)	aToSpace(t, 25, Team2);
			else if (team == Team2) aToSpace(t, 26, Team1);
			*hitted = yes;
			rFSpace(t, *w);
			break;
		}

	} while (w == 0 or isTeamW(t, *w - 1, team) == 0 or correctMoveW(team, *index, dice1, dice2, *w, banned) == 0);
	return ban;
}


void howManyMovesW(int t[][15], int team, int index, int dice1, int dice2, int w, int number, int *hitted ,int secret) {
	int banned = 0;
	int sum = dice1 + dice2;

	if (dice1 == dice2) sum *= 2;
	
	menuBoard(t, team, sum, number, dice1, dice2);
	do {
		if (!isPossibleMove1(t, dice1, dice2, banned) and team == Team1) {
			gotoxy(90, 24);
			cputs("you must lose your turn");
			getch();
			Game(t, team, no);
		}
		if (!isPossibleMove2(t, dice1, dice2, banned) and team == Team2) {
			gotoxy(90, 24);
			cputs("you must lose your turn");
			getch();
			Game(t, team, no);
		}
		validateN(t, team, &index);
		if (dice1 == dice2)	validateW(t, team, &w, &index, dice1, dice2, number, hitted);
		else banned = validateW(t, team, &w, &index, dice1, dice2,number, hitted, banned);
		number += countingW(team, index, dice1, dice2, w);
		if (w != 25 and w!= 0) {
			rFSpace(t, index);
			aToSpace(t, w, team);
		}
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

void introAfterHittedPawn(int rand1, int rand2) {
	gotoxy(20, 29);
	printf("first dice: %d", rand1);
	gotoxy(50, 29);
	printf("second dice: %d", rand2);
	gotoxy(12, 30);
	printf("Where wanna put the pawn (from start field):");
}
void introLostQueue(int dice1, int dice2, int team) {
	gotoxy(20, 29);
	printf("first dice: %d", dice1);
	gotoxy(50, 29);
	printf("second dice: %d", dice2);
	gotoxy(95, 14);
	if (team == 1) {
		cputs("Player 1 move");
	}
	if (team == 2) {
		cputs("Player 2 move");
	}
	gotoxy(90, 16);
	cputs("you must lose your turn");
	getch();
}

void playNewGame(int t[][15]){
	int number = 0;
	int n = 0; int w = 0;
	int hitted = no;
	int rand1 = randNumber();
	int rand2 = randNumber();
	printB(0, t);
	gotoxy(35, 28);
	int whoStarts = WhoStart();
	intro(rand1,rand2);
	howManyMovesW(t, whoStarts , n, rand1, rand2, w, number, &hitted);
	Game(t, 2, hitted);
}



int hittingJump(int t[][15], int team, int index) {
	index--;
	int number = 0;
	for (int i = 0; i < 15; i++) {
		if (t[index][i] != team and t[index][i]!= 0) number++;
	}

	if(number == 1)	return 1;
	return false;
} // if pawn come back from bar and immedietaly capture another pawn

int clearHittedPawns(int t[][15],int team, int dice1, int dice2, int *hitted) {
	introAfterHittedPawn(dice1 , dice2);
	int w;

	if (team == Team1) {
		if ((!isTeamOrEmpty(t, dice1, team) and !hittingJump(t, team, dice1)) and (!isTeamOrEmpty(t, dice2, team) and !hittingJump(t, team, dice2))) {
			clrscr();
			printB(0, t);
			introLostQueue(dice1, dice2, team);
			Game(t, team, no);
			return 0;
		}
		while (true) {
			w = cinW();
			if ((w == dice1 || w == dice2) and isTeamOrEmpty(t, w, team)) {
				aToSpace(t, w, Team1);
				rFSpace(t, 26);
				if (w == dice1) return dice1;
				else if (w == dice2) return dice2;
			}
			else if ((w == dice1 || w == dice2) and hittingJump(t, team, w)) {
				rFSpace(t, w);
				aToSpace(t, 25, Team2);
				aToSpace(t, w, Team1);
				rFSpace(t, 26);
				if (w == dice1) return dice1;
				else if (w == dice2) return dice2;
			}
		}
	}
	else {
		if ((!isTeamOrEmpty(t,25 - dice1, team) and !hittingJump(t, team, 25 - dice1)) and (!isTeamOrEmpty(t,25- dice2, team) and !hittingJump(t, team,25 - dice2))) {
			clrscr();
			printB(0, t);
			introLostQueue(dice1, dice2, team);
			Game(t, team, no);
			return 0;
		}
		while (true) {
			w = cinW();
			if ((w == 25 - dice1 || w == 25 - dice2) and isTeamOrEmpty(t, w, team)) {
				aToSpace(t, w, Team2);
				rFSpace(t, 25);
				if (w ==25 - dice1) return dice1;
				else if (w == 25 - dice2) return dice2;
			}
			else if ((w == 25 - dice1 || w == 25 - dice2) and hittingJump(t, team, w)) { 
				rFSpace(t, w);
				aToSpace(t, w, Team2);
				rFSpace(t, 25);
				aToSpace(t, 26, Team1);
				if (w == 25 - dice1) return dice1;
				else if (w == 25 - dice2) return dice2;
			}
		}
	}
	return 0;
}

int isBarTeam1(int t[][15]) {
	for (int i = 0; i < 15; i++) {
		if (t[25][i] == Team1) return 1;
	}
	return 0;
}

int isBarTeam2(int t[][15]) {
	for (int i = 0; i < 15; i++) {
		if (t[24][i] == Team2) return 1;
	}
	return 0;
}


void playGame(int t[][15], int team, int hitted) {
	int number = 0; int m = 0;
	int n = 0; int w = 0;
	int rand1 = randNumber();
	int rand2 = randNumber();

	clrscr();
	printB(0, t);
	if (team == 1) {
		if(isBarTeam1(t))	m = clearHittedPawns(t, team, rand1, rand2, &hitted);
		clrscr();
		printB(0, t);
		if (m == rand1) rand1 = 0;
		else if (m == rand2) rand2 = 0;
		m = 0;
		if (isBarTeam1(t))	m = clearHittedPawns(t, team, rand1, rand2, &hitted);
		if (m == rand1) rand1 = 0;
		else if (m == rand2) rand2 = 0;
	}
	else {
		if (isBarTeam2(t))	m = clearHittedPawns(t, team, rand1, rand2, &hitted);
		clrscr();
		printB(0, t);
		if (m == rand1) rand1 = 0;
		else if (m == rand2) rand2 = 0;
		m = 0;
		if (isBarTeam2(t))	m = clearHittedPawns(t, team, rand1, rand2, &hitted);
		if (m == rand1) rand1 = 0;
		else if (m == rand2) rand2 = 0;
	}
	//printf("%d %d", rand1, rand2); getch();
	if(rand1 == 0 and rand2 == 0) Game(t, team, hitted);
	gotoxy(35, 28);
	intro(rand1, rand2);
	howManyMovesW(t, team, n, rand1, rand2, w, number, &hitted);
	Game(t, team, hitted);
}
