/*
 * Idan Hauser
 * 205542459
 */
#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "stdlib.h"
#include <stdbool.h>


#define  SIGN1  'X';
#define  SIGN2  'O';

///struct of a Position includes a row of a table and a colmun of a table
struct position {
    int position_r;
    int position_c;

};

typedef struct position POSITION;

///struct of a pleayer includes a sign and a position
struct player {
    char sign;
    POSITION position;

};

typedef struct player PLAYER;

/*************** Board ***************/
#define ROWS 6
#define COLS 7
char board[ROWS][COLS];

/*********** Declarations ************/

/// This function initializes the game board by assigning each cell
/// with ' ' (resulting with an empty game board).
void initBoard();

/// This function gets a row number and a column number (a cell),
/// and returns the character in that cell (could be 'X', 'O' or ' ').
/// For example:
/// char c = getCell(1, 1);
char getCell(int row, int col);

/// This function gets a row number, a column number and a sign,
/// and assigns the cell with the given sign.
/// For example:
/// setCell(1, 1, 'X');
void setCell(int row, int col, char sign);

/// This function clears the screen.
void clearScreen();

/// This function prints the screen.
void printScreen();

/// This function gets an address of a player,
///checks the input of the user
///Sets the player coin on the table game
void gamePlay(PLAYER *p1, int *arr);

/// This is a sub-function gets a position,
/////a counter to count the four signs and a sign
/////the function returns number of the coins in a row from a pos to the right
int checkRowRight(POSITION pos, int counter, char sign);

/// This is a sub-function function gets a position,
/////a counter to count the four signs and a sign
/////the function returns number of the coins in a row from a pos to the left
int checkRowLeft(POSITION pos, int counter, char sign);

/// This is a sub-function function gets a position,
/////a counter to count the four signs and a sign
/////the function returns number of the coins in a col from a pos to col down
int checkColDown(POSITION pos, int counter, char sign);

/// This sub-function gets a position,
///a counter to count the four signs and a sign
/////the function returns number of the coins in a diagonal Right from a pos to going up
int checkDiagonalRightUp(POSITION pos, int counter, char sign);

/// This sub-function gets a position,
///a counter to count the four signs and a sign
/////the function returns number of the coins in a diagonal left from a pos to going up
int checkDiagonalLeftUp(POSITION pos, int counter, char sign);

/// This sub-function gets a position,
///a counter to count the four signs and a sign
/////the function returns number of the coins in a diagonal Right from a pos to going down
int checkDiagonalRightDown(POSITION pos, int counter, char sign);

/// This sub-function gets a position,
///a counter to count the four signs and a sign
///the function returns true if it found a winner with for signs in a diaonal left  going down
int checkDiagonalLeftDown(POSITION pos, int counter, char sign);

/// This function gets a position,
/// and a sign
///the function returns true if it found a winner.
bool checkWin(POSITION pos, char sign);

/// This sub-function gets a position,
///a counter to count the four signs and a sign
///the function returns true if it found a winner with for signs in a diaonal right
bool checkDiagonalRight(POSITION pos, int counter, char sign);

///a counter to count the four signs and a sign
///the function returns true if it found a winner with for signs in a diaonal left
bool checkDiagonalLeft(POSITION pos, int counter, char sign);

///a counter to count the four signs and a sign
///the function returns true if it found a winner with for signs in a row
bool checkRow(POSITION pos, int counter, char sign);
///a counter to count the four signs and a sign
///the function returns true if it found a winner with for signs in a col
bool checkCol(POSITION pos, int counter, char sign);

/*************** Main ****************/
void main() {
    PLAYER player1, player2;
    player1.sign = SIGN1;
    player2.sign = SIGN2;
    int arr[COLS] = {0};
    bool foundWinner = false;
    int counter = 0;
    initBoard();
    printScreen();

    while (!foundWinner) {
        if (counter >= 42) {
            printf("\n its a TIE - try again \n");
            foundWinner = true;
        } else {
            printf("Player number 1: \n Please enter column (a number between 1-7): \n");
            gamePlay(&player1, arr);
            counter++;
            if (counter >= 6) {
                foundWinner = checkWin(player1.position, player1.sign);
            }
            if (foundWinner) {
                printf("Player 1 well done you won! \n");
            } else {
                printf("Player number 2: \n Please enter column (a number between 1-7): \n");
                gamePlay(&player2, arr);
                counter++;
                if (counter >= 6) {
                    foundWinner = checkWin(player2.position, player2.sign);
                    if (foundWinner) {
                        printf("Player 2 well done you won! \n");
                    }
                }
            }
        }
    }
}

/********** Implementations **********/
char getCell(int row, int col) {
    return board[row - 1][col - 1];
}

void setCell(int row, int col, char sign) {
    board[row - 1][col - 1] = sign;
}

void initBoard() {
    int i, j;

    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            setCell(i + 1, j + 1, ' ');
        }
    }
}

//I had to chance this function because
// im working with mac machine, so i made this game
//compatible with any operation system
void clearScreen() {
#ifdef _WIN32
    system("cls");
#elif defined(unix) || defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
    system("clear");

#else
#error "OS not supported."

#endif
}

//cPlayer - current player pointer
void gamePlay(PLAYER *cPlayer, int *arr) {
    bool inputChecker = false;
    while (!inputChecker) {
        scanf("%d", &cPlayer->position.position_c);
        if ((cPlayer->position.position_c < 8) && (cPlayer->position.position_c > 0)) {
            if (arr[cPlayer->position.position_c] < 6) {
                setCell(cPlayer->position.position_r = ROWS - arr[cPlayer->position.position_c],
                        cPlayer->position.position_c,
                        cPlayer->sign);
                arr[cPlayer->position.position_c]++;
                inputChecker = true;
                clearScreen();
                printScreen();
            } else {
                if (inputChecker == false) {
                    printf("the column you %d chose is full, please try again choose from 1-7 without %d which is full\n",
                           cPlayer->position.position_c, cPlayer->position.position_c);
                }
            }
        } else {
            printf("the column you chosen %d is not exist, please try again choose from 1-7\n",
                   cPlayer->position.position_c);
        }
    }

}

bool checkWin(POSITION pos, char sign) {
    int counter = 0;
    return checkRow(pos, counter, sign) ||
           checkCol(pos, counter, sign)
           || checkDiagonalRight(pos, counter, sign) ||
           checkDiagonalLeft(pos, counter, sign);
}

void printScreen() {
    for (int j = 0; j <= COLS; ++j) {
        if (j != 0) {
            printf("%d \t", j);
        } else {
            printf("\t");
        }
    }
    printf("\n");
    for (int i = 1; i <= ROWS; ++i) {
        printf("%c \t", 64 + i);
        for (int j = 1; j <= COLS; ++j) {
            printf("%c \t", getCell(i, j));
        }
        printf("\n");
    }
}

//plu - position left up
//prd - position right down
bool checkDiagonalLeft(POSITION pos, int counter, char sign) {
    POSITION plu = pos, prd = pos;
    plu.position_c -= 1;
    plu.position_r -= 1;

    prd.position_r += 1;
    prd.position_c += 1;
    return ((checkDiagonalRightDown(prd, counter, sign) + checkDiagonalLeftUp(plu, counter, sign)) + 1) >= 4;
}

//pld - position left down
//pru - position right up
bool checkDiagonalRight(POSITION pos, int counter, char sign) {
    POSITION pru = pos, pld = pos;
    pru.position_c += 1;
    pru.position_r -= 1;

    pld.position_r += 1;
    pld.position_c -= 1;
    return ((checkDiagonalRightUp(pru, counter, sign) + checkDiagonalLeftDown(pld, counter, sign)) + 1) >= 4;
}

//pr - position right
//pl - position left
bool checkRow(POSITION pos, int counter, char sign) {
    POSITION pr = pos, pl = pos;
    pr.position_c += 1;
    pl.position_c -= 1;
    return ((checkRowRight(pr, counter, sign) + checkRowLeft(pl, counter, sign)) + 1) >= 4;
}

//pc - position down
bool checkCol(POSITION pos, int counter, char sign) {
    POSITION pd = pos;
    pd.position_r += 1;
    return (checkColDown(pd, counter, sign) + 1) >= 4;
}

int checkRowLeft(POSITION pos, int counter, char sign) {
    if (counter < 3)
        if (pos.position_c > 0) {
            if (getCell(pos.position_r, pos.position_c) == sign) {
                counter++;
                pos.position_c--;
                if (pos.position_c > 0) {
                    return checkRowLeft(pos, counter, sign);
                }
            }
        }
    return counter;
}

int checkRowRight(POSITION pos, int counter, char sign) {
    if (counter < 3)
        if (pos.position_c <= COLS) {
            if (getCell(pos.position_r, pos.position_c) == sign) {
                counter++;
                pos.position_c++;
                if (pos.position_c <= COLS) {
                    return checkRowRight(pos, counter, sign);
                }
            }
        }
    return counter;
}

int checkColDown(POSITION pos, int counter, char sign) {
    if (counter < 3)
        if (pos.position_r <= ROWS) {
            if (getCell(pos.position_r, pos.position_c) == sign) {
                counter++;
                pos.position_r++;
                if (pos.position_r <= ROWS) {
                    return checkColDown(pos, counter, sign);
                }
            }
        }
    return counter;
}

int checkDiagonalRightUp(POSITION pos, int counter, char sign) {
    if (counter < 3)
        if (pos.position_r <= ROWS && pos.position_c <= COLS) {
            if (getCell(pos.position_r, pos.position_c) == sign) {
                counter++;
                pos.position_c++;
                pos.position_r--;
                if (pos.position_r <= ROWS && pos.position_c >= COLS) {
                    return checkDiagonalRightUp(pos, counter, sign);
                }
            }
        }
    return counter;
}

int checkDiagonalLeftUp(POSITION pos, int counter, char sign) {
    if (counter < 3)
        if (pos.position_r >= 0 && pos.position_c >= 0) {
            if (getCell(pos.position_r, pos.position_c) == sign) {
                counter++;
                pos.position_c--;
                pos.position_r--;
                if (pos.position_r >= 0 && pos.position_c >= 0) {
                    return checkDiagonalLeftUp(pos, counter, sign);
                }
            }
        }
    return counter;
}

int checkDiagonalRightDown(POSITION pos, int counter, char sign) {
    if (counter < 3)
        if (pos.position_r <= ROWS && pos.position_c <= COLS) {
            if (getCell(pos.position_r, pos.position_c) == sign) {
                counter++;
                pos.position_c++;
                pos.position_r++;
                if (pos.position_r <= ROWS && pos.position_c <= COLS) {
                    return checkDiagonalRightDown(pos, counter, sign);
                }
            }
        }
    return counter;
}

int checkDiagonalLeftDown(POSITION pos, int counter, char sign) {
    if (counter < 3)
        if (pos.position_r <= ROWS && pos.position_c > 0) {
            if (getCell(pos.position_r, pos.position_c) == sign) {
                counter++;
                pos.position_c--;
                pos.position_r++;
                if (pos.position_r <= ROWS && pos.position_c > 0) {
                    return checkDiagonalLeftDown(pos, counter, sign);
                }
            }
        }
    return counter;
}
