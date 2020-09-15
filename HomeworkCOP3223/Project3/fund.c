//Esteban Lau koo, class nbr:62226, Program3(Project3), 5/31/20

#include <stdio.h>

// allows me to put these number threshholds and change accordingly
#define FIRST_SCHOLARSHIP 1000
#define SECOND_SCHOLARSHIP 500
#define THIRD_SCHOLARSHIP 250

int main() {

// variables for fund interest, rate and x,y,z to hold the values for the scholarships
float rate;
int x,y,z;
double fund, interest;

// user input questions
printf("How much was in the fund last year?\n");
scanf("%lf",&fund);
printf("What is the yearly percentage rate?\n");
scanf("%f",&rate);
   
// calculates the interest rate.   
interest = fund * rate * 0.01;

// checks to see how many 1000 scholarships you can have 
x = interest/FIRST_SCHOLARSHIP;

// if it reaches max then change x to 5
if (x > 5) {
    x = 5;
}
// then subtracts the x scholarships from the interest
interest = interest - x * FIRST_SCHOLARSHIP;

y = interest / SECOND_SCHOLARSHIP;

// limits the second to 10 scholarhips
if (y > 10) {
    y = 10;
}

// subtracts the value from interest
interest = interest - y * SECOND_SCHOLARSHIP;

// calculates how many 3rd scholars you can get
z = interest / THIRD_SCHOLARSHIP;

interest = interest - z / THIRD_SCHOLARSHIP;

// prints out the numbers for each scholarship
printf("%d $1000 scholarships will be awarded.\n", x);
printf("%d $500 scholarships will be awarded.\n", y);
printf("%d $250 scholarships will be awarded.\n", z);

return 0;
}