// 在 xv6 源码目录中创建 gomoku.c 文件
#include "types.h"
#include "stat.h"
#include "user.h"

#define SIZE 15

void initializeBoard(char board[SIZE][SIZE]);
void printBoard(char board[SIZE][SIZE]);
bool makeMove(char board[SIZE][SIZE], int row, int col, char player);
bool checkWin(char board[SIZE][SIZE], int row, int col, char player);

int main(int argc, char *argv[]) {
    char board[SIZE][SIZE];
    initializeBoard(board);
    char currentPlayer = 'X';
    int row, col;
    bool gameWon = false;

    while (!gameWon) {
        printBoard(board);
        printf(1, "Player %c, enter your move (row and column): ", currentPlayer);
        char input[10];
        gets(input, 10);
        sscanf(input, "%d %d", &row, &col);

        if (makeMove(board, row, col, currentPlayer)) {
            if (checkWin(board, row, col, currentPlayer)) {
                gameWon = true;
                printBoard(board);
                printf(1, "Player %c wins!\n", currentPlayer);
            } else {
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            }
        } else {
            printf(1, "Invalid move. Try again.\n");
        }
    }

    exit();
}

void initializeBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = '.';
        }
    }
}

void printBoard(char board[SIZE][SIZE]) {
    printf(1, "   ");
    for (int i = 0; i < SIZE; i++) {
        printf(1, "%2d ", i + 1);
    }
    printf(1, "\n");

    for (int i = 0; i < SIZE; i++) {
        printf(1, "%2d ", i + 1);
        for (int j = 0; j < SIZE; j++) {
            printf(1, " %c ", board[i][j]);
        }
        printf(1, "\n");
    }
}

bool makeMove(char board[SIZE][SIZE], int row, int col, char player) {
    if (row >= 1 && row <= SIZE && col >= 1 && col <= SIZE && board[row - 1][col - 1] == '.') {
        board[row - 1][col - 1] = player;
        return true;
    }
    return false;
}

bool checkWin(char board[SIZE][SIZE], int row, int col, char player) {
    int directions[4][2] = { {0, 1}, {1, 0}, {1, 1}, {1, -1} };
    row--; col--;
    for (int d = 0; d < 4; d++) {
        int count = 1;
        for (int i = 1; i < 5; i++) {
            int newRow = row + i * directions[d][0];
            int newCol = col + i * directions[d][1];
            if (newRow >= 0 && newRow < SIZE && newCol >= 0 && newCol < SIZE && board[newRow][newCol] == player) {
                count++;
            } else {
                break;
            }
        }
        for (int i = 1; i < 5; i++) {
            int newRow = row - i * directions[d][0];
            int newCol = col - i * directions[d][1];
            if (newRow >= 0 && newRow < SIZE && newCol >= 0 && newCol < SIZE && board[newRow][newCol] == player) {
                count++;
            } else {
                break;
            }
        }
        if (count >= 5) {
            return true;
        }
    }
    return false;
}
