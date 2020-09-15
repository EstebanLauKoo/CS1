d//Esteban Lau koo homework1

//pre-processor directives
#include <stdio.h>

#define CALS_PER_GR_PROTEIN 4
#define CALS_PER_GR_CARB 4
#define CALS_PER_GR_FAT 9

//main function
int main() {

int gramProtein, gramCarb, gramFat;
int calProtein, calCarb, calFat;
int totalCal;   

printf("How many grams of protein did you eat?\n");
scanf("%d", &gramProtein);

printf("How many grams of carbohydrates did you eat?\n");
scanf("%d", &gramCarb);

printf("how many grams of fat did you eat?\n");
scanf("%d", &gramFat);

calProtein = gramProtein * CALS_PER_GR_PROTEIN;
calCarb = gramCarb * CALS_PER_GR_CARB;
calFat = gramFat * CALS_PER_GR_FAT;
totalCal = calProtein + calCarb + calFat;

printf("You ate %d calories of food.\n", totalCal);
 
return 0;

}