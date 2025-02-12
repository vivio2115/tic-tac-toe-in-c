/*
 * Main code base for small console game made by vivio2115 (Github) last updated on 12/02/2025.
 * Its free to use and its under MIT license.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "unistd.h"
#include "acsii.h"
#include "images.c"


#define MAX_DEPTH 9
#define STAT 1 //0 is for debug menu and all other things that are not that needed for player, 1 just stand for production ;)

char board[3][3];
char PLAYER;
char COMPUTER;
int difficulty;
int console_width = 110;
int board_width = 21;
char debug;
char input;

void restBoard();
void printBoard(int padding_left);
int checkFreeSpaces();
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char);

static void clearScreen() {
    printf("\033[2J");
    printf("\033[H");
}

static void printCenteredLine(const char* line, int console_width) {
    int line_length = (int)strlen(line);
    int padding_left = (console_width - line_length) / 2;
    if (padding_left < 0) padding_left = 0;
    printf("%*s%s\n", padding_left, "", line);
}

static void printLogo() {
    printCenteredLine(YEL"   _______  ___   _______    _______  _______  _______    _______  _______  _______ ", console_width);
    printCenteredLine(YEL"  |       ||   | |       |  |       ||       ||       |  |       ||       ||       |", console_width);
    printCenteredLine(YEL"  |_     _||   | |    ___|  |_     _||   _   ||    ___|  |_     _||   _   ||    ___|", console_width);
    printCenteredLine(YEL"    |   |  |   | |   |        |   |  |  |_|  ||   |        |   |  |  | |  ||   |___ ", console_width);
    printCenteredLine(YEL"    |   |  |   | |   |        |   |  |       ||   |        |   |  |  |_|  ||    ___|", console_width);
    printCenteredLine(YEL"    |   |  |   | |   |___     |   |  |   _   ||   |___     |   |  |       ||   |___ ", console_width);
    printCenteredLine(YEL"    |___|  |___| |_______|    |___|  |__| |__||_______|    |___|  |_______||_______|", console_width);
    printf(reset"\n");
}
static void computerWinAcsii() {
    printCenteredLine(" ____________________ ", console_width);
	printCenteredLine("|                    |", console_width);
	printCenteredLine("|  ________________  |", console_width);
	printCenteredLine("| |                | |", console_width);
	printCenteredLine("| |  COMPUTER WIN  | |", console_width);
	printCenteredLine("| |________________| |", console_width);
    printCenteredLine("|                    |", console_width);
	printCenteredLine("|____________________|", console_width);
    printf("\n");
}
static void playerWinAcsii() {
    printCenteredLine(" ____________________ ", console_width);
    printCenteredLine("|                    |", console_width);
    printCenteredLine("|  ________________  |", console_width);
    printCenteredLine("| |                | |", console_width);
    printCenteredLine("| |   PLAYER WIN   | |", console_width);
    printCenteredLine("| |________________| |", console_width);
    printCenteredLine("|                    |", console_width);
    printCenteredLine("|____________________|", console_width);
    printf("\n");
}
static void drawAcsii() {
    printCenteredLine(" ____________________ ", console_width);
    printCenteredLine("|                    |", console_width);
    printCenteredLine("|  ________________  |", console_width);
    printCenteredLine("| |                | |", console_width);
    printCenteredLine("| |  COMPUTER WIN  | |", console_width);
    printCenteredLine("| |________________| |", console_width);
    printCenteredLine("|                    |", console_width);
    printCenteredLine("|____________________|", console_width);
    printf("\n");
}


int main()
{
    int padding_left = (console_width - board_width) / 2;

    printLogo();
    if (STAT == 0) {
       printf(RED "Enable debug mode (y/n):" reset);
       scanf_s(" %c", &debug, 1);
	}
	else {
		debug = 'n';
	}
    printf("Choose difficulty (1-3): \n");
    printf("1 - Easy\n");
    printf("2 - Medium\n");
    printf("3 - Hard\n");
	printf("4 - Impossible\n");
    if (STAT == 0) {
        printf("5 - Something about program\n");
    }
    while (1) {
        printf("Enter difficulty: ");
        if (scanf_s("%d", &difficulty) == 1) {
            if (difficulty == 1 || difficulty == 2 || difficulty == 3 || difficulty == 4) {
                break;
            }
            else if (difficulty == 5) {
				catACSII();
            }
            else {
                printf(RED "[Invalid input]" reset " Please enter 1, 2, 3 or 4.\n");
            }
        }
        else {
            printf(RED "[Invalid input]" reset " Please enter a number between 1 and 5.\n");
            while ((input = getchar()) != '\n' && input != EOF);
        }
    }
    printf("Choose your symbol (X/O): ");
    while (1) {
        printf("Enter X or O: ");
        if (scanf_s(" %c", &PLAYER, 1) == 1) {
            if (PLAYER == 'X') {
                PLAYER = 'X';
                COMPUTER = 'O';
                break;
            }
            else if (PLAYER == 'O') {
                PLAYER = 'O';
                COMPUTER = 'X';
                break;
            }
            else {
                printf(RED "[Invalid input]" reset " Please enter X or O.\n");
            }
        }
    }

    
    while (1) {
        char winner = ' ';

        restBoard();

        while (winner == ' ' && checkFreeSpaces() > 0)
        {
            printBoard(padding_left);

            playerMove();
            winner = checkWinner();
            if (winner != ' ' || checkFreeSpaces() == 0) {
                break;
            }

            computerMove();
            winner = checkWinner();
            if (winner != ' ' || checkFreeSpaces() == 0) {
                break;
            }
        }

         
        printBoard(padding_left);
        printWinner(winner);

        char choice;
        while (1) {
            printf("Do you want to see the board? (y/n): ");
            scanf_s(" %c", &choice, 1);
            if (choice == 'y' || choice == 'Y') {
                printBoard((console_width - board_width) / 2);
                printCenteredLine("Here is the board:", console_width);
                if (winner == PLAYER) {
                    printCenteredLine("The winner is: you", console_width);
                }
                else if (winner == COMPUTER) {
                    printCenteredLine("The winner is: computer", console_width);
                }
                else {
                    printCenteredLine("The game is a draw", console_width);
                }
                break;
            }
            else if (choice == 'n' || choice == 'N') {
                clearScreen();
                break;
            }
        }

        while (1) {
            printf("Do you want to play again? (y/n): ");
            scanf_s(" %c", &choice, 1);
            if (choice == 'y' || choice == 'Y') {
                break;
            }
            else if (choice == 'n' || choice == 'N') {
                printf("Thanks for playing!\n");
                printf("Press any key to exit...\n");
                int ch = getchar();
                ch = getchar();
                return 0;
            }
        }


    }

    return 0;
}


static int blockPlayerMove()
{
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == PLAYER && board[i][1] == PLAYER && board[i][2] == ' ') {
            board[i][2] = COMPUTER;
            return 1;
        }
        if (board[i][1] == PLAYER && board[i][2] == PLAYER && board[i][0] == ' ') {
            board[i][0] = COMPUTER;
            return 1;
        }
        if (board[i][0] == PLAYER && board[i][2] == PLAYER && board[i][1] == ' ') {
            board[i][1] = COMPUTER;
            return 1;
        }
    }

    for (int i = 0; i < 3; i++) {
        if (board[0][i] == PLAYER && board[1][i] == PLAYER && board[2][i] == ' ') {
            board[2][i] = COMPUTER;
            return 1;
        }
        if (board[1][i] == PLAYER && board[2][i] == PLAYER && board[0][i] == ' ') {
            board[0][i] = COMPUTER;
            return 1;
        }
        if (board[0][i] == PLAYER && board[2][i] == PLAYER && board[1][i] == ' ') {
            board[1][i] = COMPUTER;
            return 1;
        }
    }

    if (board[0][0] == PLAYER && board[1][1] == PLAYER && board[2][2] == ' ') {
        board[2][2] = COMPUTER;
        return 1;
    }
    if (board[1][1] == PLAYER && board[2][2] == PLAYER && board[0][0] == ' ') {
        board[0][0] = COMPUTER;
        return 1;
    }
    if (board[0][0] == PLAYER && board[2][2] == PLAYER && board[1][1] == ' ') {
        board[1][1] = COMPUTER;
        return 1;
    }

    if (board[0][2] == PLAYER && board[1][1] == PLAYER && board[2][0] == ' ') {
        board[2][0] = COMPUTER;
        return 1;
    }
    if (board[1][1] == PLAYER && board[2][0] == PLAYER && board[0][2] == ' ') {
        board[0][2] = COMPUTER;
        return 1;
    }
    if (board[0][2] == PLAYER && board[2][0] == PLAYER && board[1][1] == ' ') {
        board[1][1] = COMPUTER;
        return 1;
    }

    return 0;
}

static int tryToWin() {
    for (int i = 0; i < 3; i++) {
        //check rows
        if (board[i][0] == COMPUTER && board[i][1] == COMPUTER && board[i][2] == ' ') {
            board[i][2] = COMPUTER;
            return 1;
        }
        if (board[i][1] == COMPUTER && board[i][2] == COMPUTER && board[i][0] == ' ') {
            board[i][0] = COMPUTER;
            return 1;
        }
        if (board[i][0] == COMPUTER && board[i][2] == COMPUTER && board[i][1] == ' ') {
            board[i][1] = COMPUTER;
            return 1;
        }

        //check columns (xD)
        if (board[0][i] == COMPUTER && board[1][i] == COMPUTER && board[2][i] == ' ') {
            board[2][i] = COMPUTER;
            return 1;
        }
        if (board[1][i] == COMPUTER && board[2][i] == COMPUTER && board[0][i] == ' ') {
            board[0][i] = COMPUTER;
            return 1;
        }
        if (board[0][i] == COMPUTER && board[2][i] == COMPUTER && board[1][i] == ' ') {
            board[1][i] = COMPUTER;
            return 1;
        }

    }

    //check diagonals
    if (board[0][0] == COMPUTER && board[1][1] == COMPUTER && board[2][2] == ' ') {
        board[2][2] = COMPUTER;
        return 1;
    }
    if (board[1][1] == COMPUTER && board[2][2] == COMPUTER && board[0][0] == ' ') {
        board[0][0] = COMPUTER;
        return 1;
    }
    if (board[0][0] == COMPUTER && board[2][2] == COMPUTER && board[1][1] == ' ') {
        board[1][1] = COMPUTER;
        return 1;
    }

    if (board[0][2] == COMPUTER && board[1][1] == COMPUTER && board[2][0] == ' ') {
        board[2][0] = COMPUTER;
        return 1;
    }
    if (board[1][1] == COMPUTER && board[2][0] == COMPUTER && board[0][2] == ' ') {
        board[0][2] = COMPUTER;
        return 1;
    }
    if (board[0][2] == COMPUTER && board[2][0] == COMPUTER && board[1][1] == ' ') {
        board[1][1] = COMPUTER;
        return 1;
    }

    return 0;
}

static int pickBestSpot() {
    //in the middel
    if (board[1][1] == ' ') {
        board[1][1] = COMPUTER;
        return 1;
    }
    //in the corner
    if (board[0][0] == ' ') {
        board[0][0] = COMPUTER;
        return 1;
    }
    if (board[2][0] == ' ') {
        board[2][0] = COMPUTER;
        return 1;
    }
    if (board[0][2] == ' ') {
        board[0][2] = COMPUTER;
        return 1;
    }
    if (board[2][2] == ' ') {
        board[2][2] = COMPUTER;
        return 1;
    }
    //just random lamo
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = COMPUTER;
                return 1;
            }
        }
    }

    return 0;
}

static int evaluateBoard() {
    //check rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
            if (board[i][0] == COMPUTER) {
                return 10;
            }
            else if (board[i][0] == PLAYER) {
                return -10;
            }
        }
    }

    //check columns
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i]) {
            if (board[0][i] == COMPUTER) {
                return 10;
            }
            else if (board[0][i] == PLAYER) {
                return -10;
            }
        }
    }

    //check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == COMPUTER) {
            return 10;
        }
        else if (board[0][0] == PLAYER) {
            return -10;
        }
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == COMPUTER) {
            return 10;
        }
        else if (board[0][2] == PLAYER) {
            return -10;
        }
    }

    return 0;
}

static int minimax(int depth, int isMaximizing) {
    int score = evaluateBoard();

    if (score == 10 || score == -10) {
        return score;
    }
    if (checkFreeSpaces() == 0) {
        return 0;
    }

    if (isMaximizing) {
        int best = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = COMPUTER;
                    best = (best > minimax(depth + 1, 0)) ? best : minimax(depth + 1, 0);
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
    else {
        int best = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = PLAYER;
                    best = (best < minimax(depth + 1, 1)) ? best : minimax(depth + 1, 1);
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
}

static int findBestMove() {
    int bestVal = -1000;
    int bestMove[2] = { -1, -1 };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = COMPUTER;
                int moveVal = minimax(0, 0);
                board[i][j] = ' ';
                if (moveVal > bestVal) {
                    bestMove[0] = i;
                    bestMove[1] = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove[0] * 3 + bestMove[1]; 
}

static int tryHard() {
    int bestMove = findBestMove();
    board[bestMove / 3][bestMove % 3] = COMPUTER;
    return 1;
}

void restBoard()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}

static void printDebugBoard() {
    printf("\nDEBUG: Current board state:\n");
    printf("    0   1   2     Minimax Evaluation\n");
    printf("  -------------   ------------------\n");
    for (int i = 0; i < 3; i++) {
        printf("%d |", i);
        for (int j = 0; j < 3; j++) {
            printf(" %c |", board[i][j] == ' ' ? '-' : board[i][j]);
        }

        if (difficulty == 4) {
            printf("   ");
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = COMPUTER;
                    int eval = minimax(0, 0);
                    board[i][j] = ' ';
					if (eval == 10){
                        printf(GRN " %2d " reset, eval);
                    }
                    else {
                        printf(CYN " %2d " reset, eval);
                    }
                }
                else {
                    printf(RED "  X " reset);
                }
            }
        }

        printf("\n  -------------   ------------------\n");
    }
}


void printBoard(int padding_left)
{
    clearScreen();
    printLogo();
    printf("%*s+-----+-----+-----+\n", padding_left, "");

    for (int i = 0; i < 3; i++) {
        printf("%*s|     |     |     |\n", padding_left, "");
        printf("%*s|  %c  |  %c  |  %c  |\n", padding_left, "",
            board[i][0] == ' ' ? ' ' : (board[i][0] == PLAYER ? 'X' : 'O'),
            board[i][1] == ' ' ? ' ' : (board[i][1] == PLAYER ? 'X' : 'O'),
            board[i][2] == ' ' ? ' ' : (board[i][2] == PLAYER ? 'X' : 'O'));
        printf("%*s|     |     |     |\n", padding_left, "");
        if (i < 2) {
            printf("%*s+-----+-----+-----+\n", padding_left, "");
        }
    }
    printf("%*s+-----+-----+-----+\n", padding_left, "");

    if (debug == 'y' || debug == 'Y') {
        printDebugBoard();
    }
}



int checkFreeSpaces()
{
    int freeSpaces = 9;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != ' ') {
                freeSpaces--;
            }
        }
    }
    return freeSpaces;
}

void playerMove()
{
    int x, y;

    while (1) {
        printf("Enter row (#1-3): ");
        scanf_s("%d", &x);
        x--;
        printf("Enter column (#1-3): ");
        scanf_s("%d", &y);
        y--;

        if (x < 0 || x > 2 || y < 0 || y > 2) {
            printf(RED "[Invalid input]" reset " Please enter a number between 1 and 3.\n");
        }
        else if (board[x][y] != ' ') {
            printf(RED "Invalid move!" reset " The cell is already occupied.\n");
        }
        else {
            board[x][y] = PLAYER;
            break;
        }
    }
}

void computerMove()
{
    srand((unsigned int)time(0));
    int x, y;

    if (checkFreeSpaces() == 0) {
        return;
    }
    if (difficulty == 1) {
        //easy (lamo)
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (board[x][y] != ' ');

        board[x][y] = COMPUTER;
    }
    else if (difficulty == 2) {
        //medium
        if (!blockPlayerMove()) {
            do {
                x = rand() % 3;
                y = rand() % 3;
            } while (board[x][y] != ' ');

            board[x][y] = COMPUTER;
        }
    }
    else if (difficulty == 3) {
        //hard
        int moved = 0;

        if (tryToWin()) {
            moved = 1;
            return;
        }
        if (blockPlayerMove()) {
            moved = 1;
            return;
        }
        if (pickBestSpot()) {
            moved = 1;
            return;
        }

        if (!moved) {
            do {
                x = rand() % 3;
                y = rand() % 3;
            } while (board[x][y] != ' ');
        }

        board[x][y] = COMPUTER;
    }
    else if (difficulty == 4) {
        //impossible
        int movedI = 0;


        if (tryHard()) {
            movedI = 1;
            return;
        }
        if (tryToWin()) {
            movedI = 1;
            return;
        }
        if (blockPlayerMove()) {
            movedI = 1;
            return;
        }
        if (pickBestSpot()) {
            movedI = 1;
            return;
        }

        if (!movedI) {
            do {
                x = rand() % 3;
                y = rand() % 3;
            } while (board[x][y] != ' ');
        }

        board[x][y] = COMPUTER;
    }
}

char checkWinner()
{
    //check rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] != ' ') {
            return board[i][0];
        }
    }
    //check columns
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] != ' ') {
            return board[0][i];
        }
    }
    //check diagonals
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != ' ') {
        return board[0][0];
    }
    if (board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[0][2] != ' ') {
        return board[0][2];
    }

    return ' ';
}

void printWinner(char winner)
{
    const int flashCount = 3;
	const int flashDelay = 400000;

    if (winner == PLAYER) {
		clearScreen();
		printLogo();
		playerWinAcsii();
        for (int i = 0; i < flashCount; i++) {
			printf(CYN);
			printCenteredLine("Player won!", console_width);
			printf("\n"reset);
			usleep(flashDelay);
			clearScreen();
			printLogo();
			playerWinAcsii();
			usleep(flashDelay);
        }
		printCenteredLine("Player won!\n", console_width);
    }
    else if (winner == COMPUTER) {
        clearScreen();
        printLogo();
        computerWinAcsii();
        for (int i = 0; i < flashCount; i++) {
            printf(CYN);
            printCenteredLine("Computer won!" , console_width);
            printf("\n"reset);
            usleep(flashDelay);
            clearScreen();
            printLogo();
            computerWinAcsii();
            usleep(flashDelay);
        }
        printCenteredLine("Computer won!\n", console_width);
    }
    else {
		clearScreen();
		printLogo();
		drawAcsii();
		for (int i = 0; i < flashCount; i++) {
            printf(CYN);
			printCenteredLine("It's a draw!", console_width);
            printf("\n"reset);
			usleep(flashDelay);
            clearScreen();
			printLogo();
			drawAcsii();
			usleep(flashDelay);
		}
		printCenteredLine("It's a draw!\n", console_width);
    }
}
