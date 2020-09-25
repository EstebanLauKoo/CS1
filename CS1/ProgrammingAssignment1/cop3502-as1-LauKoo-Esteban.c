#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leak_detector_c.h"


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


void fill_monster(monster *m, int id, char *name, char *element, int population) {

    m -> id = id;
    m -> name = strdup(name);
    m -> element = strdup(element);
    m -> population = population;

}

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

monster **new_monster_list(int nmonstersinRegion) {

    monster **monster_list = malloc(nmonstersinRegion * sizeof(monster *));

}

monster *new_monster_array(int nmonsters) {

    monster *m = calloc(nmonsters, sizeof(monster));

}

void dispose_monster_array(monster *m, int nmonsters) {
    
    for (int i = 0; i < nmonsters; i++) {
        clear_monster(m + i);
    }

    free(m);
}


int get_number_of_monsters(FILE *ifp) {
    char s[128];
    int num;

    fgets(s, 127, ifp);
    sscanf(s, "%d", &num);

    return num;
}

void remove_crlf(char *s)
{
    char *t = s + strlen(s);

    // t begins at the null sentinel at the end of s.

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



// potential might use
// void get_next_char(FILE *ifp, char *s, int max_length) {
//     s[0] = ' ';

//     while (s[0] == ' ') {
//         fgets(s, max_length, ifp);
//         remove_crlf(s);
//     }
// }

/* Read a monster from our file. */

void read_monster(FILE *ifp, monster *m, int idnum) {
    
    int id;
    char name[128];
    char element[128];
    char population_string[128];
    int population;

    fscanf(ifp, "%s %s %s", name, element, population_string);

    // work on parsing it correctly this doesn't work accurately right now
    population = atoi(population_string);



    fill_monster(m , idnum, name, element, population);


}

void print_monster(FILE *ofp, monster *m) {
    fprintf(ofp, "Id: %d Monster: %s  Element: %s Population: %d\n",
            m->id, m->name, m->element, m->population);
}


// THIS STARTS REGION MEMORY ALLOCATION

void fill_region(region *r, char *name , int nmonsters, int total_population, monster **monsters) {

    r -> name = strdup(name);
    r -> nmonsters = nmonsters;
    r -> total_population = total_population;
    r -> monsters = monsters;

}

void clear_region(region *r ) {


    if (r->name != NULL) {
        free(r->name);
        r->name = NULL;
    } 

    r -> nmonsters = 0;

    r -> total_population = 0;

    // r -> monsters = 0;

    if (r->monsters != NULL) {
        free(r->monsters);
        r->monsters = NULL;
    } 

}

region *new_region_array(int nregions) {

    region *r = calloc(nregions, sizeof(region));

}

void dispose_region_array(region *r, int nregions) {
    
    for (int i = 0; i < nregions; i++) {
        clear_region(r + 1);
    }

    free(r);
}


int get_number_of_regions(FILE *ifp) {
    char s[128];
    int num;

    get_next_nonblank_line(ifp, s, 127);
    sscanf(s, "%d", &num);

    return num;
}

// int get_total_population(region *r) {
//     int i;
//     int num;

//     // num monsters inst filled in the region

//     printf("%d \n ", r->nmonsters);

//     // for (i = 0; i < r->nmonsters; i++) {
//     //     num += r->monsters[i]->population;
//     //     printf("%d \n",  r->monsters[i]->population);
//     //     printf("%s: %d \n", r->monsters[i]->name, r->monsters[i]->population);
//     // }

//     return num;
// }

/* Read a monster from our file. */

// needs to be worked on 
void read_region(FILE *ifp, region *r, int nmonsters, monster *m) {
    
    int i;
    int k; 
    int j;

    // srand((unsigned int) time(&t));

    char name[128];
    char nmonstersinRegion_string[128];
    int nmonstersinRegion;

    char monsterName[128];
    // this might not be needed
    // char total_population_string[128];
    int total_population;

    // this is needed just don't know how to link double pointers
    // monster monsters;


    get_next_nonblank_line(ifp, name, 127);
    get_next_nonblank_line(ifp, nmonstersinRegion_string, 127);
    nmonstersinRegion = atoi(nmonstersinRegion_string);


    monster **monster_list;

    // monster_list = malloc(nmonstersinRegion * sizeof(monster *));
    total_population = 0;
    // searches through the monster array for a match to the monster name;
    for (i = 0; i < nmonstersinRegion; i++) {

        monster_list = new_monster_list(nmonstersinRegion);

        fscanf(ifp, "%s", monsterName);

        for (k = 0; k < nmonsters; k++) {

            char str1[128];
            char str2[128];
            int ret;


            strcpy(str1, monsterName);
            strcpy(str2, (m + k)->name);

            ret = strcmp(str1, str2);
            if( ret == 0) {

                monster_list[k] = (m + k);

                // printf("%d total population;" ,total_population);

                total_population += monster_list[k]->population;

                printf("match found %s = %s population: %d total population = %d \n", str1, monster_list[k]->name, monster_list[k]->population, total_population);
                    // int j;

                    // for (j = 0; i < nmonstersinRegion; i++) {
                    //     printf("id: %d, name: %s, element: %s, population: %d", 
                    //             monster_list[j]->id, monster_list[j]->name, monster_list[j]->element, monster_list[j]->population);
                    // }
            }
    
        }        

    }

    // for (i = 0; i < nmonstersinRegion; i++) {
    //     total_population = 0;
    //     printf("monster: %s\n", monster_list[i]->name);
    //     total_population = total_population + monster_list[i]->population;
    // }

    //total_population = get_total_population(r);

    fill_region(r , name, nmonstersinRegion, total_population, monster_list);


}


void print_region(FILE *ofp, region *r) {
    // int i;

    // int limit = r->nmonsters;

    // for (i = 0; i = limit; i++) {
    //     fprintf(ofp, "id: %d, name: %s, element: %s, population: %d", r->monsters[i]->id, r->monsters[i]->name, r->monsters[i]->element, r->monsters[i]->population);
    // }
    

    fprintf(ofp, "name: %s #Monsters: %d  Total Population: %d \n",
            r->name, r->nmonsters, r->total_population);

}



int main (void) {
    atexit(report_mem_leak);

    FILE *ofp;
    FILE *ifp;

    int nmonsters;
    int i;
    int j;
    monster *monsters;

    int nregions;
    region *regions;

    ifp = fopen("cop3502-as1-input.txt", "r");
    ofp = fopen("cop3502-as1-out-LauKoo-Esteban", "w");

    nmonsters = get_number_of_monsters(ifp);

    monsters = new_monster_array(nmonsters);
   

    for (i = 0; i < nmonsters; i++) {
        read_monster(ifp, monsters + i, i + 1);
    }

    for(i = 0; i < nmonsters; i++) {
        print_monster(ofp, monsters + i);
    }


    // starts the region set up
    nregions = get_number_of_regions(ifp);

    regions = new_region_array(nregions);

    // for (i = 0; i < nregions; i++) {
    //     read_region(ifp, regions + i, nmonsters, monsters);
    // }

    // for (i = 0; i < nregions; i++) {
    //     print_region(ofp, regions + i);
    // }


    dispose_monster_array(monsters, nmonsters);
    dispose_region_array(regions, nregions);

    fclose(ifp);
    fclose(ofp);

    return 0;
}

