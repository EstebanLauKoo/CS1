
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leak_detector_c.h"
#include <math.h>

struct stack_node_struct
{
   int payload;
   struct stack_node_struct *next;
};

typedef struct stack_node_struct stack_node;

typedef struct
{
   stack_node *head;
} stack;

stack_node *new_stack_node(int payload)
{

   stack_node *node = malloc(sizeof(node));

   node->payload = payload;
   node->next = NULL;
   return node;
}

void dispose_node(stack_node *node)
{
   free(node);
}

stack *new_stack(void)
{
   stack *st = malloc(sizeof(stack));

   st->head = NULL;

   return st;
}

void dispose_stack(stack *st)
{
   free(st);
}

void push(stack *st, stack_node *node)
{

   node->next = st->head;

   st->head = node;

   printf("Pushed node %d\n", node->payload);
}

stack_node *pop(stack *st)
{

   stack_node *stack_node = st->head;

   if (st->head != NULL)
   {
      st->head = st->head->next;
   }

   return stack_node;
}

int stack_peek(stack *st)
{
   if (st->head == NULL)
   {
      return 0;
   }
   else
   {
      return 1;
   }
}

int is_empty(stack *st)
{

   if (stack_peek(st) == 0)
   {

      return 1;
   }

   else
   {

      return 0;
   }
}

int main(void)
{

   atexit(report_mem_leak);

   stack *st;

   st = new_stack();

   push(st, new_stack_node(3));
   push(st, new_stack_node(4));
   push(st, new_stack_node(5));

   printf("---------\n");

   while (is_empty(st) == 0)
   {
      stack_node *node = pop(st);
      printf("  Item value: %d\n", node->payload);
      dispose_node(node);
   }

   dispose_stack(st);

   return 0;
}