#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <pthread.h>

#define NUM_OF_THREADS 27

int valid[NUM_OF_THREADS] = {0};

typedef struct {

int row;

int column;   

} parameters;

int sudoku[9][9] = {

{2, 7, 6, 3, 1, 4, 9, 5, 8},

{8, 5, 4, 9, 6, 2, 7, 1, 3},

{9, 1, 3, 8, 7, 5, 2, 6, 4},

{4, 6, 8, 1, 2, 7, 3, 9, 5},

{5, 9, 7, 4, 3, 8, 6, 2, 1},

{1, 3, 2, 5, 9, 6, 4, 8, 7},

{3, 2, 5, 7, 8, 9, 1, 4, 6},

{6, 4, 1, 2, 5, 3, 8, 7, 9},

{7, 8, 9, 6, 4, 1, 5, 3, 2}

};

// checks the collum 

void *CollumnValidator(void* param) {

  
parameters *params = (parameters*) param;

// passes parameters to row and col

int row = params -> row;

int col = params -> column;   

// checks for 

if (row != 0 || col > 8) {

fprintf(stderr, "Invalid row or column for col subsection! row=%d, col=%d\n", row, col);

pthread_exit(NULL);

}


int validityArray[9] = {0};

int i;   

for (i = 0; i < 9; i++) {

int num = sudoku[i][col];

if (num < 1 || num > 9 || validityArray[num - 1] == 1) {

pthread_exit(NULL);

} else {

validityArray[num - 1] = 1;

}

}

valid[18 + col] = 1;

pthread_exit(NULL);

}

void *isRowValid(void* param) {


parameters *params = (parameters*) param;

int row = params->row;

int col = params->column;   

if (col != 0 || row > 8) {

fprintf(stderr, "Invalid row or column for row subsection! row=%d, col=%d\n", row, col);

pthread_exit(NULL);

}


int validityArray[9] = {0};

int i;

for (i = 0; i < 9; i++) {

int num = sudoku[row][i];

if (num < 1 || num > 9 || validityArray[num - 1] == 1) {

pthread_exit(NULL);

} else {

validityArray[num - 1] = 1;

}

}

valid[9 + row] = 1;

pthread_exit(NULL);

}


void *is3x3Valid(void* param) {


parameters *params = (parameters*) param;

int row = params->row;

int col = params->column;   

if (row > 6 || row % 3 != 0 || col > 6 || col % 3 != 0) {

fprintf(stderr, "Invalid row or column for subsection! row=%d, col=%d\n", row, col);

pthread_exit(NULL);

}

int validityArray[9] = {0};

int i, j;

for (i = row; i < row + 3; i++) {

for (j = col; j < col + 3; j++) {

int num = sudoku[i][j];

if (num < 1 || num > 9 || validityArray[num - 1] == 1) {

pthread_exit(NULL);

} else {

validityArray[num - 1] = 1;

}

}

}

valid[row + col/3] = 1;

pthread_exit(NULL);

}

int main() {

pthread_t threads[NUM_OF_THREADS];

int threadIndex = 0;   

int i,j;


for (i = 0; i < 9; i++) {

for (j = 0; j < 9; j++) {   

if (i%3 == 0 && j%3 == 0) {

parameters *data = (parameters *) malloc(sizeof(parameters));

data->row = i;

data->column = j;

pthread_create(&threads[threadIndex++], NULL, is3x3Valid, data);

}

if (i == 0) {

parameters *columnData = (parameters *) malloc(sizeof(parameters));

columnData->row = i;   

columnData->column = j;

pthread_create(&threads[threadIndex++], NULL, CollumnValidator, columnData);

}

if (j == 0) {

parameters *rowData = (parameters *) malloc(sizeof(parameters));   

rowData->row = i;

rowData->column = j;

pthread_create(&threads[threadIndex++], NULL, isRowValid, rowData);

}

}

}

for (i = 0; i < NUM_OF_THREADS; i++) {

pthread_join(threads[i], NULL);   

}

for (i = 0; i < NUM_OF_THREADS; i++) {

if (valid[i] == 0) {

printf("Sudoku solution is invalid!\n");

return EXIT_SUCCESS;

}

}

printf("Sudoku solution is valid!\n");

return EXIT_SUCCESS;

}