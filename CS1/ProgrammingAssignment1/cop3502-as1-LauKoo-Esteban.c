#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leak_detector_c.h"
#include <math.h>


typedef struct monster {
    int id;
    char *name;
    char *element;
    int population;
} monster;

typedef struct region {
    char *name;
    int nmonsters;
    int total_population;
    monster **monsters;
} region;

typedef struct itinerary {
    int numRegions;
    region **regions;
    int captures;
} itinerary;

typedef struct trainer {            
    char *name;
    itinerary *visits;
} trainer;

// This was given
void remove_crlf(char *s)
{
    char *t = s + strlen(s);

    // t begins at the null sentinel at the end of s.z

    t--;

    /* t is now at the last character of s - unless s didn't contain any characters, in which
       case, t is now *BEFORE* s.  We have to keep checking for that. */

    /* We repeat until EITHER t slides to the left of s, OR we find a character that is not a
       line feed (\n) or a carriage return (\r). */

    while ((t >= s) && (*t == '\n' || *t == '\r'))
    {
        *t = '\0'; // Clobber the character t is pointing at.
        t--;      // Decrement t.
    }
}


/* Get the next line from an input file that isn't blank, and leave it in s.  Will clobber
   s no matter what happens.  Will crash if there isn't a next blank line. 

   YOU ARE ALLOWED TO COPY THIS FUNCTION. */

void get_next_nonblank_line(FILE *ifp, char *s, int max_length)
{
    s[0] = '\0';

    while (s[0] == '\0')
    {
        fgets(s, max_length, ifp);
        remove_crlf(s);
    }
}

// gets the number of monsters from the ifp. and returns it
int get_number_of_monsters(FILE *ifp) {
    char s[128];
    int num;

    fgets(s, 127, ifp);
    sscanf(s, "%d monsters", &num);

    return num;
}

// creates the memory allocation for the monster array. and returns the object.
monster *new_monster_array(int nmonsters) {

    monster *m = calloc(nmonsters, sizeof(monster));
    
    return m;

}

// this clears the values within the monster array.
void clear_monster(monster *m ) {

    m -> id = 0;

    if (m->name != NULL) {
        free(m->name);
        m->name = NULL;
    } 
    
    if (m->element != NULL) {
        free(m->element);
        m->element = NULL;
    }

    m -> population = 0;
}

// frees the memory allocation of the monster array.
void dispose_monster_array(monster *m, int nmonsters) {
    
    // calls the clear monster function to remove the data within the structure
    for (int i = 0; i < nmonsters; i++) {
        clear_monster(m + i);
    }
    // frees the memory allocation.
    free(m);
}

// grabs the information that is passed through and fills in the corresponding parts of the structure.
void fill_monster(monster *m, int id, char *name, char *element, int population) {

    m -> id = id;
    m -> name = strdup(name);
    m -> element = strdup(element);
    m -> population = population;

}

/* Read a monster from our file. and directs to a fill function */
void read_monster(FILE *ifp, monster *m) {
    
    int id;
    char name[128];
    char element[128];
    char population_string[128];
    int population;

    // filler data for id (id is currently not used in any of the data)
    id = 1;

    // scans the the file for the corresponding values and names them accordingly
    fscanf(ifp, "%s %s %s", name, element, population_string);

    // turns the population string from the scanf into an integer called population
    population = atoi(population_string);

    // sends the information to the fill monster function in order to fill the corresponding data.
    fill_monster(m , id, name, element, population);

}

// prints the monster based on the given monster structure pointer.
void print_monster(FILE *ofp, monster *m) {
    fprintf(ofp, "Id: %d Monster: %s  Element: %s Population: %d\n",
            m->id, m->name, m->element, m->population);
}

// THIS STARTS REGION MEMORY ALLOCATION

// gets the number of regions from the ifp and returns it to main.
int get_number_of_regions(FILE *ifp) {
    char s[128];
    int num;

    get_next_nonblank_line(ifp, s, 127);
    sscanf(s, "%d regions", &num);

    return num;
}

// creates the regions array and returns the object.
region *new_region_array(int nregions) {

    region *r = calloc(nregions, sizeof(region));

    return r;

}

// clears the region data in each pointer
void clear_region(region *r ) {


    if (r->name != NULL) {
        free(r->name);
        r->name = NULL;
    } 

    r -> nmonsters = 0;

    r -> total_population = 0;

    if (r->monsters != NULL) {
        free(r->monsters);
        r->monsters = NULL;
    } 

}


// clears the regions and then frees the memory allocation
void dispose_region_array(region *r, int nregions) {
    

    for (int i = 0; i < nregions; i++) {

        clear_region(r + 1);
        free((r + i) -> monsters);
    }

    free(r);
}



// fills the region with the correct values in each area of the struct 
void fill_region(region *r, char *name , int nmonsters, int total_population, monster **monsters) {

    r -> name = strdup(name);
    r -> nmonsters = nmonsters;
    r -> total_population = total_population;
    r -> monsters = monsters;

}

// allocates the monster_list double pointer array.
monster **monsters_in_region(int numMonsters)
{
    monster **monster_list = malloc(numMonsters * sizeof(monster *));

    return monster_list;
}
// reads the region and creates the monster double pointer array.
void read_region(FILE *ifp, region *r, int nmonsters, monster *m) {
    int i;
    int k; 

    char name[128];
    char nmonstersinRegion_string[128];
    int nmonstersinRegion;
    monster **monster_list;

    char monsterName[128];

    int total_population;

    get_next_nonblank_line(ifp, name, 127);
    get_next_nonblank_line(ifp, nmonstersinRegion_string, 127);
    nmonstersinRegion = atoi(nmonstersinRegion_string);

    // creates the correct size array for each region for the monster**
    monster_list = monsters_in_region(nmonstersinRegion);

    char str1[128];
    char str2[128];
    int ret;
    
    total_population = 0;

    // searches through the monster array for a match to the monster name;
    for (i = 0; i < nmonstersinRegion; i++) {

        get_next_nonblank_line(ifp, monsterName, 128);

        for (k = 0; k < nmonsters; k++) {
            
            // does a string comparison between the file and the information from the monster array.
            strcpy(str1, monsterName);
            strcpy(str2, (m + k)->name);

            ret = strcmp(str1, str2);
            // sets the value of the monster list equal to the monster index
            if( ret == 0) {
                
                monster_list[i] = (m + k);

            }
            
 
        }        
        total_population += monster_list[i]->population;
    };

    fill_region(r , name, nmonstersinRegion, total_population, monster_list);

}

// prints the region if necessary to the ofp
void print_region(FILE *ofp, region *r) {

    fprintf(ofp, "name: %s #Monsters: %d  Total Population: %d \n",
            r->name, r->nmonsters, r->total_population);

}

// gets the number of trainers from the ifp and returns it
int get_number_of_trainers(FILE *ifp) {
    char s[128];
    int num;

    get_next_nonblank_line(ifp, s, 127);
    sscanf(s, "%d Trainers", &num);

    return num;
    
}

// starts the itinerary structures

// builds the new itinerary array and returns it
itinerary *new_itinerary_array(int ntrainers) {

    itinerary *iten = calloc(ntrainers, sizeof(itinerary));

    return iten;
}

// clears the values within the struct.
void clear_itinerary(itinerary *iten) {

    iten->numRegions = 0;

    if (iten->regions != NULL) {
        free(iten->regions);
        iten->regions = NULL;
    }

    iten->captures = 0;
    
}

// calls the clear itinerary and then frees the memory allocation
void dispose_itinerary_array(itinerary *iten, int ntrainers) {
    int i;

    for (i = 0; i < ntrainers; i++) {
        clear_itinerary(iten + i);
    }

    free(iten);
}

// fills the itinerary with the given information
void fill_itinerary(itinerary *iten, int nregions, region **regions, int captures)
{

    iten->numRegions = nregions;
    iten->regions = regions;
    iten->captures = captures;

}

// builds the regions** array
region **regions_trainers(int numRegions)
{
    region **regions_trainers= malloc(numRegions * sizeof(region *));

    return regions_trainers;
}

// reads teh itinerary and calls the fill function
void read_itinerary(FILE *ifp, itinerary *iten, region *r, int nregions) {
    char captures_string[128];
    char regionsGone_String[128];

    int captures;
    int regionsGone;

    region **regions_list;

    int i;
    int j;

    char str1[128];
    char str2[128];
    int length;
    int ret;

    char compRegion[128];

    // gets the next non blank lines for each and names it correctly.
    get_next_nonblank_line(ifp, captures_string, 127);
    captures = atoi(captures_string);


    get_next_nonblank_line(ifp, regionsGone_String, 127);
    regionsGone = atoi(regionsGone_String);

    // creates the regions array **
    regions_list = regions_trainers(regionsGone);

    // string compares and if its a match it places it on the regions_list;
    for (i = 0; i < regionsGone; i++) {
         get_next_nonblank_line(ifp, compRegion, 127);

        for (j = 0; j < nregions; j++) {

            strcpy(str1, compRegion);
            strcpy(str2, (r + j)->name);

            ret = strcmp(str1, str2);

            if(ret == 0) {
                
                regions_list[i] = (r + j);

             }
         }
     }
    // calls the fill itinerary with the correct information.
     fill_itinerary(iten, regionsGone, regions_list, captures);
}

// prints the itinerary if necessary
void print_itinerary(FILE *ofp, itinerary *iten) {
    int i;
    
    fprintf(ofp, "# of regions: %d  # of captures: %d \n", iten->numRegions, iten->captures);

    for(i = 0; i < iten->numRegions; i++) {
        fprintf(ofp, "Name: %s # of Monsters: %d Total Population %d\n", iten->regions[i]->name, iten->regions[i]->nmonsters, iten->regions[i]->total_population);
    }

    fprintf(ofp, "\n");
}

// creates the trainer array.
trainer *new_trainer_array(int ntrainers) {

    trainer *t = calloc(ntrainers, sizeof(trainer));
    
    return t;
}

// clears the trainer array values
void clear_trainer(trainer *t) {
    if (t->name != NULL) {

        free(t->name);
        t->name = NULL;
    }
}

// frees the allocation for the trainer array
void dispose_trainer_array(trainer *t, int ntrainers) {
    int i;

    for (i = 0; i < ntrainers; i++) {

        clear_trainer(t + i);
    
    }

    free(t);
}


// grabs the name and assigns it to the trainer struct.
void get_name(FILE *ifp, FILE *ofp, trainer *t)
{
    char name[199];

    get_next_nonblank_line(ifp, name, 199);

    t->name = strdup(name);

}

//links the itenerary struct in the trainers visit struct.
void trainer_visits(trainer *t, itinerary *iten)
{
        t->visits = iten;

}

// prints the trainers if necessary
void print_trainers(FILE *ofp, trainer *t)
{
    fprintf(ofp, "Name: %s\n", t->name);
}

// prints the information into the ofp
void ofp_print(FILE *ofp, trainer *t)
{
    int numCaptured;
    double freqCaught;
    int sizeofArray;

    // prints the trainers name
    fprintf(ofp, "%s\n", t->name);

    // loops through the array based on num of regions each trainer has
    for (int i=0; i < t->visits->numRegions; i++)
    {
        //name of region
        fprintf(ofp, "%s\n", t->visits->regions[i]->name);


        for (int j=0; j < t->visits->regions[i]->nmonsters; j++)
        {
            sizeofArray = sizeof(t->visits->regions[i]->monsters);

            freqCaught = ((double)t->visits->regions[i]->monsters[j]->population)/(t->visits->regions[i]->total_population);
            numCaptured = round((t->visits->captures) * freqCaught);
 
            if (numCaptured >= 1)
            {
                //prings the number of capturea and the name.
                fprintf(ofp, "%d %s\n", numCaptured,t->visits->regions[i]->monsters[j]->name);

            }
        }
    }
    fprintf(ofp, "\n");
}



int main (void) {
    atexit(report_mem_leak);

    FILE *ofp;
    FILE *ifp;

    int nmonsters;
    monster *monsters;
    int nregions;
    region *regions;
    int ntrainers;
    itinerary *itineraries;
    trainer *trainers;

    int i;

    // ifp and ofp files
    ifp = fopen("cop3502-as1-input.txt", "r");
    ofp = fopen("cop3502-as1-out-LauKoo-Esteban", "w");

    // assigns nmonsters and monsters to the values returned by each function
    nmonsters = get_number_of_monsters(ifp);

    monsters = new_monster_array(nmonsters);
   
    for (i = 0; i < nmonsters; i++) {
        read_monster(ifp, monsters + i );
    }


    // starts the region set up
    nregions = get_number_of_regions(ifp);

    regions = new_region_array(nregions);


    for (i = 0; i < nregions; i++) {
        read_region(ifp, regions + i, nmonsters, monsters);
    }
    
    // starts the trainers and itineraries set up
    ntrainers = get_number_of_trainers(ifp);

    itineraries = new_itinerary_array(ntrainers);

    trainers = new_trainer_array(ntrainers);

    for (i = 0; i < ntrainers; i++) {

        get_name(ifp, ofp, trainers + i);
        read_itinerary(ifp, itineraries + i, regions, nregions);
        trainer_visits(trainers + i, itineraries + i);
    }
    
    for (i = 0; i < ntrainers; i++)
    {
        ofp_print(ofp, trainers + i);
    }

    dispose_monster_array(monsters, nmonsters);



    dispose_region_array(regions, nregions);  
    dispose_itinerary_array(itineraries, ntrainers);
    dispose_trainer_array(trainers, ntrainers);

    fclose(ifp);
    fclose(ofp);

    return 0;
}

