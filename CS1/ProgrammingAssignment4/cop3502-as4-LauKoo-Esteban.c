#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* binary-trees.c - basics of binary trees. */

struct item_node_struct
{
    char name[32];
    int count;
    struct item_node_struct *left, *right;
};

typedef struct item_node_struct item_node;

struct tree_name_node_struct
{
    char treeName[32];
    struct tree_name_node_struct *left, *right;
    item_node *theTree;
};

typedef struct tree_name_node_struct tree_name_node;

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

void get_next_nonblank_line(FILE *ifp, char *s, int max_length)
{
    s[0] = '\0';

    while (s[0] == '\0')
    {
        fgets(s, max_length, ifp);
        remove_crlf(s);
    }
}

void print_tree_inorder(tree_name_node *t, int depth) {
  if(t->left) {
    print_indent(depth);
    printf("descending left...\n");
    print_tree_inorder(t->left, depth + 1);
  }

  print_indent(depth);
  printf("payload: %d\n", t->payload);

  if(t->right) {
    print_indent(depth);
    printf("descending right...\n");
    print_tree_inorder(t->right, depth + 1);
  }
}

tree_name_node *new_tree_node(char *name) {

    tree_name_node *t = malloc(sizeof(tree_name_node));
    strcpy(t->treeName, name);
    t->left = NULL;
    t->right = NULL;
    t->theTree = NULL;
    return t;

}

void set_left_child(tree_name_node *parent, tree_name_node *child) {
  parent->left = child;
}

void set_right_child(tree_name_node *parent, tree_name_node *child) {
  parent->right = child;
}


tree_name_node *bst_insert_tree(tree_name_node *parent, tree_name_node *new_node) {

    if (new_node->treeName < parent->treeName) {
        if (parent->left != NULL ) {
            return bst_insert_tree(parent->left, new_node);
        } else {
            set_left_child(parent, new_node);
            return new_node;
        }
    } else {
        if (parent->right != NULL) {
            return bst_insert_tree(parent->right, new_node);
        } else {
            set_right_child(parent, new_node);
            return new_node;
        }
    }  

} 

// item_node *new_item_node(char *name, int count) {

//     item_node *t = malloc(sizeof(item_node));
//     strcpy(t->name, name);
//     t->count = count;

// }


void get_n_line(FILE *ifp, int* ntrees, int* nitems, int* ncommands) {

    char ntrees_string[128];
    char nitems_string[128];
    char ncommands_string[128];

    int integerNTrees, integerNItems, integerNCommands;

    fscanf(ifp, "%s %s %s", ntrees_string, nitems_string, ncommands_string);

    integerNTrees = atoi(ntrees_string);
    integerNItems = atoi(nitems_string);
    integerNCommands = atoi(ncommands_string);

    *ntrees = integerNTrees;
    *nitems = integerNItems;
    *ncommands = integerNCommands;

}

int main(void)
{
    FILE *ofp;
    FILE *ifp;

    int ntrees, nitems, ncommands;
    int i, j, k;
    char s[32];

    // ifp and ofp files
    ifp = fopen("cop3502-as4-input.txt", "r");
    ofp = fopen("cop3502-as4-out-LauKoo-Esteban", "w");


    // gets our n values for ntrees, nitems, and ncommands;
    get_n_line(ifp, &ntrees, &nitems, &ncommands);

    printf("ntrees: %d, nitems: %d, ncommands: %d\n", ntrees, nitems, ncommands);
        
    get_next_nonblank_line(ifp, s, 31);
    tree_name_node *t1 = new_tree_node(s);


    for (i = 0; i < ntrees; i++) {
        
        get_next_nonblank_line(ifp, s, 31);

        tree_name_node *t2 = new_tree_node(s);

        bst_insert_tree(t1, t2);

        printf("treeName %s\n", t2->treeName);

    }

    print_tree_inorder(t1, 0);
    
    fclose(ifp);
    fclose(ofp);


}