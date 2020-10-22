#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "leak_detector_c.h"


// Removes carriage return and/or line feed characters from a string
void remove_crlf(char *s)
{
    char *t = s + strlen(s);
    t--;

    while ((t >=s) && (*t == '\n' || *t == '\r'))
    {
        *t = '\0';
        t--;
    }
}

//Skips over blank lines
void get_next_nonblank_line(FILE *ifp, char *s, int max_length)
{
    s[0] = '\0';
    
    while (s[0] == '\0')
    {
        fgets(s, max_length, ifp);
        remove_crlf(s);
    }
}

typedef struct monster
{
    char *name;
    char *element;
    int population;
} monster;

typedef struct region {
    char *name;
    int numMonsters;
    int totPop;
    monster **monsters;
} region;

typedef struct itinerary {
    int regionsVisited;
    region **regions;
    int captures;
} itinerary;

typedef struct trainer {
    char *name;
    itinerary *visits;
} trainer;

//Individual Monsters--------------------------------------------------------

//Gets the number of monster species overall
int get_num_monsters(FILE *ifp)
{
    char s[200];
    int num;

    fgets(s, 199, ifp);
    sscanf(s, "%d monsters", &num);

    return num;
}

//Creates array for all monster species
monster *new_monster_array(int numSpecies)
{
    monster *m = calloc(numSpecies, sizeof(monster));
    
    return m;
}

//Helps with dispose function. De-allocates information on a monster
void clear_monster(monster *m)
{
    if(m->name != NULL)
    {
        free(m->name);
        m->name = NULL;
    }

    if(m->element != NULL)
    {
        free(m->element);
        m->element = NULL;
    }
    
    m->population = 0;
}

//Disposes of the monster array
void dispose_monster_array(monster *m, int numSpecies)
{
    for (int i = 0; i < numSpecies; i++)
    {
        clear_monster(m + i);
    }

    free(m);
}

//Allocates information on a monster
void fill_monster(monster *m, char *name, char *element, int population)
{
    m->name = strdup(name);
    m->element = strdup(element);
    m->population = population;
}

//Reads input to grab monster info
void read_monster(FILE *ifp, monster *m)
{
    char name[199];
    char element[199];
    char population_string[199];
    int population;

    fscanf(ifp, "%s %s %s", name, element, population_string);
    population = atoi(population_string);

    fill_monster(m, name, element, population);
}

//Prints monster to output
void print_monster(FILE *ofp, monster *m)
{
    fprintf(ofp, "Monster: %s   Element: %s   Population: %d\n", m->name, m->element, m->population);
}



//Regions-------------------------------------------------------

//Gets number of regions
int get_number_regions(FILE *ifp)
{
    char s[199];
    int num;

    fgets(s, 199, ifp);
    get_next_nonblank_line(ifp, s, 199);
    sscanf(s, "%d regions", &num);

    return num;
}

//Creates new region array


region *new_region_array(int numRegions)
{
    region *r = calloc(numRegions, sizeof(region));
    
    return r;
}

//Helps with dispose function. De-allocates information on a region
void clear_region(region *r)
{
    if(r->name != NULL)
    {
        free(r->name);
        r->name = NULL;
    }
    
    r->numMonsters = 0;
    r->totPop = 0;

    if(r->monsters != NULL)
    {
        free(r->monsters);
        r->monsters = NULL;
    }
}

//Disposes of the Regions array
void dispose_regions_array(region *r, int numRegions)
{
    for (int i = 0; i < numRegions; i++)
    {
        clear_region(r + i);
    }

    free(r);
}

//Allocates information on a region
void fill_region(region *r, char *name, int numMonsters, int totPop, monster **monsters)
{
    r->name = strdup(name);
    r->numMonsters = numMonsters;
    r->totPop = totPop;                
    r->monsters = monsters;            
}

//Creates dynamic empty monster array for each region
monster **monsters_in_region(int numMonsters)
{

    monster **monster_list= malloc(numMonsters * sizeof(monster *));

    return monster_list;
}

//Reads input to grab region info
void read_region(FILE *ifp, region *r, monster *m, int numSpecies)
{
    char name[199];
    char numMonsters_string[199];
    int numMonsters;
    int totPop = 0;
    char testMonster[128];
    monster **monster_list;

    get_next_nonblank_line(ifp, name, 199);
    get_next_nonblank_line(ifp, numMonsters_string, 199);
    numMonsters = atoi(numMonsters_string);


    printf("%d\n", numMonsters);
    monster_list = monsters_in_region(numMonsters);
    
    //Scans through monster names in monster struct for those in region and fills in the monster list
    char str1[199];
    char str2[199];
    int population = m->population;
    int length;

    for(int i = 0; i < numMonsters; i++)
    {
        get_next_nonblank_line(ifp, testMonster, 128);


        for(int j = 0; j < numSpecies; j++)
        {
            strcpy(str1, testMonster);
            strcpy(str2, (m + j)->name);
            
            if(strcmp(str1, str2) == 0)  //0 means they match
            {
                monster_list[i] = (m + j);
            }
            
        }
        totPop += monster_list[i]->population;
    };
    
fill_region(r, name, numMonsters, totPop, monster_list);
}

//Prints region to output
void print_region(FILE *ofp, region *r)
{

    fprintf(ofp, "Region: %s   Number of Monsters: %d   Total Population: %d\n", r->name, r->numMonsters, r->totPop);
    for(int i=0; i < r->numMonsters; i++)
    {
        fprintf(ofp, "Name: %s    Element: %s     Population %d\n", r->monsters[i]->name, r->monsters[i]->element, r->monsters[i]->population);
    }
    fprintf(ofp, "\n");
}

//itinerary-------------------------------------------------------

//Gets number of regions
int get_number_trainers(FILE *ifp)
{
    char s[199];
    int num;

    fgets(s, 199, ifp);
    get_next_nonblank_line(ifp, s, 199);
    sscanf(s, "%d Trainers", &num);

    return num;
}

//Creates new itinerary array
itinerary *new_itinerary_array(int numTrainers)
{
    itinerary *it = calloc(numTrainers, sizeof(itinerary));
    
    return it;
}

//Helps with dispose function. De-allocates information on a itinerary
void clear_itinerary(itinerary *it)
{   
    it->regionsVisited = 0;

    if(it->regions != NULL)
    {
        free(it->regions);
        it->regions = NULL;
    }

    it->captures = 0;
}

//Disposes of the itinerary array
void dispose_itinerary_array(itinerary *it, int numTrainers)
{
    for (int i = 0; i < numTrainers; i++)
    {
        clear_itinerary(it + i);
    }

    free(it);
}

//Allocates information on a itinerary
void fill_itinerary(itinerary *it, int regionsVisited, region **regions, int captures)
{
    it->regionsVisited = regionsVisited;
    it->regions = regions;
    it->captures = captures;
}

//Creates dynamic empty regions array for each trainer
region **regions_trainers(int regionsVisited)
{
    region **regions_trainers= malloc(regionsVisited * sizeof(region *));

    return regions_trainers;
}

//Reads input to grab itinerary info
void read_itinerary(FILE *ifp, itinerary *it, region *r, int numRegions)
{
    char regionsVisited_string[199];
    int regionsVisited;
    region **regions_list;
    char captures_string[199];
    int captures;
    char testRegion[199];

    get_next_nonblank_line(ifp, captures_string, 199);
    captures = atoi(captures_string);
    get_next_nonblank_line(ifp, regionsVisited_string, 199);
    regionsVisited = atoi(regionsVisited_string);

    regions_list = regions_trainers(regionsVisited);
    
    //Scans through region names and creates an array
    char str1[199];
    char str2[199];
    int length;

    for(int i = 0; i < regionsVisited; i++)
    {
        get_next_nonblank_line(ifp, testRegion, 128);


        for(int j = 0; j < numRegions; j++)
        {
            strcpy(str1, testRegion);
            strcpy(str2, (r + j)->name);
            
            if(strcmp(str1, str2) == 0)  //0 means they match
            {
                regions_list[i] = (r + j);
            } 
        }
    };
fill_itinerary(it, regionsVisited, regions_list, captures);
}


//Prints region to output
void print_itinerary(FILE *ofp, itinerary *it)
{

    fprintf(ofp, "# of regions: %d      # of captures: %d\n", it->regionsVisited, it->captures);
    for(int i=0; i < it->regionsVisited; i++)
    {
        fprintf(ofp, "Name: %s    # of Monsters: %d     Total Population %d\n", it->regions[i]->name, it->regions[i]->numMonsters, it->regions[i]->totPop);
    }
    fprintf(ofp, "\n");
}

//Trainer---------------------------------------------------
//creates new trainer array
trainer *new_trainer_array(int numTrainers)
{
     trainer *t = calloc(numTrainers, sizeof(trainer));
    
    return t;
}

//Helps with dispose function. De-allocates information on a itinerary
void clear_trainer(trainer *t)
{   
    if(t->name != NULL)
    {   

        free(t->name);
        t->name = NULL;
    }

    // if(t->visits != NULL)
    // {
    //     printf("%d regions visited\n", t->visits->regionsVisited);
    //     free(t->visits);        //gives me error cause values are 0
    //     t->visits = NULL;
    // }
}

//Disposes of the itinerary array
void dispose_trainer_array(trainer *t, int numTrainers){
    for (int i = 0; i < numTrainers; i++)
    {

        clear_trainer(t + i);
    }

    free(t);
}


//Will grab name BEFORE read_itinerary occurs and assigns it to trainer struct
void get_name(FILE *ifp, FILE *ofp, trainer *t)
{
    char name[199];

    get_next_nonblank_line(ifp, name, 199);

    t->name = strdup(name);
}

//moves itinerary struct information into trainer
void trainer_visits(trainer *t, itinerary *it)
{
        t->visits = it;

}

void print_trainers(FILE *ofp, trainer *t)
{
    fprintf(ofp, "Name: %s\n", t->name);
}

//Prints output that matches assignemnt (hopefully)
void print_final(FILE *ofp, trainer *t)
{
    int numCaptured;
    double freqCaught;

    //trainer's name
    fprintf(ofp, "%s\n", t->name);

    for (int i=0; i < t->visits->regionsVisited; i++)
    {
        //name of region
        fprintf(ofp, "%s\n", t->visits->regions[i]->name);

        for (int j=0; j < t->visits->regions[i]->numMonsters; j++)
        {
            freqCaught = ((double)t->visits->regions[i]->monsters[j]->population)/(t->visits->regions[i]->totPop);
            numCaptured = round((t->visits->captures) * freqCaught);

            if (numCaptured >= 1)
            {
                //# of captured Monsters and their names
                fprintf(ofp, "%d %s\n", numCaptured,t->visits->regions[i]->monsters[j]->name);

            }
        }
    }
    fprintf(ofp, "\n");
}

int main(void)
{
    atexit(report_mem_leak);

    FILE *ifp;
    FILE *ofp;

    int numSpecies;
    monster *monsters;
    int numMonsters;
    int numRegions;
    region *regions;
    int numTrainers;
    itinerary *itineraries;
    trainer *trainers;

    //for loops
    int i;

    // INPUT: "r"ead the input
    // OUTPUT: "w"rite to start new in output, "a"ppend to continue where it left off
    ifp = fopen("cop3502-as1-input.txt", "r");
    ofp = fopen("cop3502-as1-output-lam-mina.txt", "w");

    //Monsters
    numSpecies = get_num_monsters(ifp);

    
    monsters = new_monster_array(numSpecies);

    for (i=0; i < numSpecies; i++)
    {
        read_monster(ifp, monsters + i);
    }

    //Regions
    numRegions = get_number_regions(ifp);

    regions = new_region_array(numRegions);

    for (i=0; i < numRegions; i++)
    {
        read_region(ifp, regions + i, monsters, numSpecies);
    }


    //Itineraries & Trainers
    numTrainers=get_number_trainers(ifp);

    itineraries = new_itinerary_array(numTrainers);
    trainers = new_trainer_array(numTrainers);

    //trainers are allocated in here along with stuff for itinerary for proper scanning
    for (i=0; i < numTrainers; i++)
    {
        get_name(ifp, ofp, trainers + i);
        read_itinerary(ifp, itineraries + i, regions, numRegions);
        trainer_visits(trainers + i, itineraries + i);
    }

    //Final output
    for (i=0; i < numTrainers; i++)
    {
        print_final(ofp, trainers + i);
    }

    dispose_monster_array(monsters, numSpecies);
    dispose_regions_array(regions, numRegions);
    dispose_itinerary_array(itineraries, numTrainers);
    dispose_trainer_array(trainers, numTrainers);  


    fclose(ifp);
    fclose(ofp);

    return 0;
}
