#include "Libraries.h"


void getNameFile(char* n) {
    clrscr();
    char c;
    int i = 0;
    printf("Name file: (press enter to finish):\n");

    do {
        c = getch();

        if (c != '\r' && c != '\n') {
            putchar(c);
            n[i++] = c;
            if (i == 19) {
                break;
            }
        }
    } while (c != '\r' && c != '\n');

    n[i] = '\0';  
}
void g(char* n) {
    clrscr();
    char c;
    int i = 0;
    printf("Key to your game: (press enter to finish):\n");

    do {
        c = getch();

        if (c != '\r' && c != '\n') {
            putchar(c);
            n[i++] = c;
            if (i == 19) {
                break;
            }
        }
    } while (c != '\r' && c != '\n');

    n[i] = '\0';
    clrscr();
}


void save(int t[][15], int lastTeam) {
    clrscr();
    FILE* file;
    char NameFile[20];
    getNameFile(NameFile);

    file = fopen(NameFile, "a");

    if (file == NULL) {
        printf("Can't open file.\n");
        getch();
        return;
    }
    fprintf(file, "%d\n", lastTeam);
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 15; j++) {
            fprintf(file, "%d ", t[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    printf("Everything saved.\n");
    getch();
    clrscr();
}

void load(int key) {
    int t[26][15]; int team;
    FILE* file;

    char NameFile[20];
    getNameFile(NameFile);

    char KeyFile[20];
    g(KeyFile);
    int num = atoi(KeyFile);

    file = fopen(NameFile, "r");

    if (file == NULL) {
        printf("Can't open file.\n");
    }
    fscanf(file, "%d", &team);
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 15; j++) {
            fscanf(file, "%d", &t[i][j]);
        }
    }

    fclose(file);
    Game(t, team, no,num);
}



void saveNextMove(int t[][15], int lastMove, int rand) {
    FILE* file;
    char c[15];

    sprintf(c, "%d", rand);
    file = fopen(c, "a");
    fprintf(file, "%d\n", lastMove);
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 15; j++) {
            fprintf(file, "%d ", t[i][j]);
        }
        fprintf(file, "\n");
    }
}


void in(int t[][15], int team) {
    printB(0, t);
    gotoxy(88, 11);
    cputs("type 's' to go to the start");
    gotoxy(88, 14);
    cputs("type 'e' to go to the end");
    gotoxy(88, 17);
    cputs("type'u' to undo the move");
    gotoxy(88, 20);
    cputs("press any other key to continue");
    gotoxy(30, 30);
    printf("Team number:  %d  move", team);
}

void p(int t[][15]) {
    clrscr();
    printB(0, t);
}
void x(int t[][15]) {
    gotoxy(1, 1);
    menu();
    firstChoice();
}
void c() {
    clrscr();
}

void loadNextMove() {
    c();
    int t[26][15]; int te;
    FILE* y;

    char K[20];
    g(K);

    y = fopen(K, "r");

    int s;
    int f[500];
    int i = 0; int la;
    s = ftell(y);
    while (!feof(y))
    {
        f[i++] = ftell(y);
        fscanf(y, "%d", &te);
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < 15; j++) {
                fscanf(y, "%d", &t[i][j]);
            }
        }
    }
    la = i - 2;
    i = 0;
   
    fseek(y, s, SEEK_SET);
    char k;
    while (!feof(y))
    {
        i++;
        fscanf(y, "%d", &te);
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < 15; j++) {
                fscanf(y, "%d", &t[i][j]);
            }
        }
        in(t, te);
        k = getch();
        if (k == 'u') {
            fseek(y, f[i-2], SEEK_SET);
            i -= 2;
            p(t);
        }
        if (k == 's') {
            fseek(y, s, SEEK_SET);
            i = 0;
            p(t);
        }
        if (k == 'e') {
            fseek(y, f[la], SEEK_SET);
            i = la;
            p(t);
        }
        c();
    }
    x(t);
}
