/*Sarah Angell
 *Homework 8, Functions
 *Assignment Scaffold
 */

#include <stdio.h>

//function prototypes
int exp(int base, int exponent);
/***Add the factorial function prototype here***/

//main function
int main(){
    int n, pow, result, option;

    printf("What would you like to do?\n");
    printf("1 - Calculate a power.\n");
    printf("2 - Calculate a factorial.\n");
    scanf("%d", &option);

    while (option != 1 && option != 2) {
        printf("Sorry, that was not a valid option.\n");
        printf("What would you like to do?\n");
        printf("1 - Calculate a power.\n");
        printf("2 - Calculate a factorial.\n");
        scanf("%d", &option);
    }

    if (option == 1) {
        printf("Please enter the base value.\n");
        scanf("%d", &n);

        printf("Please enter the exponent.\n");
        scanf("%d", &pow);

        while (pow < 0) {
            printf("Sorry, that was not a valid exponent.\n");
            printf("Please enter the exponent.\n");
            scanf("%d", &pow);
        }

        /***Add the function call for exp here***/

        printf("The result of %d raised to %d is %d.\n", n, pow, result);
    }
    else {
        printf("Please enter a value.\n");
        scanf("%d", &n);

        while (n <= 0 || n >= 13) {
            printf("Sorry, that was not a valid number.\n");
            printf("Please enter a value.\n");
            scanf("%d", &n);
        }

        result = fact(n);

        printf("%d! = %d.", n, result);
    }

    return 0;
}

// Precondition: base is a real number, exp >= 0
// Postcondition: Returns base raised to the exp power.
int exp(int base, int exponent) {
    int i, result = 1;

    for(i=0; i<exponent; i++)
        result *= base;

    return result;
}

/*** Add the factorial function here ***/
