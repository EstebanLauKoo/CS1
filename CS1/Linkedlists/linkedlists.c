/* linkedlists.c - this program demonstrates the basic principles of linked lists.

   Matthew Gerber, 2020, for COP3502. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* This is a monster structure for a singly linked list of monsters.  It contains basic 
   information about a monster, as well as a link to a next monster.  next is null if and only
   if one of the following things is true:

    * The monster has not been added to a list yet
    * The monster sits at the tail of the list, i.e. the other end of the list from the 
    * head, so there is no next monster from it */

struct monster_struct {
    char *name;
    int commonality;
    int weight;
    struct monster_struct *next;
};


// type def struct that makes monster an alias for monster_struct;
typedef struct monster_struct monster;



/* This is a structure for a singly linked list of monsters.  It contains only a head node.
   head is NULL if and only if the list is empty.  Otherwise, head points to the most recently
   added monster. */

struct monster_list_struct {
    monster *head;
};

typedef struct monster_list_struct monster_list;

/* ------ Functions for monsters. */

/* Allocate and return a new monster. */

monster *new_monster(char *name, int commonality, int weight)
{
    monster *m;

    m = malloc(sizeof(monster));
    m->name = strdup(name);
    m->commonality = commonality;
    m->weight = weight;
    m->next = NULL;

    return m;
}

/* Destructor for monster. */

void dispose_monster(monster *m)
{
    free(m->name);
    free(m->commonality);
    free(m->weight);
    free(m);
}

/* Print out basic info for a monster. */

void print_monster(monster *m)
{
    printf("  Monster %s of commonality %d with weight %d\n", m->name, m->commonality, m->weight);
    // if(m->next == NULL) {
    //     printf("    Monster has no link\n");
    // } else {
    //     printf("    Monster has link to: %s\n", m->next->name);
    // }
}

/* ------ Functions for monster_lists. */

/* Allocate a new, empty linked list of monsters. */

monster_list *new_monster_list(void)
{
    monster_list *ml;

    ml = malloc(sizeof(monster_list));
    ml->head = NULL;

    return ml;
}

/* Dispose of a list of monsters. */

void dispose_monster_list(monster_list *ml)
{
    free(ml);
}

/* Dispose of a list of monsters *and* all the monsters in it. */

void dispose_monster_list_all(monster_list *ml)
{
    monster *m = ml->head;
    monster *n;

    while(m != NULL)
    {
        n = m->next;
        dispose_monster(m);
        m = n;
    }

    dispose_monster_list(ml);
}

/* Print every monster in a list of monsters. */

void print_monster_list(monster_list *ml)
{
    monster *m = ml->head;

    while(m != NULL)
    {
        print_monster(m);
        m = m->next;
    }
}

/* Add monster m to list ml.  m must already be an allocated monster and must *not* be
   a member of ml or any other monster_list. */

void monster_list_add(monster_list *ml, monster *m)
{
    m->next = ml->head;
    ml->head = m;
}

/* Delete a monster from a list of monsters. */

void monster_list_delete(monster_list *ml, monster *m_to_delete)
{
    monster *m = ml->head;
    monster *n;

    /* Deleting the head is a special case. */

    if(ml->head == m_to_delete) {
        ml->head = ml->head->next;
        dispose_monster(m_to_delete);
        return;
    }

    /* Otherwise, linked list deletion always works the same way.  You need to:

       * Find the item in the list
       * Set the pointer(s) that reference the item to reference the next item
         instead
       * Dispose the item

       The trick is making sure you do it IN THAT ORDER. */

    while(m->next != NULL)
    {
        if(m->next == m_to_delete)
        {
            n = m->next->next;
            dispose_monster(m->next);
            m->next = n;
        }
    }
}

monster *second_most_common(monster_list *ml) {
    monster *m = ml->head;

    monster *mostComMonster;
    monster *secondMostComMonster;

    mostComMonster = NULL;
    secondMostComMonster = NULL;

    int firstComInt;
    int secondComInt;

    firstComInt = 0;
    secondComInt = 0;


    // goes through the loop till the linked list is NULL
    while (m != NULL)
    {
        // This has separate values for the commonalities and then also assigns the correct monster to each holder.
        if (m -> commonality > firstComInt)
        {
            secondComInt = firstComInt;
            firstComInt = m -> commonality;


            secondMostComMonster = mostComMonster;
            mostComMonster = m;


        }

        else if (m -> commonality > secondComInt) {
            secondComInt = m -> commonality;
            secondMostComMonster = m;
        }
        // moves to next on the list
        m = m -> next;

    }

    // returns the monster 
    return secondMostComMonster;
}

monster *third_lightest(monster_list *ml) {
    monster *m = ml->head;

    int weightInt1;
    int weightInt2;
    int weightInt3;

    monster *lightest;
    monster *secondLightest;
    monster *thirdLightest;

    lightest = NULL;
    secondLightest = NULL;
    thirdLightest = NULL;

    weightInt1 = 0;
    weightInt2 = 0;
    weightInt3 = 0;


    while (m != NULL)
    {
        // same as second most common except now we shift for three different int holders for weight and also adjust the monster holders;
        if (m -> weight > weightInt1)
        {
            
            weightInt3 = weightInt2;
            weightInt2 = weightInt1;
            weightInt1 = m->weight;

            thirdLightest = secondLightest;
            secondLightest = lightest;
            lightest = m;                

        }

        else if (m -> weight > weightInt2) {
            weightInt3 = weightInt2;
            weightInt2 = m -> weight;

            thirdLightest = secondLightest;
            secondLightest = m;

        }
        
        else if (m -> weight > weightInt3) {
            
            weightInt3 = m -> weight;
            thirdLightest = m;
            
        }

        m = m -> next;

    }

    return thirdLightest;
}

int main(void)
{
    monster *m;
    monster_list *ml = new_monster_list();

    m = new_monster("WholeWheat53", 5, 3);
    monster_list_add(ml, m);
    m = new_monster("Rye41", 4, 1);
    monster_list_add(ml, m);
    m = new_monster("SunDriedTomato25", 2, 5);
    monster_list_add(ml, m); 
    m = new_monster("Esteban12", 1, 2);
    monster_list_add(ml, m); 
    m = new_monster("John66", 6, 6);
    monster_list_add(ml, m); 
    m = new_monster("Mina34", 3, 4);
    monster_list_add(ml, m); 

    m = second_most_common(ml);

    print_monster(m);

    m = third_lightest(ml);

    print_monster(m);

    dispose_monster_list_all(ml);
    return 0;
}