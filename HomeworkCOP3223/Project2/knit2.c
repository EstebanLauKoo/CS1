//Esteban Lau koo, class nbr:62226, Program2(Project2), 5/22/20

// this includes the packages we need including Pow()
#include <stdio.h>
#include <math.h>

// defines the necessary squares per blanket. Useful if we ever need to change it
#define SQUARES_PER_BLANKET 60

int main() {

// instantiating the variables.
int people, newSquares, blankets, remainingSquares;
double newPeople, power;

// prompt for user input and grabbing
printf("How many people are knitting blanket squares at the beginning of the week?\n");
scanf("%d", &people);

// checking that the number is a positive integer 
if (people < 0) 
{
    printf("This needs to be a positive integer");
}

else
{
    // prompt for sthe second question this time grabbing a long format number
    printf("How many new people are knitting blanket squares each day?\n");
    scanf("%lf", &newPeople);

    // a couple functions that helps us use pow, and calculate the blankets made and remaining squares using modulus.
    
    newSquares = pow(1 + newPeople, (double) 7) * people;

    blankets = newSquares / SQUARES_PER_BLANKET;
    
    remainingSquares = newSquares % SQUARES_PER_BLANKET;

    // checking for positive number
    if (newPeople < 0)
    {
        printf("This also needs to be a positive number");
    }

    // prints out answer.
    else
    {
        printf("%d blanket squares will be made this week!\n", newSquares);
        printf("You will be able to make %d blankets and start new week with %d squares", blankets, remainingSquares);
    }
    
    
}

return 0;

}