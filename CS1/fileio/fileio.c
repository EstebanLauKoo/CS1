#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *type;
    char *region;
    int commonality;

} monster;

monster *new_monster_array(int i) {
    monster *m = malloc(sizeof(monster) * i);
    return m;
}

void dispose_monster_array(monster *m) {
    free(m);
}

void fill_monster(monster *m, char *name, char *type, char *region, int commonality) {
    
    m -> name = malloc(strlen(name) + 1); 
    strcpy(m -> name, name);

    m -> name = strdup(name);
    m -> type = strdup(type);
    m -> region = strdup(region);
    m -> commonality = commonality;
}

int get_number_of_monsters(FILE *ifp) {
    char s[128];
    int num;

    fgets(s, 127, ifp);
    sscanf(s, "%d", &num);

    return num;

}

int main (void) {
    FILE *ofp;
    FILE *ifp;

    int num_monsters;

    ifp = fopen("input.txt", "r");
    ofp = fopen("output.txt", "w");

    num_monsters = get_number_of_monsters(ifp);

    fprintf(ofp, "Hello World!, I should have %d monsters.\n", num_monsters);

    fclose(ifp);
    fclose(ofp);

    return 0;

}