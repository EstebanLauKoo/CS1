// Esteban Lau Koo Homework5
// 5/31/20


#include <stdio.h>

int main() {
    int num_rows, num_symbols, i, j;

    printf("How many rows for your star design?\n");
    scanf("%d", &num_rows);

    printf("How many stars on the first row?\n");
    scanf("%d", &num_symbols);

    /*** Add your loops here  ***/

    for(i = 0; i < num_rows; i++)

        if (i % 2) {

            for(j = 0; j < num_symbols - 1; j++) {
                printf(" *");
            }

            printf("\n");
        }

        else {

            for(j = 0; j < num_symbols; j++){
                printf("* "); 
            }
            
            printf("\n");
        }

    return 0;
}
