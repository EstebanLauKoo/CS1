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

void print_indent(int depth)
{
  for(int i = 0; i < depth; i++) {
    printf(" ");
  }
}

void print_tree_inorder_item_node(item_node *t) {
  if(t->left) {

    print_tree_inorder_item_node(t->left);
  }


  printf("%s ", t->name);

  if(t->right) {


    print_tree_inorder_item_node(t->right);
  }
}

void print_tree_inorder_second(tree_name_node *t, int depth) {
  if(t->left) {

    print_tree_inorder_second(t->left, depth + 1);
  }


  printf("===%s===\n", t->treeName);

    print_tree_inorder_item_node(t->theTree);
    printf("\n");

  if(t->right) {


    print_tree_inorder_second(t->right, depth + 1);
  }
}

void print_tree_inorder(item_node *t, int depth) {
  if(t->left) {
    print_indent(depth);
    printf("descending left...\n");
    print_tree_inorder(t->left, depth + 1);
  }

  print_indent(depth);
  printf("name:  %s\n", t->name);

  if(t->right) {
    print_indent(depth);
    printf("descending right...\n");
    print_tree_inorder(t->right, depth + 1);
  }
}


void print_tree_inorder_first(tree_name_node *t, int depth) {
  if(t->left) {
    print_tree_inorder_first(t->left, depth + 1);
  }

  printf("%s ", t->treeName);

  if(t->right) {
    print_tree_inorder_first(t->right, depth + 1);
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

item_node *new_item_node(char *name, int count) {

    item_node *it = malloc(sizeof(item_node));
    strcpy(it->name, name);
    it->count = count;
    it->left = NULL;
    it->right= NULL;

    return it;
}

// this stuff works for the first bst.
tree_name_node *search_tree_name(tree_name_node *parent, char *value) {
  if(parent == NULL) {
    return NULL;
  } else if(strcmp(value ,parent->treeName) == 0) {
    return parent;
  } else if(strcmp(value, parent->treeName) == -1) {
    return search_tree_name(parent->left, value);
  } else {
    return search_tree_name(parent->right, value);
  }
}

item_node *search_item_node(item_node *parent, char *value) {
  if(parent == NULL) {
    return NULL;
  } else if(strcmp(value ,parent->name) == 0) {
    return parent;
  } else if(strcmp(value, parent->name) == -1) {
    return search_item_node(parent->left, value);
  } else {
    return search_item_node(parent->right, value);
  }
}

int item_before(item_node *parent, char *value) {

  int nitemsBefore = 0;

  // if(parent == NULL) {
  //   return NULL;
  // } else if(strcmp(value ,parent->name) == 0) {
  //   printf("nitemsBefore:%d\n", nitemsBefore);
  //   return nitemsBefore;
  // } else if(strcmp(value, parent->name) == -1) {
  //   nitemsBefore++;
  //   return item_before(parent->left, value);
  // } else {
  //   nitemsBefore++;
  //   return item_before(parent->right, value);
  // }

  while (parent != NULL) {
    nitemsBefore++;
      printf("parent: %s value : %s\n", parent->name, value);

    int result = strcmp(parent->name, value);

   
    if (result == -1) {

      item_before(parent->left, value);

    }

    if (result == 1) {

      item_before(parent->right,value);
    }

    if (result == 0) {

          return item_before(parent->left , value) + item_before(parent->right, value);

    }



  }
  




    // if(parent->left) {
    // nitemsBefore++;
    // printf("descending left...\n");

    // item_before(parent->left, value);
    // }


    // if(parent->right) {
    // nitemsBefore++;
    // printf("descending right...\n");
    // item_before(parent->right, value);
    // }
  

  // if (strcmp(parent->name, value) == 0) {
  //   printf("its true:\n");
  //   return nitemsBefore;
  // }

  // if (strcmp(parent->name, value) != 0) {
    
  //   if(parent->left) {
  //   nitemsBefore++;
  //   printf("descending left...\n");

  //   item_before(parent->left, value);
  // }


  //   if(parent->right) {
  //   nitemsBefore++;
  //   printf("descending right...\n");
  //   item_before(parent->right, value);
  //   }
  
  // }






}




void set_left_child(tree_name_node *parent, tree_name_node *child) {
  parent->left = child;
}

void set_right_child(tree_name_node *parent, tree_name_node *child) {
  parent->right = child;
}


tree_name_node *bst_insert_tree(tree_name_node *parent, tree_name_node *new_node) {

    if (strcmp(new_node->treeName,parent->treeName) == -1) {
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


// this is for the 2nd bst

void set_left_child_bottom(item_node *parent, item_node *child) {
    parent->left= child;
}

void set_right_child_bottom(item_node *parent, item_node *child) {
    parent->right= child;
}

item_node *bst_insert_tree_bottom(item_node *parent, item_node *new_node) {

    if (strcmp(new_node->name,parent->name) == -1) {
        if (parent->left != NULL ) {
            return bst_insert_tree_bottom(parent->left, new_node);
        } else {
            set_left_child_bottom(parent, new_node);
            return new_node;
        }
    } else {
        if (parent->right != NULL) {
            return bst_insert_tree_bottom(parent->right, new_node);
        } else {
            set_right_child_bottom(parent, new_node);
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
    char s[64];

    // ifp and ofp files
    ifp = fopen("cop3502-as4-input.txt", "r");
    ofp = fopen("cop3502-as4-out-LauKoo-Esteban", "w");

    char tree_string[64];
    char item_string[32];
    char count_string[32];

    int count;

    char command_string[64];
    char tree_command_string[64];
    char item_command_string[32];


    // gets our n values for ntrees, nitems, and ncommands;
    get_n_line(ifp, &ntrees, &nitems, &ncommands);

    printf("ntrees: %d, nitems: %d, ncommands: %d\n", ntrees, nitems, ncommands);
        
    get_next_nonblank_line(ifp, s, 31);
    tree_name_node *t1 = new_tree_node(s);


    for (i = 0; i < ntrees - 1; i++) {
        
        get_next_nonblank_line(ifp, s, 63);

        tree_name_node *t2 = new_tree_node(s);

        bst_insert_tree(t1, t2);


    }

    

    // the add function has to add left and right from the item and connect to tree. so we have to pass tree by search.

    for (i = 0; i < nitems; i++) {


        fscanf(ifp, "%s %s %s", tree_string, item_string, count_string);

        count = atoi(count_string);

        item_node *it1 = new_item_node(item_string, count);
        
        // this will return the tree that we need to link to the first item. need to build logic for that.
        tree_name_node *mainTree = search_tree_name(t1, tree_string);

        if (mainTree == NULL) {
            printf("no mainTree found \n");
        }
        // this checks if the main tree has no link for theTree; If it doesn't then sets the first one to that. problem if there is no tree that matches.
        else if(mainTree->theTree == NULL) {

            mainTree->theTree = it1;

        }

        else {


            bst_insert_tree_bottom(mainTree->theTree, it1);

        }


    }


    print_tree_inorder_first(t1, 0);

    printf("\n");

    print_tree_inorder_second(t1, 0);

    printf("===Processing Commands===\n");

    for (i = 0; i < ncommands; i++) {
        get_next_nonblank_line(ifp, s, 62);

        char *command = strtok(s, " ");
        char *tree_command_string = strtok(NULL, " ");
        char *item_command_string  = strtok(NULL, " ");



        if (strcmp(command, "search") == 0) {


            tree_name_node *mainTree = search_tree_name(t1, tree_command_string);

            item_node *search_item = search_item_node(mainTree->theTree, item_command_string);

            if (search_item == NULL) {

                printf("%s not found in %s\n", item_command_string, tree_command_string);

            }

            else {
            printf("%d %s found in %s\n", search_item->count, search_item->name, tree_command_string);


            }

        }
        else if (strcmp(command, "item_before") == 0) {

            tree_name_node *mainTree = search_tree_name(t1, tree_command_string);

            int nitemBefore = item_before(mainTree->theTree, item_command_string);
            
            printf("item_before %s: %d\n", item_command_string, nitemBefore);
            // printf("item_before command\n");

            print_tree_inorder(mainTree->theTree, 0);

        }
        else if (strcmp(command, "height_balance") == 0) {

            // printf("height_balance command\n");



        }
        else if (strcmp(command, "count") == 0) {

            // printf("count command\n");

        }
        else if (strcmp(command, "delete") == 0) {

            // printf("delete command\n");

        }
        else if (strcmp(command, "delete_tree") == 0) {

            // printf("delete_tree command\n");

        }
        else {
            printf("incorrect command\n");
        }                

    }

    
    
    
    fclose(ifp);
    fclose(ofp);


}