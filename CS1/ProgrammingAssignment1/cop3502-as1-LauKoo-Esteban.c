#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct monster {
    int id;
    char *name;
    char *element;
    int population;
} monster;

typedef struct region {
    char *name;
    int numMonsters;
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

monster *new_monster_array(int i) {
    monster *m = malloc(sizeof(monster) * i);
    return m;
}

void dispose_monster_array(monster *m) {
    free(m);
}

void fill_monster(monster *m, int id, char *name, char *element, int population) {
    
    m -> name = malloc(strlen(name) + 1);
    strcpy(m -> name, name);

    m -> id = id;
    m -> name = strdup(name);
    m -> element = strdup(element);
    m -> population = population;
}

int get_number_of_monsters(FILE *ifp) {
    char s[128];
    int num;

    fgets(s, 127, ifp);
    sscanf(s, "%d", &num);

    return num;
}

void remove_crlf(char *s) {
    
    char *t = s + strlen(s);

    t--;

    while((t < s) && (*t == '\n' || *t == '\r')) {
        *t = '\0';
        *t--;
    }

}

void read_monster(FILE *ifp, monster *m) {
    char s[128] = "\0";

    while(strlen(s)) {
        fgets(s, 127, ifp);
    }
}


int main (void) {

    FILE *ofp;
    FILE *ifp;

    int num_monsters;

    ifp = fopen("cop3502-as1-input.txt", "r");
    ofp = fopen("cop3502-as1-out-LauKoo-Esteban", "w");

    num_monsters = get_number_of_monsters(ifp);

    fprintf(ofp, "Hello World!, I should have %d monsters.\n", num_monsters);

    fclose(ifp);
    fclose(ofp);

    return 0;
}

