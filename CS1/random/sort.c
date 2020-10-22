// sort.c - demonstrate basic sorting algorithms

/* The idea of sorting is simple: take unordered objects, and arrange them in an
   order.  It has a lot of uses, so there's been a lot of work done with it.  Here,
   we're going to demonstrate a few of the simpler, more classic sorting techniques.
   */

#include <stdio.h>
#include <math.h>
#include <limits.h>

/* Output a list of integers. */

void output_integer_list(int *list, int n, char *title) {
  printf("List %s:\n", title);
  for(int i = 0; i < n; i++) {
    printf("  Value %3d: %10d\n", i, list[i]);
  }
  printf("\n");
}

/* Implement ascending bubble sort. */

void bubble_sort(int *list, int n) 
{
  int i;
  int j;
  int temp;
  int comparisons = 0;
  int swaps = 0;

  printf("Bubble sort %d integers...\n", n);

  for(i = n-1; i >= 0; i--)
  {
    for(j = 0; j < i; j++)
    {
      comparisons++;
      if(list[j] > list[j+1]) // Are our elements out of order?
      {
        swaps++;
        temp = list[j];
        list[j] = list[j+1];
        list[j+1] = temp;
      }
    }
  }
  printf("Sort complete with %d comparisons and %d swaps.\n", comparisons, swaps);
}

/* Highest-value finder for selection sort. */

int find_highest(int *list, int n, int *comparisons)
{
  int highest_val = INT_MIN;
  int highest_loc = -1;
  int i;
  
  for(i = 0; i <= n; i++)
  {
    (*comparisons)++;
    if(list[i] > highest_val)
    {
      highest_loc = i;
      highest_val = list[i];
    }
  }

  return highest_loc;
}

/* Implement ascending selection sort. */

void selection_sort(int *list, int n)
{
  int i;
  int highest;
  int temp;
  int comparisons = 0;
  int swaps = 0;

  printf("Selection sort %d integers...\n", n);
  for(i = n-1; i > 0; i--)
  {
    highest = find_highest(list, i, &comparisons);
    if(highest != i)
    {
      swaps++;
      temp = list[highest];
      list[highest] = list[i];
      list[i] = temp;
    }
  }
  printf("Sort complete with %d comparisons and %d swaps.\n", comparisons, swaps);
}

/* Main program. */

int main(void) {
  int our_list[] = {5, 8, 1, 598, 23,       // 5
                    248, 12, 8983, 23, 1,   // 10
                    78, -3, 6, 0, 41,       // 15
                    889, 92348, 42, 16, 71, // 20
                    7, 36, 15, 616, 390};   // 25
  int n = 25;

  output_integer_list(our_list, 25, "unsorted values");
  // bubble_sort(our_list, 25);
  selection_sort(our_list, 25);

  output_integer_list(our_list, 25, "sorted values");

  return 0;
}