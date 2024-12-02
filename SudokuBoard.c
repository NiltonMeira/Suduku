#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>

#define SIZE 9

int hidden_matrix[SIZE][SIZE];

// Function to check if a number is safe to place in the grid
int isSafe(int board[SIZE][SIZE], int row, int col, int num) {
    // Check if the number is not already present in the row and column
    for (int i = 0; i < SIZE; i++) {
        if (board[row][i] == num || board[i][col] == num) {
            return 0;
        }
    }

    // Check if the number is not present in the 3x3 subgrid
    int subgridSize = 3;
    int startRow = row - (row % subgridSize);
    int startCol = col - (col % subgridSize);
    for (int i = 0; i < subgridSize; i++) {
        for (int j = 0; j < subgridSize; j++) {
            if (board[startRow + i][startCol + j] == num) {
                return 0;
            }
        }
    }

    // If the number is safe, return 1
    return 1;
}

// Function to generate a random Sudoku grid
int generateSudoku(int board[SIZE][SIZE]) {
    int row, col;
    int num;
    int unassigned = 0;

    // Seed the random number generator
    srand(time(NULL));

    // Initialize the board with zeros
    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            board[row][col] = 0;
        }
    }

    // Fill the diagonal subgrids with random values
    for (int subgrid = 0; subgrid < SIZE; subgrid += 3) {
        for (num = 1; num <= SIZE; num++) {
            do {
                row = subgrid + rand() % 3;
                col = subgrid + rand() % 3;
            } while (board[row][col] != 0);
            board[row][col] = num;
        }
    }

    // Fill the remaining grid using a backtracking approach
    if (!solveSudoku(board)) {
        return 0;
    }

    return 1;
}

// Function to solve the Sudoku puzzle using backtracking
int solveSudoku(int board[SIZE][SIZE]) {
    int row, col;

    if (!findUnassignedLocation(board, &row, &col)) {
        return 1; // All cells are assigned, Sudoku is solved
    }

    for (int num = 1; num <= SIZE; num++) {
        if (isSafe(board, row, col, num)) {
            board[row][col] = num;
            if (solveSudoku(board)) {
                return 1;
            }
            board[row][col] = 0; // Unassign the cell if no solution found
        }
    }

    return 0; // No solution exists
}

// Function to find an unassigned location in the grid
int findUnassignedLocation(int board[SIZE][SIZE], int *row, int *col) {
    for (*row = 0; *row < SIZE; (*row)++) {
        for (*col = 0; *col < SIZE; (*col)++) {
            if (board[*row][*col] == 0) {
                return 1; // Unassigned location found
            }
        }
    }
    return 0; // No unassigned location exists
}

void startGame(int board[SIZE][SIZE], bool has_palyed, int row_pos, int col_pos, int my_num) {
    int border = 219;

    if (generateSudoku(board)) {
        // Printing the resulting Sudoku grid
        for (int i = 0; i < SIZE; i++) {
            //printf("%c", border);
            if (i % 3 == 0) {
                for(int k = 0; k < 26; k++) {
                    printf("%c", border);
                }
                printf("\n");
            }
            for (int j = 0; j < SIZE; j++) {
                if (j % 3 == 0) {
                    printf("%c%c", border,border);
                }
                if (rand() % 2 == 0) {
                    if (has_palyed == false) {
                        printf("[]");
                        hidden_matrix[i][j] = 0;
                    } else {
                        if (board[i][j] == board[row_pos][col_pos]){
                            printf("%d ", my_num);
                        } else {
                            printf("[]");
                            hidden_matrix[i][j] = 0;
                        }
                    }
                    
                } else {
                    printf("%d ", board[i][j]);
                    hidden_matrix[i][j] = board[i][j];
                }
            }
            printf("%c%c", border,border);
            printf("\n");
        }
        for(int k = 0; k < 26; k++) {
            printf("%c", border);
        }
    } else {
        printf("No solution found.\n");
    }
}

void printMatrix(int row_pos, int col_pos, int my_num) {
    int border = 219;
    system("cls");
    if (hidden_matrix[row_pos][col_pos] == 0) {
        hidden_matrix[row_pos][col_pos] = my_num;
    }
    for(int x = 0 ; x < 9 ; x++) {
        if (x % 3 == 0) {
            for(int k = 0; k < 26; k++) {
                printf("%c", border);
            }
           printf("\n");
        }
        for(int y = 0 ; y < 9 ; y++){
            if (y % 3 == 0) {
                printf("%c%c", border,border);
            }
            if (hidden_matrix[x][y] == 0){
                printf("[]");
            } else {
                printf("%d ", hidden_matrix[x][y]);
            }
        }
        printf("%c%c", border,border);
        printf("\n");
    }
    for(int k = 0; k < 26; k++) {
        printf("%c", border);
    }
    printf("\n");
}

void playGame() {
    int board[SIZE][SIZE];
    bool has_played = false;
    int my_num, row_pos, col_pos;
    startGame(board, has_played, row_pos, col_pos, my_num);

    printf("\n");

    for (int i = 0; i < 81; i++) {
        while (1)
        {
            printf("\nDigite a linha: ");
            if (scanf("%i", &row_pos) != 1 || row_pos < 1 || row_pos > 9 || row_pos == NULL) {
                printf("Numero invalido! ");
                i--;
                break;
            }
            printf("\nDigite a coluna: ");
            if (scanf("%i", &col_pos) != 1 || col_pos < 1 || col_pos > 9 || col_pos == NULL) {
                printf("Numero invalido! ");
                i--;
                break;
            }
            printf("\nDigite o numero: ");
            if (scanf("%i", &my_num) != 1 || my_num < 1 || my_num > 9 || my_num == NULL) {
                printf("Numero invalido! ");
                i--;
                break;
            } else {
                printMatrix(row_pos-1, col_pos-1, my_num);
            }
            break;
        }
    }
    has_played = true;
    printf("\n\n\n");
}

int main() {
    playGame();
    return 0;
}