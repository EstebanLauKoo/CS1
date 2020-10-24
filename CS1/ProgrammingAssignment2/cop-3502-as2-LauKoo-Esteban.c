#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leak_detector_c.h"
#include <math.h>



struct fish_struct {
    int id;
    struct fish_struct *next;
    struct fish_struct *prev;
};

typedef struct fish_struct fish;

struct fish_list_struct {
    int n;
    int e;
    int th;
    fish *head;
    fish *tail;
};

typedef struct fish_list_struct fish_list;


// build the pond struct read values from input.
struct pond_struct {
    int pond_number;
    char *name;
    fish_list *fl;
};

typedef struct pond_struct pond;




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


pond *new_pond_array(int nponds) {

    pond *p = calloc(nponds, sizeof(pond));

    return p;
}

void clear_pond(pond *p ) {

    p -> pond_number = 0;

    if (p->name != NULL) {
        free(p->name);
        p->name = NULL;
    } 
    
}

fish_list *new_fish_list(void) {

    fish_list *fl;

    fl = malloc(sizeof(fish_list));
    fl->e = 0;
    fl->n = 0;
    fl->th = 0;
    fl->head = NULL;
    fl->tail = NULL;
}

// grabs the information that is passed through and fills in the corresponding parts of the structure.
void fill_fish_list(fish_list *fl, int n, int e, int th) {

    fl -> n = n;
    fl -> e = e;
    fl -> th = th;

}

void dispose_pond_array(pond *p, int nponds) {
    
    // calls the clear monster function to remove the data within the structure
    for (int i = 0; i < nponds; i++) {
        clear_pond(p + i);
    }
    // frees the memory allocation.
    free(p);
}

void fill_pond(pond *p, int pond_number, char *name, fish_list *fl) {

    p -> name = strdup(name);
    p -> pond_number= pond_number;
    p -> fl = fl;   


}



/* Read a monster from our file. and directs to a fill function */
void read_pond(FILE *ifp, pond *p) {
    

    char name[128];

    char order_string[128];
    int order;

    char n_string[128];
    int n;

    char e_string[128];
    int e;

    char th_string[128];
    int th;

    fish_list *fl;
 
    // scans the the file for the corresponding values and names them accordingly
    fscanf(ifp, "%s %s %s %s %s", order_string, name, n_string, e_string, th_string);

    order = atoi(order_string);

    fl = new_fish_list();

    n = atoi(n_string);    
    e = atoi(e_string);
    th = atoi(th_string);    

    fill_fish_list(fl , n, e, th);

    // sends the information to the fill monster function in order to fill the corresponding data.
    fill_pond(p , order, name, fl);

}

void print_fish(fish *f) {

    printf("    Fish: %d\n", f->id);

    // if(f->prev == NULL) {
    //     printf("    No link back\n");
    // } else {
    //     printf("    Link back to: %d\n", f->prev->id);
    // }
    // if(f->next == NULL) {
    //     printf("    No link forward\n");
    // } else {
    //     printf("    Link forward to: %d\n", f->next->id);
    // }
}

// prints the monster based on the given monster structure pointer.
void print_pond(FILE *ofp, pond *p) {

    int i;

    fprintf(ofp, "%d %s n: %d e: %d th %d Fish: ",
            p->pond_number, p->name, p->fl->n, p->fl->e, p->fl->th);


            
        fish *f = p->fl->head;

        do {
            fprintf(ofp, " %d", f->id);
            f = f->next;
        } while(f != p->fl->head);    




    fprintf(ofp, "\n");

}

fish *new_fish(int id) {

    fish *f;

    f = malloc(sizeof(fish));

    f->id = id;
    f->next = NULL;
    f->prev = NULL;

    return f;
}

void  dispose_fish(fish *f) {

    free(f);
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

void print_fish_tail(fish_list *fl) {
    fish *f = fl->tail;

    if(f == NULL) {
        return;
    }

    do {
        print_fish(f);
        f = f->prev;
    } while(f != fl->tail);

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

    // printf("fish: %d deleted\n" , f_to_delete->id);
}

void output_integer_list(pond *p, int n) {

  for(int i = 0; i < n; i++) {
    printf("  pond %d\n", p[i].pond_number);
  }
  printf("\n");
}

int find_highest(pond *p, int n, int *comparisons)
{
  int highest_val = INT_MIN;
  int highest_loc = -1;
  int i;
  
  for(i = 0; i <= n; i++)
  {
    (*comparisons)++;
    if((p + i)->pond_number > highest_val)
    {
      highest_loc = i;
      highest_val = p[i].pond_number;
    }
  }

  return highest_loc;
}

int find_highest_fl(pond *p, int n )
{
  int highest_val = INT_MIN;
  fish *highest_position;
  int i;
  
  for(i = 0; i <= n; i++)
  {

    if(p->fl->head->id > highest_val)
    {
      highest_position = p->fl->tail;
      highest_val =  p->fl->tail->id;
    }
  }

  printf("tail: %d\n", p->fl->tail->id);

  return highest_val;
}

int find_lowest_fl(pond *p, int n)
{

  fish *lowest_position; 
  int lowest_val = INT_MAX;
  int i;
  
  printf("n %d\n", n);

  for(i = 0; i <= n; i++)
  {

    if(p->fl->head->id < lowest_val)
    {

      lowest_position = p->fl->head;  
      lowest_val = p->fl->head->id;      

    }

    p->fl->head = p->fl->head->next;

        printf("head value %d\n", p->fl->head->id);
        printf("lowest val %d\n", lowest_val);
    
  }


    p->fl->head = lowest_position;


    printf("head: %d\n", p->fl->head->id);


  return lowest_val;
}

void selection_sort(pond *p, int n)
{
  int i;
  int highest;
  pond temp;
  int comparisons = 0;
  int swaps = 0;


  for(i = n-1; i > 0; i--)
  {
    highest = find_highest(p, i, &comparisons);
    if(highest != i)
    {
      swaps++;
      temp = p[highest];
      p[highest] = p[i];
      p[i] = temp;
    }
  }

}

// void size_of_linked_list(pond *p) {

//     fish *f;

//     int size = 0;
//     if (f == NULL) {
//         printf("HEAD IS NULL");
//         return;
//     }

//     f = p->fl->head;

//     while (f != NULL) {
//         ++size;
//         f = p->fl->head->next;
//     }

//     printf("size of list is %d\n", size);
// }

void eat_fish(pond *p) {
    
    int i;

    fish_list *fl = p->fl;

    int n = fl->n;
    int th = fl->th;
    
    // printf("fish e: %d, n: %d, th: %d\n", fl->e, fl->n, fl->th);

    while (n != th) {
    for (i = 0; i < (fl->e)-1; i++) {

        fl->head = fl->head->next;


    }
        fish *f = fl->head;
                fish_list_delete(fl, f, 0);

                        --n;

                // printf("n: %d\n", n);


    };


}

void enqueue(fish_list *fl, fish *f) {

    f->next = NULL;


    if(fl->head == NULL) {

    fl->head = f;
    fl->tail = f;

    } else{

    fl->tail->next = f;
    fl->tail = f;

    }
}

    // Add f to the tail of q.

fish *dequeue(fish_list *fl) {

    fish *fish_to_delete = fl->head;

    if ( fl->head != NULL) {
        fl->head = fl->head->next;
    }

    if ( fl->head == NULL) {
        fl->tail= NULL;
    }

    return fish_to_delete;

}

    // Pull an item off the head of q - don't delete it - and return it.

fish *queue_peek(fish_list *fl) {

    return fl->head;

}

    // Look at the item on the head of q - don't delete it or remove it - and return it.

int is_empty(fish_list *fl) {

    if(queue_peek(fl) == NULL) {
        return 1;
    }

    else {
        return 0;
    }
    

}

    // Look to see if q->head == NULL.


int main(void) {

    atexit(report_mem_leak);

    FILE *ofp;
    FILE *ifp;

    int i, j, k;
    int nponds;
    pond *ponds;

    fish *f;
    fish_list *fl;



    ifp = fopen("cop3502-as2-input-2.txt", "r");
    ofp = fopen("cop3502-as2-out-LauKoo-Esteban", "w");

    nponds = get_number_of_ponds(ifp);


    ponds = new_pond_array(nponds);

    for (i = 0; i < nponds; i++) {
        read_pond(ifp, ponds + i );
    }

    selection_sort(ponds, nponds);
    // printf("Sorted array: \n"); 
    // output_integer_list(ponds, nponds);


    for (i = 0; i < nponds; i++) {

        for ( j = 0; j < ponds[i].fl->n; j++) {
            f = new_fish((j+1));
            fish_list_add_tail(ponds[i].fl, f);
        }
    }

    for (i = 0; i < nponds; i++) {
        print_pond(ofp, ponds + i);
    }

    for (i = 0; i < nponds; i++) {

  
        eat_fish((ponds+i));

    }



    fprintf(ofp,"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");




    for (i = 0; i < nponds; i++) {

        int lowest;

        fish *headFL;

        find_lowest_fl(ponds + i, (ponds + i)->fl->th);

        find_highest_fl(ponds + i, (ponds + i)->fl->th);

        printf("---------------------\n");

    }

    //probably need another sort here for the values.

    for (i = 0; i < nponds; i++) {
        print_pond(ofp, ponds + i);
    }

    // create formula to place head in the lowest number in each fl
    // 


    // eat_fish((ponds+0));
    // f = new_fish("failfish1");
    // fish_list_add(fl, f);
    // f = new_fish("failfish2");
    // fish_list_add(fl, f);
    // f = new_fish("failfish3");
    // fish_list_add(fl, f);

    // print_fish_list(fl);


    
    // dispose_fish_list_all(fl);

    // dispose_pond_array(ponds, nponds);


    fclose(ifp);
    fclose(ofp);

    return 0;
}
