//Esteban Lau koo homework3

#include <stdio.h>

int main() {

// struggled with the float aspect of this along with the scanf for float.
float orangeCost, totalCost;
int cartons;

printf("What is the cost of one container of OJ in dollars?\n");
scanf("%f", &orangeCost);

printf("How many cartons are you buying?\n");
scanf(" %d", &cartons);

// if conditions let me know if the carton amounts are odd or even. I'm not sure if i need to wrap the condition operations but I did.
if (cartons % 2 == 0) {
    totalCost = (cartons / 2) * orangeCost;
}
    
else {
    totalCost = (cartons / 2) * orangeCost + orangeCost;
}

printf("The total cost is $%.2f.\n", totalCost);

return 0;

}