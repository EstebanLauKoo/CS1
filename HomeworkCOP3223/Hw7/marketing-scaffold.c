// Original File by Arup Guha
// 8/17/2015

// Modified by Sarah Angell
// 2/10/2016

// Esteban Lau Koo Homework7

#include <stdio.h>

#define ROWS 20
#define COLS 5

int main() {
    // Open the input file and read in the number of cases to process.
    FILE* ifp = fopen("marketing.txt", "r");
    int loop, numCases, best, sum;
    int grid[ROWS][COLS], i, j;
    fscanf(ifp, "%d", &numCases);

    // Go through each input case.
    for (loop=0; loop<numCases; loop++) {

        // Get this input grid.
        for (i=0; i<ROWS; i++)
            for (j=0; j<COLS; j++)
                fscanf(ifp, "%d", &grid[i][j]);

        // Will store best value for row or column.
        best = 0;

        // This sets the sum at 0 to begin with
        int sum = 0;

        // this will add the values in each row and compare so it will go (0,0) (0,1) (0,2) (0,3) (0,4) (1,0) (1,1) ....
        for (i = 0; i < ROWS; i++) {

            for (j = 0; j < COLS; j++) {
                // adds the grid value to the sum until the row ends
                sum += grid[i][j];
            }
                // compares the current sum with the current best and replace if higher
            if (sum > best) {
                best = sum;
            }
            
            // resets sum to 0 for next row
            sum = 0;
            
        }

        // this will add the value in each collumn
        for (i = 0 ; i < COLS; i++) {
            for (j = 0; j < ROWS; j++) {
                // adds the grid value for the sum until the collunm ends
                sum += grid[j][i];
            }
            
            if (sum > best) {
                // compares the current sum with the current best and replaces if higher
                best = sum;
            }

            // resets sum to 0 for next row
            sum = 0;
        }

        // Output result.
        printf("%d\n", best);

    }

    fclose(ifp);
    return 0;
}
