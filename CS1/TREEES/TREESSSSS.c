#include <stdio.h>
#include <stdlib.h>

struct tree_node_struct
{
  int payload;
  struct tree_node_struct *child;
  struct tree_node_struct *sibling;
  unsigned int nchildren;
};

typedef struct tree_node_struct tree_node;

tree_node *new_tree_node(int p)
{
  tree_node *t = malloc(sizeof(tree_node));
  t->payload = p;
  t->child = NULL;
  t->sibling = NULL;
  t->nchildren = 0;
  return t;
}

void add_child(tree_node *parent, tree_node *child)
{
  parent->nchildren++;
  child->sibling = parent->child;
  parent->child = child;
}

void insert_child(tree_node *head, tree_node *child)
{
  // if just one child then add next to it

  if (head->sibling == NULL)
  {
    head->sibling = child;
  }

  // setting a temp node equal to the head which is parent->child;
  tree_node *temp = head;

  int holder;

  // traverse the siblings and add to right position
  // checks
  while ((temp->sibling) && (temp->payload > child->payload))
  {

    holder = temp->sibling->payload;
    temp->sibling->payload = temp->payload;
    temp->payload = holder;
  }
}

void add_sorted_child(tree_node *parent, tree_node *child)
{

  // if no child then just add it to child
  if (parent->child == NULL)
  {
    printf("added parent %d first child %d\n", parent->payload, child->payload);
    ;
    parent->nchildren++;
    parent->child = child;
  }

  else
  {
    printf("sorting children parent->child %d, child %d\n", parent->child->payload, child->payload);
    parent->nchildren++;
    insert_child(parent->child, child);
  }
}

/* This will dispose of a node *and* all its children.  Don't use this
   on a node you stlil have on your tree or bad things will happen.  you
   *can* use this to get rid of a whole tree. */

void dispose_node(tree_node *n)
{
  tree_node *child = n->child;

  while (child)
  {
    tree_node *next = child->sibling;
    dispose_node(child);
    child = next;
  }

  free(n);
}

tree_node *remove_child(tree_node *parent, tree_node *child)
{
  int removed = 0;

  // This is just a linked list removal function with parent->child
  // acting as the head.

  if (child == parent->child)
  {
    parent->child = child->sibling;
    removed = 1;
  }
  else
  {
    tree_node *find = parent->child;

    while (find->sibling != NULL)
    {
      if (find->sibling == child)
      {
        find->sibling = find->sibling->sibling;
        removed = 1;
      }
      find = find->sibling;
    }
  }

  if (removed)
  {
    parent->nchildren--;
    return child;
  }
  else
  {
    return NULL;
  }
}

void remove_and_dispose(tree_node *parent, tree_node *child)
{
  tree_node *ret = remove_child(parent, child);
  if (ret)
  {
    dispose_node(ret);
  }
}

void print_tree(tree_node *t, int depth)
{
  for (int i = 0; i < depth; i++)
  {
    printf(" ");
  }
  printf("payload: %d\n", t->payload);
  if (t->nchildren)
  {
    printf("descending...\n");
    tree_node *n = t->child;
    while (n)
    { // Same as while(n != NULL)
      print_tree(n, depth + 1);
      n = n->sibling;
    }
  }
}

int main(void)
{

  tree_node *t = new_tree_node(1);
  tree_node *n;
  tree_node *to_delete;

  n = new_tree_node(2);
  add_sorted_child(t, n);

  n = new_tree_node(3);

  add_sorted_child(t, n);

  add_sorted_child(n, new_tree_node(7));
  add_sorted_child(n, new_tree_node(15));

  remove_and_dispose(t, to_delete);
  print_tree(t, 0);

  dispose_node(t);

  return 0;
}
