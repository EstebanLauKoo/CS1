// Esteban Lau Koo Homework4

#include <stdio.h>

// This helps me understand at what number I need to send the notice
#define DOLLAR_NOTICE 10.00

int main() {
    // instantiat variables (Am I allowed to camelcase?)
    int ounces , iterations , ouncesTotal , ouncesDrank , ounceThreshhold;
    float ojCost, totalCost;  

    // this is just asking for user input
    printf("What is the weight (in oz.) of the original container of OJ?\n");
    scanf("%d", &ounces);

    printf("What is the cost of the original container of OJ in dollars?\n");
    scanf("%f", &ojCost);

    // This helps me know at what ounce number do i need to set the notification about owing
    ounceThreshhold = (DOLLAR_NOTICE / ojCost) * ounces;

    printf("How many times did you roommate take your juice?\n");
    scanf("%d", &iterations);

    // sets the total ounces before the loop to 0
    ouncesTotal = 0;

    // a loop that asks the question as the amount of times the roommate drank the oj. I could have done a for loop also here
    while(iterations > 0 ) {
        
        // asks the question about how many ounces taken
        printf("How much juice did your roommate take this time (in oz.)?\n");
        scanf("%d", &ouncesDrank);

        
        // this helps me figure out many ounces in total printf("OunceTotal: %d\n", ouncesTotal);
        
        // adds the total to preexisting value
        ouncesTotal += ouncesDrank;

        // calculates the total cost 
        totalCost = ((double) ouncesTotal / (double) ounces) * (double) ojCost;
        
        // checks if the total cost is above 10, substract 10 dollars and continues the process 
        if (totalCost >= 10) {
            printf("Your roommate owes you $10.00.\n");
            totalCost = totalCost - DOLLAR_NOTICE;
            ouncesTotal = ouncesTotal - ounceThreshhold;
        }
        // substract one iteration and continues the loop until it equals 0
        iterations--;
    }

    printf("Your roommate owes you $%.2f.\n", totalCost);

return 0;

}