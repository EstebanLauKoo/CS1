//Esteban Lau koo, class nbr:62226, Program1(Project1), 5/19/20

//allows us to include the library. This library includes printf, and scanf which we will use
#include <stdio.h>

//The define helps us state how much yarn is required per hat or sweater. better to write it this way to the program can be dynamic
#define YARN_PER_HAT 225
#define YARN_PER_SWEATER 450

//This is where we put the code for the program wrapped within main
int main() {

//Basic instatiation of the variables. One line is for the user values. and second line is for the calculations
int ballsYarn, yardEachBall, totalYards;
int possHat, possSweater;

//prompts the user to type the answer to each question and also grabs the user response.
printf("how many balls of yarn do you have?\n");
scanf("%d", &ballsYarn);

printf("How many yards are in each ball of yarn?\n");
scanf("%d", &yardEachBall);

//This calculates the total yards based on the user input
totalYards = ballsYarn * yardEachBall;

//This calculates the possible(poss) hats or sweaters that can be made
possHat = totalYards/YARN_PER_HAT;
possSweater = totalYards/YARN_PER_SWEATER;

//This will print out the calculated possibilities given the total yards of the user.
printf("You can make %d hats or %d sweaters.\n", possHat, possSweater);

//ends the program
return 0;

}