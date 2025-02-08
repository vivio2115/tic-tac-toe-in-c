#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char board[3][3];
const char PLAYER = 'X';
const char COMPUTER = 'O';
int difficulty;

void restBoard();
void printBoard();
int checkFreeSpaces();
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char);

// TODO: Upgrade the look of the menu and game
int main()
{
    printf("Welcome to Tic-Tac-Toe!\n");
    printf("Choose difficulty (1-3): \n");
    printf("1 - Easy\n");
    printf("2 - Medium\n");
    printf("3 - Hard\n");
    do {
        printf("Enter difficulty: ");
        scanf("%d", &difficulty);

        if (difficulty < 1 || difficulty > 3) {
            printf("Invalid input. Please enter a number between 1 and 3.\n");
        }
    } while (difficulty < 1 || difficulty > 3);

    while (1) {
        char winner = ' ';

        restBoard();

        while (winner == ' ' && checkFreeSpaces() > 0)
        {
            printBoard();

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

        printBoard();
        printWinner(winner);

        char choice;
        while (1) {
            printf("Do you want to play again? (y/n): ");
            scanf(" %c", &choice);
            if (choice == 'y' || choice == 'Y') {
                break;
            }
            else if (choice == 'n' || choice == 'N') {
                printf("Thanks for playing!\n");
                printf("Press any key to exit...\n");
                getchar();
                getchar();
                return 0;
            }
        }
    }


    return 0;
}
int blockPlayerMove()
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

int tryToWin() {
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

int pickBestSpot() {
    //in the middel
    if (board[1][1] == ' ') {
        board[1][1] = COMPUTER;
        return 1;
    }
    //in the corner
    if (board[0][0] == ' ') {
        board[0][0] = COMPUTER;
    }
    if (board[2][0] == ' ') {
        board[2][0] = COMPUTER;
    }
    if (board[0][2] == ' ') {
        board[0][0] = COMPUTER;
    }
    if (board[2][2] == ' ') {
        board[2][2] = COMPUTER;
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

void printBoard()
{
    printf("  %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf(" ---|---|---\n");
    printf("  %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf(" ---|---|---\n");
    printf("  %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
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
        scanf("%d", &x);
        x--;
        printf("Enter column (#1-3): ");
        scanf("%d", &y);
        y--;

        if (x < 0 || x > 2 || y < 0 || y > 2) {
            printf("Invalid input. Please enter a number between 1 and 3.\n");
        }
        else if (board[x][y] != ' ') {
            printf("Invalid move! The cell is already occupied.\n");
        }
        else {
            board[x][y] = PLAYER;
            break;
        }
    }
}

void computerMove()
{
    srand(time(0));
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
    } else if (difficulty == 2) {
        //medium
        if (!blockPlayerMove()) {
            do {
                x = rand() % 3;
                y = rand() % 3;
            } while (board[x][y] != ' ');

            board[x][y] = COMPUTER;
        }
    } else if (difficulty == 3) {
        //hard
        if (tryToWin()) {
            return;
        }
        if (blockPlayerMove()) {
            return;
        }
        if (pickBestSpot()) {
            return;
        }
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (board[x][y] != ' ');

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
    if (winner == PLAYER) {
        printf("Player won!\n");
    }
    else if (winner == COMPUTER) {
        printf("Computer won!\n");
    }
    else {
        printf("Draw!\n");
    }
}
