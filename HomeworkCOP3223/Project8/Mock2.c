//declare header files

#include <stdio.h>

#include <string.h>

#define TEAMS 200

#define RUNNERS 10000

#define LENGTH 20

#define TEAMSIZE 50

#define NUMAGEGROUPS 10

// declare structure of a person

struct person {

char name[LENGTH];

int number;

int age;

int event;

float money;

float time;

};

//declare structure for team

struct team {

char name[LENGTH];

int nummembers;

float money;

struct person members[TEAMSIZE];

};

//declare structure for age group

struct agegroups {

int startAge;

int endAge;

int qualTime;

};

//declare filer objects for input and output

FILE *inptr;

FILE *optr;

//Function prototypes

void individual_registration(struct person *, FILE *,

float, int * ,FILE *fptr);

void teamRegistration(struct person * participant, struct team * teams, FILE * ifp,

float , int *, int *, FILE *);

void runEvents(struct person *, struct team *, FILE *,

int *, struct agegroups *, FILE *);

//main method

int main()

{

//Declare array of structure

//partcipants structure

struct person *p[RUNNERS];

//declare team structures

struct team *t[TEAMSIZE];

//declare age group structures

struct agegroups * group[NUMAGEGROUPS];

//declare float values

float earlyCost, lateCost, teamCost;

//declare temporary integer values

int numReg, numLateReg, i, runnerCount = 0, teamCount = 0;

char input[4];

// Declare a file pointer ifp

optr = fopen("race01.out", "w");

//open the input file in read mode

inptr = fopen("race01.txt", "r");

//read the input values

fscanf(inptr, "%f %f %f", &earlyCost, &lateCost, &teamCost);

//read how many registrations

fscanf(inptr, "%d", &numReg);

//use for-loop to read the values

for (i = 0; i < numReg; i++)

{

//read the type of registration

fscanf(inptr, "%s", &input);

//compare is input is INDV

if (strcmp(input, "INDV") == 0)

{

//call the method to pass the partcicipant struct and output file pointer

individual_registration(p, inptr, earlyCost, &runnerCount, optr);

}

//compare is input is TEAM

else if (strcmp(input, "TEAM") == 0)

{

//call the method to pass the partcicipant struct and output file pointer

teamRegistration(p, t, inptr, teamCost, &runnerCount, &teamCount, optr);

}

}

//read number of registerrations

fscanf(inptr, "%d", &numLateReg);

// For every person (individual) that registered late...

for (i = 0; i < numLateReg; i++)

{

individual_registration(p, inptr, lateCost, &runnerCount, optr);

}

//Call the function to compute runnercount

runEvents(p, t, inptr, &runnerCount, group,optr);

//close the file pointers

fclose(inptr);

fclose(optr);

system("pause");

return 0;

}

//Implement the function individual_registration

void individual_registration(struct person *p, FILE * ifp,

float regCost, int * runnerCount, FILE *fptr) {

//declare character array for event name

char eventName[9];

int i = *runnerCount;

//check if the count is equal to constant value

if (i <= RUNNERS)

{

//read the name,age,event type,money

fscanf(ifp, "%s", &p[i].name);

fscanf(ifp, "%d", &p[i].age);

fscanf(ifp, "%d", &p[i].event);

fscanf(ifp, "%f", &p[i].money);

// If the runner the 5k (event type of 5)

if (p[i].event == 5)

{

strcpy(eventName, "5k");

}

// If the runner the 10k (event type of 10)

else if (p[i].event == 10) {

strcpy(eventName, "10k");

}

// If the runner ran the marathon (event type of 42)

else if (p[i].event == 42)

{

strcpy(eventName, "marathon");

}

// Add one to our runner count pointer after we've registered them

*runnerCount += 1;

//print it to the file

fprintf(fptr,"%s registered for the %s race! They have been assigned the number %d.\n",

p[i].name, eventName, *runnerCount);

}

else

{

// If the number of registered runners is greater than 10,000

fprintf(fptr,"We can only have at most 10,000 runners, sorry!\n");

}

}

//implement method for teamRegistration

void teamRegistration(struct person * p, struct team * teams, FILE * ifp,

float regCost, int * runnerCount, int * teamCount, FILE *fptr) {

//declare array for team name

char teamName[LENGTH];

int count, i;

// If the number of teams registered is less than our max (TEAMS)

if (*teamCount <= TEAMS)

{

//read the input name and numbers from file

fscanf(ifp, "%s", &teamName);

fscanf(ifp, "%d", &count);

//assign values to the variable of structure

for (i = 0; i < *teamCount; i++)

{

strcpy(teams[i].name, teamName);

teams[i].nummembers = count;

}

//print lines in the file

fprintf(fptr,"\n");

//print the name and count

fprintf(fptr,"%s team registered for the event. They have %d members:", teamName, count);

fprintf(fptr,"\n");

// For i < the number of members in the team

for (i = 0; i < count; i++)

{

individual_registration(p, ifp, regCost, runnerCount,fptr);

}

*teamCount += 1;

fprintf(fptr,"\n");

}

// Else, if the number of teams is greater than 200

else

{

fprintf(fptr,"We can only have at most 200 teams registered, sorry!\n");

}

}

//implement method runEvents

void runEvents(struct person * p, struct team * teams, FILE * ifp, int * rc,

struct agegroups * group, FILE *fptr)

{

//declare local variables

int i, j, runnerNum, eventTime;

float short5k, short10k;

char winner5k[20], winner10k[20];

// Assign the time everyone got for their event

for (i = 0; i < *rc; i++)

{

//read the values from file

fscanf(ifp, "%d %d", &runnerNum, &eventTime);

p[i].time = eventTime;

}

//use for-loop to set the value

for (i = 0; i < *rc; i++)

{

//if event is 5k race

//then set the respective time

if (p[i].event == 5)

{

short5k = p[i].time;

}

//if event is 10k race

//then set the respective time

else if (p[i].event == 10)

{

short10k = p[i].time;

}

}

// Get every age group and their qualifying times

for (i = 0; i < NUMAGEGROUPS; i++)

{

fscanf(ifp, "%d %d %d", &group[i].startAge, &group[i].endAge, &group[i].qualTime);

fprintf(fptr, "\n");

for (i = 0; i < *rc; i++)

{

// For i is less than the number of runners

//if the race is 5k

if (p[i].event == 5)

{

if (p[i].time < short5k)

{

// Make their time the new shortest 10k time

short5k = p[i].time;

//set the wiinner

strcpy(winner5k, p[i].name);

}

}

else if (p[i].event == 10)

{

if (p[i].time < short10k)

{

// Make their time the new shortest 10k time

short10k = p[i].time;

//set the wiinner

strcpy(winner10k, p[i].name);

}

}

// If the person ran a marathon

else if (p[i].event == 42)

{

// For j is less than the number of age groups (10)

for (j = 0; j < NUMAGEGROUPS; j++) {

if ((p[i].age >= group[j].startAge) && (p[i].age <= group[j].endAge))

{

// If they qualified...

if (p[i].time <= group[j].qualTime)

{

fprintf(fptr, "%s qualified in the marathon run with a time of %.1f minutes!\n", p[i].name, p[i].time); // Say that they qualified

}

}

}

}

}

}

//print the winner for 5k race

fprintf(fptr, "5k race: %s had the fastest time with %.1f minutes!\n", winner5k, short5k);

//print the winner for 10k race

fprintf(fptr, "10k race: %s had the fastest time with %.1f minutes!\n", winner10k, short10k);

}