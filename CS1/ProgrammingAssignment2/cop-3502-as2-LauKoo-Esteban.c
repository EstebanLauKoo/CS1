#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "leak_detector_c.h"
#include <math.h>



struct fish_struct {
    char *name;
    struct fish_struct *next;
    struct fish_struct *prev;
};

typedef struct fish_struct fish;

// build the pond struct read values from input.
struct pond_struct {
    char *name;

}


struct fish_list_struct {
    fish *head;
    fish *tail;
};

typedef struct fish_list_struct fish_list;

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

// gets the number of ponds from the ifp. and returns it
int get_number_of_ponds(FILE *ifp) {
    char s[128];
    int num;

    fgets(s, 127, ifp);
    sscanf(s, "%d", &num);

    return num;
}


fish *new_fish(char* name) {

    fish *f;

    f = malloc(sizeof(fish));

    f->name = strdup(name);
    f->next = NULL;
    f->prev = NULL;

    return f;
}

void dispose_fish(fish *f) {
    free(f->name);
    free(f);
}

void print_fish(fish *f) {

    printf("    Fish: %s\n", f->name);

    if(f->prev == NULL) {
        printf("    No link back\n");
    } else {
        printf("    Link back to: %s\n", f->prev->name);
    }
    if(f->next == NULL) {
        printf("    No link forward\n");
    } else {
        printf("    Link forward to: %s\n", f->next->name);
    }
}

fish_list *new_fish_list(void) {

    fish_list *fl;

    fl = malloc(sizeof(fish_list));
    fl->head = NULL;
    fl->tail = NULL;
}

void dispose_fish_list(fish_list *fl) {

    free(fl);
}

void dispose_fish_list_all(fish_list *fl) {

    fish *f = fl->head;
    fish *n;

    if (f == NULL) {
        dispose_fish_list(fl);
        return;
    }

    do {
        n = f->next;
        dispose_fish(f);
        f = n;
    } while(f != fl->head);

    dispose_fish_list(fl);
}

void print_fish_list(fish_list *fl) {

    fish *f = fl->head;

    if(f == NULL) {
        return;
    }

    do {
        print_fish(f);
        f = f->next;
    } while(f != fl->head);
}

void fish_list_add(fish_list *fl, fish *new_fish)
{
    if(fl->head == NULL)
    {
        /* If we're adding to an empty list, just set the head equal to the tail equal
           to the new monster. */

        fl->head = new_fish;
        fl->tail = new_fish;
        new_fish->prev = new_fish;
        new_fish->next = new_fish;
    } else {
        /* If the list isn't empty, there's a head, so... */

        new_fish->prev = fl->tail;
        new_fish->next = fl->head;

        fl->head->prev = new_fish;
        fl->tail->next = new_fish;

        fl->head = new_fish;
    }
}

void fish_list_add_tail(fish_list *fl, fish *new_fish) {

    if (fl->tail == NULL) {

        fl->head = new_fish;
        fl->tail = new_fish;
        new_fish->prev = new_fish;
        new_fish->next = new_fish;
    }

    else {
        new_fish->prev = fl->tail;
        new_fish->next = fl->head;

        fl->head->prev = new_fish;
        fl->tail->next = new_fish;

        fl->tail = new_fish;
    }
}

void clear_links_or_dispose(fish *f_to_delete, int dispose) {
    if (dispose != 0) {
        dispose_fish(f_to_delete);
    }

    else {
        f_to_delete->next = NULL;
        f_to_delete->prev = NULL;
    }

}

void fish_list_delete(fish_list *fl, fish *f_to_delete, int dispose)
{
    fish *f = fl->head;
    fish *n;

    /* First thing to check is if this will empty the list. */

    if(f_to_delete->next == f_to_delete) // We could also use if(ml->head == ml->tail)
    {
      clear_links_or_dispose(f_to_delete, dispose);
      fl->head = NULL;
      fl->tail = NULL;
      return;
    }

    /* We now know we're not deleting the only item in the list.  To make this less 
       messy, we're going to repair the head and/or tail pointers *before* the actual
       linkbreaking and deletion. */

    if(fl->head == f_to_delete)
    {
      fl->head = f_to_delete->next;
    }

    if(fl->tail == f_to_delete) 
    {
      fl->tail = f_to_delete->prev;
    }

    /* We now know we're deleting an item that is not the only item in the list, and
       that is neither the head nor the tail.  We don't have to worry about head or
       tail pointers, just about our next and prev pointers - which makes the link
       repair really easy. */

    f_to_delete->prev->next = f_to_delete->next;
    f_to_delete->next->prev = f_to_delete->prev;

    /* Nothing in the list points to us any more, so we can now safely delete. */

    clear_links_or_dispose(f_to_delete, dispose);
}

int main(void) {

    //atexit(report_mem_leak);

    FILE *ofp;
    FILE *ifp;

    int i;
    int nponds;
    pond *ponds;

    ifp = fopen("cop3502-as2-input-2.txt", "r");
    ofp = fopen("cop3502-as2-out-LauKoo-Esteban", "w");

    nponds = get_number_of_ponds(ifp);
    printf("# of ponds = %d\n", nponds);

    ponds = new_ponds_array(nponds);

    

    fish *f; 
    fish_list *fl = new_fish_list();

    f = new_fish("failfish1");
    fish_list_add(fl, f);
    f = new_fish("failfish2");
    fish_list_add(fl, f);
    f = new_fish("failfish3");
    fish_list_add(fl, f);

    print_fish_list(fl);

    dispose_fish_list_all(fl);


    fclose(ifp);
    fclose(ofp);

    return 0;
}
