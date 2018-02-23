#define _XOPEN_SOURCE 500

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

void fillBoard(int** board, int rows, int cols);
void updateBoard(int** board, int rows, int cols);
void printBoard(int** board, int rows, int cols);
void clearScreen();

// fills board with random 0's and 1's
void fillBoard(int** board, int rows, int cols)
{
    srand((unsigned int) time(NULL));
    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {
            board[row][col] = rand() % 2;
        }
    }
}

// evolves board 1 step
void updateBoard(int** board, int rows, int cols)
{
    // make copy of board
    int** oldBoard;
    oldBoard = malloc(sizeof(*oldBoard) * rows);
    for (int row = 0; row < rows; row++)
    {
        oldBoard[row] = malloc(sizeof(*oldBoard[row]) * cols);
    }
    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {
            oldBoard[row][col] = board[row][col];
        }
    }

    // iterate thru board cells
    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {
            // get previous/next row relative to current cell
            int rowPrev = row - 1;
            int rowNext = row + 1;
            if (rowPrev < 0)
            {
                rowPrev = rows - 1;
            }
            if (rowNext >= rows)
            {
                rowNext = 0;
            }

            // get previous/next col relative to current cell
            int colPrev = col - 1;
            int colNext = col + 1;
            if (colPrev < 0)
            {
                colPrev = cols - 1;
            }
            if (colNext >= cols)
            {
                colNext = 0;
            }

            // get neighbor count
            int neighbors = 0;
            neighbors += oldBoard[rowPrev][colPrev];
            neighbors += oldBoard[rowPrev][col];
            neighbors += oldBoard[rowPrev][colNext];
            neighbors += oldBoard[row][colPrev];
            neighbors += oldBoard[row][colNext];
            neighbors += oldBoard[rowNext][colPrev];
            neighbors += oldBoard[rowNext][col];
            neighbors += oldBoard[rowNext][colNext];

            // update current cell
            if (oldBoard[row][col] == 0)
            {
                if (neighbors == 3)
                {
                    board[row][col] = 1;
                }
            }
            else if (oldBoard[row][col] == 1)
            {
                if (neighbors != 2)
                {
                    board[row][col] = 0;
                }
            }
        }
    }

    // free copy of board
    for (int row = 0; row < rows; row++)
    {
        free(oldBoard[row]);
    }
    free(oldBoard);
}

void printBoard(int** board, int rows, int cols)
{
    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {
            if (board[row][col] == 1)
            {
                printf("%i ", board[row][col]);
            }
            else
            {
                printf("  ");
            }
        }
        printf("\n");
    }
}

void clearScreen()
{
    system("clear");
}

void game(int rows, int cols)
{
    // declare, initialize, & fill board
    int** board;
    board = malloc(sizeof(*board) * rows);
    for (int row = 0; row < rows; row++)
    {
        board[row] = malloc(sizeof(*board[row]) * cols);
    }
    fillBoard(board, rows, cols);

    // main loop
    clearScreen();
    while (1)
    {
        clearScreen();
        printBoard(board, rows, cols);
        updateBoard(board, rows, cols);
        usleep(100000);
    }

    // free board
    for (int row = 0; row < rows; row++)
    {
        free(board[row]);
    }
    free(board);
}

int main(void)
{
    int rows = 50;
    int cols = 50;
    game(rows, cols);
}
