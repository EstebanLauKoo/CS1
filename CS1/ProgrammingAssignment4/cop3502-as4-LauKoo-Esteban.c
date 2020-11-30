#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leak_detector_c.h"

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
    t--;       // Decrement t.
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

void print_tree_inorder_item_node(FILE *ofp, item_node *t)
{
  if (t->left)
  {

    print_tree_inorder_item_node(ofp, t->left);
  }

  fprintf(ofp, "%s ", t->name);

  if (t->right)
  {

    print_tree_inorder_item_node(ofp, t->right);
  }
}

void print_tree_inorder_second(FILE *ofp, tree_name_node *t)
{
  if (t->left)
  {

    print_tree_inorder_second(ofp, t->left);
  }

  fprintf(ofp, "===%s===\n", t->treeName);

  print_tree_inorder_item_node(ofp, t->theTree);
  fprintf(ofp, "\n");

  if (t->right)
  {

    print_tree_inorder_second(ofp, t->right);
  }
}

void print_tree_inorder_first(FILE *ofp, tree_name_node *t)
{
  if (t->left)
  {
    print_tree_inorder_first(ofp, t->left);
  }

  fprintf(ofp, "%s ", t->treeName);

  if (t->right)
  {
    print_tree_inorder_first(ofp, t->right);
  }
}

void freeItem(item_node *parent) {

  if (parent->left) {
    freeItem(parent->left);
  }

  free(parent);

  if (parent->right) {
    freeItem(parent->right);
  }

}

void freeStuff(tree_name_node *parent) {

  if (parent->left)
  {
    freeStuff(parent->left);
  }

  freeItem(parent->theTree);
  free(parent);

  if (parent->right)
  {
    freeStuff(parent->right);
  }



}

tree_name_node *new_tree_node(char *name)
{

  tree_name_node *t = malloc(sizeof(tree_name_node));
  strcpy(t->treeName, name);
  t->left = NULL;
  t->right = NULL;
  t->theTree = NULL;
  return t;
}

item_node *new_item_node(char *name, int count)
{

  item_node *it = malloc(sizeof(item_node));
  strcpy(it->name, name);
  it->count = count;
  it->left = NULL;
  it->right = NULL;

  return it;
}

// this stuff works for the first bst.
tree_name_node *search_for_name_node(tree_name_node *parent, char *value)
{
  if (parent == NULL)
  {
    return NULL;
  }
  else if (strcmp(value, parent->treeName) == 0)
  {
    return parent;
  }
  else if (strcmp(value, parent->treeName) == -1)
  {
    return search_for_name_node(parent->left, value);
  }
  else
  {
    return search_for_name_node(parent->right, value);
  }
}

item_node *search_in_name_node(item_node *parent, char *value)
{
  if (parent == NULL)
  {
    return NULL;
  }
  else if (strcmp(value, parent->name) == 0)
  {
    return parent;
  }
  else if (strcmp(value, parent->name) == -1)
  {
    return search_in_name_node(parent->left, value);
  }
  else
  {
    return search_in_name_node(parent->right, value);
  }
}

//Performs items_before function
int count_items_before(item_node *it, char *item, int count)
{

  if (it->left)
  {
    count = count_items_before(it->left, item, count);
  }
  if (strcmp(it->name, item) < 0)
  {
    count++;
  }
  if (it->right)
  {
    count = count_items_before(it->right, item, count);
  }

  return count;
}

void set_left_child(tree_name_node *parent, tree_name_node *child)
{
  parent->left = child;
}

void set_right_child(tree_name_node *parent, tree_name_node *child)
{
  parent->right = child;
}

tree_name_node *bst_insert_tree(tree_name_node *parent, tree_name_node *new_node)
{

  if (strcmp(new_node->treeName, parent->treeName) == -1)
  {
    if (parent->left != NULL)
    {
      return bst_insert_tree(parent->left, new_node);
    }
    else
    {
      set_left_child(parent, new_node);
      return new_node;
    }
  }
  else
  {
    if (parent->right != NULL)
    {
      return bst_insert_tree(parent->right, new_node);
    }
    else
    {
      set_right_child(parent, new_node);
      return new_node;
    }
  }
}

// this is for the 2nd bst

void set_left_child_bottom(item_node *parent, item_node *child)
{
  parent->left = child;
}

void set_right_child_bottom(item_node *parent, item_node *child)
{
  parent->right = child;
}

item_node *bst_insert_tree_bottom(item_node *parent, item_node *new_node)
{

  if (strcmp(new_node->name, parent->name) < 0)
  {
    if (parent->left != NULL)
    {
      return bst_insert_tree_bottom(parent->left, new_node);
    }
    else
    {
      set_left_child_bottom(parent, new_node);
      return new_node;
    }
  }
  else
  {
    if (parent->right != NULL)
    {
      return bst_insert_tree_bottom(parent->right, new_node);
    }
    else
    {
      set_right_child_bottom(parent, new_node);
      return new_node;
    }
  }
}

int findHeight(item_node *parent)
{
  if (parent == NULL)
  {
    return -1;
  }

  int lefth = findHeight(parent->left);
  int righth = findHeight(parent->right);

  if (lefth > righth)
  {
    return lefth + 1;
  }
  else
  {
    return righth + 1;
  }
}

int tree_count(item_node *parent, int totalCount)
{

  if (parent->left)
  {
    // totalCount += parent->left->count;
    totalCount = tree_count(parent->left, totalCount);
  }

  totalCount += parent->count;

  if (parent->right)
  {
    // totalCount += parent->right->count;
    totalCount = tree_count(parent->right, totalCount);
  }

  return totalCount;
}

item_node *find_minimum(item_node *parent)
{
  if (parent == NULL)
    return NULL;
  else if (parent->left != NULL)
    return find_minimum(parent->left);
  return parent;
}

item_node *delete (item_node *parent, char *value)
{
  if (parent == NULL)
    return NULL;
  if (strcmp(value, parent->name) > 0)
    parent->right = delete (parent->right, value);
  else if (strcmp(value, parent->name) < 0)
    parent->left = delete (parent->left, value);
  else
  {
    //No Children
    if (parent->left == NULL && parent->right == NULL)
    {
      free(parent);
      return NULL;
    }

    //One Child
    else if (parent->left == NULL || parent->right == NULL)
    {
      item_node *temp;
      if (parent->left == NULL)
        temp = parent->right;
      else
        temp = parent->left;
      free(parent);
      return temp;
    }

    //Two Children
    else
    {
      item_node *temp = find_minimum(parent->right);
      strcpy(parent->name, temp->name);
      parent->count = temp->count;

      parent->right = delete (parent->right, temp->name);
    }
  }
  return parent;
}

tree_name_node *find_minimum_tree(tree_name_node *parent)
{
  if (parent == NULL)
    return NULL;
  else if (parent->left != NULL)
    return find_minimum_tree(parent->left);
  return parent;
}

tree_name_node *delete_tree(tree_name_node *parent, char *value)
{
  if (parent == NULL)
    return NULL;
  if (strcmp(value, parent->treeName) > 0)
    parent->right = delete_tree(parent->right, value);
  else if (strcmp(value, parent->treeName) < 0)
    parent->left = delete_tree(parent->left, value);
  else
  {
    //No Children
    if (parent->left == NULL && parent->right == NULL)
    {
      free(parent);
      return NULL;
    }

    //One Child
    else if (parent->left == NULL || parent->right == NULL)
    {
      tree_name_node *temp;
      if (parent->left == NULL)
        temp = parent->right;
      else
        temp = parent->left;

      freeItem(parent->theTree);  
      free(parent);
      return temp;
    }

    //Two Children
    else
    {
      printf("two children");
      tree_name_node *temp = find_minimum_tree(parent->right);

      strcpy(parent->treeName, temp->treeName);
      parent->theTree = temp->theTree;

      parent->right = delete_tree(parent->right, temp->treeName);
    }
  }
  return parent;
}

void get_n_line(FILE *ifp, int *ntrees, int *nitems, int *ncommands)
{

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

void traverse_in_order(FILE *ofp, tree_name_node *parent)
{

  print_tree_inorder_first(ofp, parent);

  fprintf(ofp, "\n");

  print_tree_inorder_second(ofp, parent);
}
int main(void)
{
  atexit(report_mem_leak);

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

  // gets our n values for ntrees, nitems, and ncommands;
  get_n_line(ifp, &ntrees, &nitems, &ncommands);

  printf("ntrees: %d, nitems: %d, ncommands: %d\n", ntrees, nitems, ncommands);

  get_next_nonblank_line(ifp, s, 31);
  tree_name_node *t1 = new_tree_node(s);

  for (i = 0; i < ntrees - 1; i++)
  {

    get_next_nonblank_line(ifp, s, 63);

    tree_name_node *t2 = new_tree_node(s);

    bst_insert_tree(t1, t2);
  }

  // the add function has to add left and right from the item and connect to tree. so we have to pass tree by search.

  for (i = 0; i < nitems; i++)
  {

    fscanf(ifp, "%s %s %s", tree_string, item_string, count_string);

    count = atoi(count_string);

    item_node *it1 = new_item_node(item_string, count);

    // this will return the tree that we need to link to the first item. need to build logic for that.
    tree_name_node *mainTree = search_for_name_node(t1, tree_string);

    if (mainTree == NULL)
    {
      printf("no mainTree found \n");
    }
    // this checks if the main tree has no link for theTree; If it doesn't then sets the first one to that. problem if there is no tree that matches.
    else if (mainTree->theTree == NULL)
    {

      mainTree->theTree = it1;
    }

    else
    {

      bst_insert_tree_bottom(mainTree->theTree, it1);
    }
  }

  traverse_in_order(ofp, t1);

  fprintf(ofp, "===Processing Commands===\n");

  for (i = 0; i < ncommands; i++)
  {
    get_next_nonblank_line(ifp, s, 63);

    char *command = strtok(s, " ");
    char *tree_command_string = strtok(NULL, " ");
    char *item_command_string = strtok(NULL, " ");

    if (strcmp(command, "search") == 0)
    {

      // find fish animal whatever
      tree_name_node *mainTree = search_for_name_node(t1, tree_command_string);

      if (mainTree == NULL)
      {
        fprintf(ofp, "%s does not exist\n", tree_command_string);
      }
      else if (mainTree != NULL)
      {

        item_node *search_item = search_in_name_node(mainTree->theTree, item_command_string);

        if (search_item == NULL)
        {

          fprintf(ofp, "%s not found in %s\n", item_command_string, tree_command_string);
        }

        else
        {

          fprintf(ofp, "%d %s found in %s\n", search_item->count, search_item->name, tree_command_string);
        }
      }


    }
    else if (strcmp(command, "item_before") == 0)
    {

      tree_name_node *mainTree = search_for_name_node(t1, tree_command_string);

      int nitemBefore = count_items_before(mainTree->theTree, item_command_string, 0);

      fprintf(ofp, "item_before %s: %d\n", item_command_string, nitemBefore);
    }
    else if (strcmp(command, "height_balance") == 0)
    {

      int leftHeight;
      int rightHeight;
      int difference;

      tree_name_node *mainTree = search_for_name_node(t1, tree_command_string);

      leftHeight = findHeight(mainTree->theTree->left);

      rightHeight = findHeight(mainTree->theTree->right);

      difference = rightHeight - leftHeight;

      if (difference == 0)
      {

        fprintf(ofp, "%s: left height %d, right height %d, difference %d, balanced\n", tree_command_string, leftHeight, rightHeight, difference);
      }

      else
      {

        fprintf(ofp, "%s: left height %d, right height %d, difference %d, not balanced\n", tree_command_string, leftHeight, rightHeight, difference);
      }
    }
    else if (strcmp(command, "count") == 0)
    {

      // printf("count command\n");
      tree_name_node *mainTree = search_for_name_node(t1, tree_command_string);

      int totalCount = tree_count(mainTree->theTree, 0);

      fprintf(ofp, "%s count %d\n", tree_command_string, totalCount);
    }
    else if (strcmp(command, "delete") == 0)
    {

      // printf("delete command\n");
      tree_name_node *mainTree = search_for_name_node(t1, tree_command_string);
      item_node *search_item = search_in_name_node(mainTree->theTree, item_command_string);

      delete (mainTree->theTree, item_command_string);

      fprintf(ofp, "%s deleted from %s\n", item_command_string, tree_command_string);

      // print_tree_inorder_second(t1, 0);
    }
    else if (strcmp(command, "delete_tree") == 0)
    {

      tree_name_node *mainTree = search_for_name_node(t1, tree_command_string);

      delete_tree(t1, tree_command_string);
      fprintf(ofp, "%s deleted\n", tree_command_string);
    }
    else
    {
      printf("incorrect command\n");
    }
  }


  freeStuff(t1);

  fclose(ifp);
  fclose(ofp);
}