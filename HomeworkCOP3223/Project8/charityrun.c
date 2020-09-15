//Esteban Lau koo, class nbr:62226, Program 8(Project8), 7/26/20
//Finished Processing individual, team registration, and running events.
//Part 4 would loop through the arrays find the money values for each team and compare with other.
//Then you can print out highest along with total value. you would do another loop inside to go through the team members and find the highest value there by comparison and print that out.
//then another loop to find all individuals and comparen their values to find the highest. 
//Through the for loop for inviduals you would add all the values into a float total nad pring that out last.


//header files
#include <stdio.h>
#include <string.h>

#define TEAMS 200
#define RUNNERS 10000
#define LENGTH 20
#define TEAMSIZE 50
#define NUMAGEGROUPS 10

// the structures for person team and age group
struct person {
    char name[LENGTH];
    int number;
    int age;
    int event; 
    float money;
    float time;
};

struct team {
    char name[LENGTH];
    int nummembers;
    float money;
    struct person members[TEAMSIZE];
};

struct agegroups {

int startAge;

int endAge;

int qualTime;

};

// file input and output
FILE *inptr;

FILE *optr;

// the function prototypes

void indRegistration(struct person *, FILE *, float, int *, FILE *(fptr));

void teamRegistation(struct person * participant, struct team * teams, FILE * ifp, float , int *, int *, FILE *);

void runEvents(struct person *, struct team *, FILE *, int *, struct agegroups *, FILE *);

//main

int main () {

    // structures
    struct person *p[RUNNERS];

    struct team *t[TEAMSIZE];

    struct agegroups * group[NUMAGEGROUPS];

    // first line values
    float earlyBird, lateBird, teamCost;

    int numReg, i , j, numLateReg, runnerCount = 0, teamCount = 0;

    char input[4];

    //which file to read and write

    optr = fopen("race03.out", "w");

    inptr = fopen("race03.txt", "r");

    fscanf(inptr, "%f %f %f", &earlyBird, &lateBird, &teamCost);

    fscanf(inptr, "%d", &numReg);

    //loops through and registers people and teams

    for (i = 0; i < numReg; i++) {
        fscanf(inptr, "%s", &input);

        if (strcmp(input, "INDV") == 0) {
            indRegistration(p , inptr, earlyBird, &runnerCount, optr);
        }

        else if (strcmp(input, "TEAM") == 0) {

            teamRegistation(p, t, inptr, teamCost, &runnerCount, &teamCount, optr);

        }
    }

    //reads the 3 of late registers and goes through registering them

    fscanf(inptr, "%d", &numLateReg);

    for (j = 0; j < numLateReg; j++) {
        indRegistration(p, inptr, lateBird, &runnerCount, optr);      
    }

    // call the method
    runEvents(p , t ,inptr, &runnerCount, group, optr);

    fclose(inptr);
    fclose(optr);



    return 0;
}

void indRegistration(struct person *p, FILE * ifp, float cost, int * runnerCount, FILE *fptr) {

    char race[9];

    int i = *runnerCount;

    // grabs their values from .txt
    // assigns race to the correct value
    // prints the assignment

    if( i <= RUNNERS) {

        fscanf(ifp, "%s", &p[i].name);
        fscanf(ifp, "%d", &p[i].age);
        fscanf(ifp, "%d", &p[i].event);
        fscanf(ifp, "%f", &p[i].money);

        if (p[i].event == 5) {
            strcpy(race, "5k");
        }

        else if (p[i].event == 10) {
            strcpy(race, "10k");
        }

        else if (p[i].event == 42) {
            strcpy (race, "marathon");
        }

        *runnerCount += 1;

        fprintf(fptr, "%s registered for the %s race!  They have been assigned the number %d.\n", p[i].name, race, *runnerCount);

    }

    else {
        fprintf(fptr, "Sorry too many runners!!\n");
    }
}


void teamRegistation(struct person * p, struct team * teams, FILE * ifp, float cost , int * runnerCount, int * teamCount, FILE *fptr){
    
    char teamName[LENGTH];

    int count, i;

    // grabs team name and number of people assigns values. and prints to file
    if ( *teamCount <= TEAMS) {
        fscanf(ifp, "%s", &teamName);
        fscanf(ifp, "%d", &count);

        for (i = 0; i < *teamCount; i++) {
            strcpy(teams[i].name, teamName);
            teams[i].nummembers = count;
        }

        fprintf(fptr, "\n");

        fprintf(fptr, "%s team registered for the event. They have %d members:", teamName, count);

        fprintf(fptr, "\n");

        for (i = 0; i < count; i++) {

            indRegistration(p, ifp, cost, runnerCount, fptr);

        }

        *teamCount++;

        fprintf(fptr, "\n");
    }

    else {
        fprintf(fptr, "Too many teams registered.");
    }
}

void runEvents(struct person * p, struct team * teams, FILE * ifp, int * rc, struct agegroups * group, FILE *fptr) {
    int i, j, runnerNum, eventTime;
    float short5k, short10k;
    char winner5k[20], winner10k[20];

    
    for (i = 0; i < *rc; i++) {

        fscanf(ifp, "%d %d", &runnerNum, &eventTime);
        p[i].time = eventTime;

    }
    // 
    for (i = 0; i < *rc; i++) {

        if (p[i].event == 5) {
            short5k = p[i].time;
        }

        else if (p[i].event == 10) {
            short10k = p[i].time;
        }

    }

    for (i = 0; i < NUMAGEGROUPS; i++) {

        fscanf(ifp, "%d %d %d", &group[i].startAge, &group[i].endAge, &group[i].qualTime);
        fprintf(fptr, "\n");

        for (i = 0; i < *rc; i++) {

            if (p[i].event == 5) {
                if (p[i].time < short5k) {
                    short5k = p[i].time;
                    strcpy(winner5k, p[i].name);
                }
            }

            else if (p[i].event == 10) {
                if (p[i].time < short10k) {
                    short10k = p[i].time;
                    strcpy(winner10k, p[i].name);
                }
            }

            else if (p[i].event == 42) {
                for (j = 0; j < NUMAGEGROUPS; j++) {
                    if ((p[i].age >= group[j].startAge ) && (p[i].age <= group[j].endAge)) {
                        if (p[i].time <= group[j].qualTime) {
                            fprintf(fptr, "%s qualified in the marathon run with a time of %.1f minutes\n", p[i].name, p[i].time);
                        }
                    }
                }
            }

        }
    }

    fprintf(fptr, "5k race: %s had the fastest time with %.1f minutes!\n", winner5k, short5k);

    fprintf(fptr, "10k race: %s had the fastest time with %.1f minutes!\n", winner10k, short10k);
}


