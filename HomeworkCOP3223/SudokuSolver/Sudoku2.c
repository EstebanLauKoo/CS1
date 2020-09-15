#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>

// creates a set of arrays for sudoku numbers

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

// defines the row and data
struct data {
    int row;            
    int col;
};


// checks row and collumn

void *row_col (void *d) {

int n , m , h = 0;
int k;

m = (int) d;

//loops through the row and collumn and looks for any copy number. by incrementing the value
for(int i = 0; i < 9; i++){

    k = 1;

        while( k < 10 ) {

            for(int j = 0; j < 9; j++) {

                if (m == 0 && sudoku[i][j] == k){

                        h++;
                        goto Extra;

                }

                else if ( m == 1 && sudoku[j][i] == k) {

                        h++;
                        goto Extra;

                }
            }

            Extra:
            k++;

        }
}

    if (h == 81) {

        n = 1;

    }

    else {

        n = -1;

    }

pthread_exit((void*)n);

}

// checks the 3x3 qudrant 

void *square_check(void *mn) {

struct data *my_data=(struct data *)mn;

int i = (*my_data).row;
int j = (*my_data).col;

int n , m, p;

n = i + 3;
m = j + 3;

int k = 0; 
int h = 0;

// goes through the square.
for( k = 1; k < 10; k++){

    for( i = 0; i < n; i++){

        for( j = 0; j < m; j++){

            if(sudoku[i][j] == k){

                    h++;
                    i = n;
                    j = m;

                }

         }
    }

}

// checks if true based on the h++

if( h == 9){
    p = 1;
}

else{
    p = -1;
}

pthread_exit((void*)p);

}

int main() {

struct data *p;

p = (struct data*) malloc (sizeof(struct data));

pthread_t thread[11];

int i , a;
void *b;
int t , l, k;

// creates a row col check.

for(i = 0; i < 2; i++){

    t = i;

    a = pthread_create(&thread[i], NULL, row_col, (void*)t);

}

// creates a square check.

for( l = 0; l <= 6; l = l + 3){

    for(k = 0; k <= 6; k = k + 3){

        (*p).row = l;
        (*p).col = k;

        a = pthread_create(&thread[i++], NULL, square_check, (void*)p);

    }
}


// determines the result based on the s values from join.
int s = 0;

    for (i = 0; i < 11; i++){

    pthread_join(thread[i],&b);
    s = s + (int) b;

    }

    if ( s == 11){

    printf("Sudoku valid\n");

    }

    else{

    printf("Sudoku invalid\n");

    }

pthread_exit(NULL);

}
