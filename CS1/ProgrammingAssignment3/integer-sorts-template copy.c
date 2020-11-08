// integer-sorts.c - demonstrate basic sorting algorithms

/* The idea of sorting is simple: take unordered objects, and arrange them in an
   order.  It has a lot of uses, so there's been a lot of work done with it.  Here,
   we're going to demonstrate a few of the simpler, more classic sorting techniques.
   */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include <time.h>

/* Output a list of integers. */

void output_integer_list(int *list, int n, char *title) {
  printf("List %s:\n", title);
  for(int i = 0; i < n; i++) {
    printf("  Value %3d: %10d\n", i, list[i]);
  }
  printf("\n");
}

void print_clocks(clock_t clocks) {
  printf("  %lfs CPU time used\n", ((double) clocks) / CLOCKS_PER_SEC);
}

/* Swap two integers in an array. */

void swap_integers(int *list, int i, int j)
{
  int temp;

  temp = list[i];
  list[i] = list[j];
  list[j] = temp;
}

/* Implement ascending quick sort. */

int repartition(int *list, int low_index, int high_index, int *comparisons, int *swaps)
{
  /* If the array is random, it doesn't actually matter what we pick for the pivot_index.
     However, there's one quirk: if we pick the lowest number, Quick Sort has the
     worst possible performance.  Since we often get already-sorted lists, we want to
     *NOT* pick the first item.  There are arguments for picking the median and for
     picking other more complicated things, but for our purposes, it usually works to
     just pick the last item - and it's simple to code. */

  int pivot_value = list[high_index];

  /* We already know our pivot_value.  What we're going to do is fill the lower
     elements of the array with the values below pivot_value, and let the number of them
     we encounter determine our eventual pivot index. */

  int i = low_index;
  for(int j = low_index; j < high_index; j++)
  {
    (*comparisons)++;
    if(list[j] < pivot_value) {
      (*swaps)++;
      swap_integers(list, i, j);
      i++;
    }
  }

  /* We've now placed everything below pivot_value in list[low_index..i-1] - and that
     means we can just put our pivot value in list[i]! */

  swaps++;
  swap_integers(list, i, high_index);
  return i;
}

/* Recursive function for quick sort. */

void quick_sort_recursive(int *list, int low_index, int high_index, int *comparisons, int *swaps)
{
  int pivot_index = repartition(list, low_index, high_index, comparisons, swaps);
  // Coming out of repartition, our pivot_index must already be in the right position.
  if(pivot_index-1 > low_index) quick_sort_recursive(list, low_index, pivot_index-1, comparisons, swaps);
  if(high_index > pivot_index+1) quick_sort_recursive(list, pivot_index+1, high_index, comparisons, swaps);
}

/* Shell function for quick sort. */

void quick_sort(int *list, int n)
{
  int comparisons = 0;
  int swaps = 0;
  clock_t start_cpu, end_cpu;

  printf("Quick sort %d integers...\n", n);

  start_cpu = clock();
  quick_sort_recursive(list, 0, n-1, &comparisons, &swaps);
  end_cpu = clock();

  printf("Sort complete with %d comparisons and %d swaps.\n", comparisons, swaps);
  print_clocks(end_cpu - start_cpu);
}

/* Implement ascending bubble sort. */

void bubble_sort(int *list, int n)
{
  int i;
  int j;
  int temp;
  int comparisons = 0;
  int swaps = 0;
  clock_t start_cpu, end_cpu;

  printf("Bubble sort %d integers...\n", n);

  start_cpu = clock();
  for(i = n-1; i >= 0; i--)
  {
    for(j = 0; j < i; j++)
    {
      comparisons++;
      if(list[j] > list[j+1]) // Are our elements out of order?
      {
        swaps++;
        swap_integers(list, j, j+1);
      }
    }
  }
  end_cpu = clock();
  printf("Sort complete with %d comparisons and %d swaps.\n", comparisons, swaps);
  print_clocks(end_cpu - start_cpu);
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
  int comparisons = 0;
  int swaps = 0;
  clock_t start_cpu, end_cpu;

  printf("Selection sort %d integers...\n", n);
  start_cpu = clock();
  for(i = n-1; i > 0; i--)
  {
    highest = find_highest(list, i, &comparisons);
    if(highest != i)
    {
      swaps++;
      swap_integers(list, highest, i);
    }
  }
  end_cpu = clock();
  printf("Sort complete with %d comparisons and %d swaps.\n", comparisons, swaps);
  print_clocks(end_cpu - start_cpu);
}

/* ----- BEGINNING OF THE FUNCTIONS YOU MUST IMPLEMENT ----- */

int insertion_sort_find_position(int *list, int low_index, int high_index, int k, int *comparisons)
{
    k = list[high_index];

    low_index = high_index - 1;

    while (low_index >= 0 && list[low_index] > k) {

        (*comparisons)++;
        list[low_index + 1] = list[low_index];
        low_index = low_index - 1;

    }

        list[low_index + 1] = k;


}

void insertion_sort_internal(int *list, int n, int *comparisons, int *copies, int *block_copies)
{

  int i, j;
  int key;

  for (i = 1; i < n; i++) {

    // key = list[i];

    // j = i - 1;

    insertion_sort_find_position(list, j, i, key, comparisons);

    // while (j >= 0 && list[j] > key) {

    //     list[j + 1] = list[j];
    //     j = j - 1;

    // }

    // list[j + 1] = key;

  }

}

void merge_sort_merge(int *list, int l1, int h1, int l2, int h2,
                      int *comparisons, int *copies, int *block_copies, int *mallocs)
{

  // int pointer_left =  l1;
  // int half = (l1 + h1) / 2;
  // int pointer_right = half + 1;
  // int k;
  // int *auxArray = malloc(sizeof(int) * (h1 + 1));


  // for ( k = l1; k <= h1; k++) {

  //   if (pointer_left == half + 1) {
  //     auxArray[k] = list[pointer_right];
  //     pointer_right++;
  //   } else if ( pointer_right == h1 + 1 ) {
  //     auxArray[k] = list[pointer_left];
  //     pointer_left++;
  //   } else if ( list[pointer_left] < list[pointer_right]) {
  //     auxArray[k] = list[pointer_left];
  //     pointer_left++;
  //   } else {B
  //     auxArray[k] = list[pointer_right];
  //     pointer_right++;
  //   }

  // }

  // for (k = l1; k <= h1; k++) {
  //   list[k] = auxArray[k];
  // }

  int i, j , k;
  int leftArraySize = h1 - l1 + 1;
  int rightArraySize = h2 - h1;
  int fullArraySize = rightArraySize + leftArraySize;

  // printf("l1: %d, h1 %d, l2 %d, h2 %d\n", l1, h1, l2, h2);
  // printf("size of arrays: n1: %d, n2 %d\n", n1, n2);

  int *auxArrayL = malloc(sizeof(int) * leftArraySize);
  int *auxArrayR = malloc(sizeof(int) * rightArraySize);
  int *auxFullArray = malloc(sizeof(int) * 300);


  for (i = 0; i < leftArraySize; i++) {

    auxArrayL[i] = list[l1 + i]; 
    // printf("leftArray: index: %d number: %d\n", i, auxArrayL[i]);

  }

  for (j = 0; j < rightArraySize; j++) {

    auxArrayR[j] = list[h1 + 1 + j];
    // printf("rightArray: index: %d number: %d\n", j, auxArrayR[j]);

  }

  // printf("\n");
  // printf("end of fork\n");

  i = 0;
  j = 0;
  k = l1;

  while ( i < leftArraySize && j < rightArraySize) {

    if (auxArrayL[i] <= auxArrayR[j]) {
      (*comparisons)++;

      auxFullArray[k] = auxArrayL[i];
      i++;
      // printf("left Aux array replace\n");

    }

    else {
      (*comparisons)++;
      auxFullArray[k] = auxArrayR[j];
      j++;
      // printf("right Aux array replace\n");
    }
    k++;

  } 

  while (i < leftArraySize) {
    
    auxFullArray[k] = auxArrayL[i];
    i++;
    k++;

    // printf("used all of left\n");

  } 

  while (j < rightArraySize) {

    auxFullArray[k] = auxArrayR[j];
    j++;
    k++;

    // printf("used all of right\n");
    
  }   
  // printf("+++++++++++++++++++++++++++++++++++++++++++\n");
  // printf("list\n");

  // for (i = 0; i < fullArraySize; i++) {

    
  //   printf("fake array list: index: %d number: %d\n", i, auxFullArray[i]);

  // }

  for (i = l1; i <= h2; i++) {
     list[i] = auxFullArray[i];
  }

  // printf("l1: %d, h1 %d, l2 %d, h2 %d\n", l1, h1, l2, h2);

  // printf("actualist\n");
  // for (i = 0; i < 5; i++) {

    
  //   printf("list: index: %d number: %d\n", i, list[i]);

  // }





}

void merge_sort_recursive(int *list, int low_index, int high_index,
                          int *comparisons, int *copies, int *block_copies, int *mallocs)
{



  if (high_index <= low_index) {


    return;

  }
  
  else {
  // int half = (low_index + high_index) / 2;
  int half = low_index + ( high_index - low_index) / 2;

  merge_sort_recursive(list, low_index, half, comparisons, copies, block_copies, mallocs);
  merge_sort_recursive(list, half + 1, high_index, comparisons, copies, block_copies, mallocs);

  merge_sort_merge(list, low_index, half, half + 1, high_index, comparisons, copies, block_copies, mallocs);

  }

  // int pointer_left =  low_index;
  // int pointer_right = half + 1;
  // int k;
  // int *auxArray = malloc(sizeof(int) * (high_index + 1));



  // for ( k = low_index; k <= high_index; k++) {

  //   if (pointer_left == half + 1) {

  //     auxArray[k] = list[pointer_right];
  //     pointer_right++;
  //   } else if ( pointer_right == high_index + 1 ) {
  //     auxArray[k] = list[pointer_left];
  //     pointer_left++;
  //   } else if ( list[pointer_left] < list[pointer_right]) {
  //     auxArray[k] = list[pointer_left];
  //     pointer_left++;list[low_index].name
  //   } else {
  //     auxArray[k] = list[pointer_right];
  //     pointer_right++;
  //   }

  // }

  // for (k = low_index; k <= high_index; k++) {
  //   list[k] = auxArray[k];
  // }

}

void merge_insertion_sort_recursive(int *list, int low_index, int high_index,
                                    int *comparisons, int *copies, int *block_copies, int *mallocs)
{
  // i want high index + 1 so that i can get back to in and check condition with n.

  int n = high_index + 1;

  // maybe delete this



 if ( high_index - low_index <= 25 ) {

   insertion_sort_internal(list, n, comparisons, copies, block_copies);

 } 

else {    
  int half = (low_index + high_index) / 2;

  // merge_sort_recursive(list, low_index, half, comparisons, copies, block_copies, mallocs);
  // merge_sort_recursive(list, half + 1, high_index, comparisons, copies, block_copies, mallocs);

  merge_insertion_sort_recursive(list, low_index, half, comparisons, copies, block_copies, mallocs);
  merge_insertion_sort_recursive(list, half + 1, high_index, comparisons, copies, block_copies, mallocs);
  


  merge_sort_merge(list, low_index, half, half + 1, high_index, comparisons, copies, block_copies, mallocs);
  
}



  

}

/* Shell function for merge sort. */

void merge_sort(int *list, int n)
{
  int comparisons = 0;
  int copies = 0;
  int block_copies = 0;
  int mallocs = 0;
  clock_t start_cpu, end_cpu;

  printf("Merge sort %d integers...\n", n);

  start_cpu = clock();
  merge_sort_recursive(list, 0, n-1, &comparisons, &copies, &block_copies, &mallocs);
  end_cpu = clock();

  printf("Sort complete with %d comparisons, %d block copies, %d total copies, %d mallocs.\n", comparisons, block_copies, copies, mallocs);
  print_clocks(end_cpu - start_cpu);
}

/* Shell function for merge-insertion sort. */

void merge_insertion_sort(int *list, int n)
{
  int comparisons = 0;
  int copies = 0;
  int block_copies = 0;
  int mallocs = 0;
  clock_t start_cpu, end_cpu;

  printf("Merge-insertion sort %d integers...\n", n);

  start_cpu = clock();
  merge_insertion_sort_recursive(list, 0, n-1, &comparisons, &copies, &block_copies, &mallocs);
  end_cpu = clock();

  printf("Sort complete with %d comparisons, %d block copies, %d total copies, %d mallocs.\n", comparisons, block_copies, copies, mallocs);
  print_clocks(end_cpu - start_cpu);
}

/* Shell function for insertion sort. */

void insertion_sort(int *list, int n)
{
  int comparisons = 0;
  int block_copies = 0;
  int total_copies = 0;
  clock_t start_cpu, end_cpu;
  printf("Insertion sort %d integers...\n", n);
  start_cpu = clock();

  insertion_sort_internal(list, n, &comparisons, &total_copies, &block_copies);

  end_cpu = clock();
  printf("Sort complete with %d comparisons and %d block copies (%d total copies).\n", comparisons, block_copies, total_copies);
  print_clocks(end_cpu - start_cpu);

  return;
}

int *make_some_integers(int n)
{
  int *integers = malloc(sizeof(int) * n);

  time_t t;

  srand((unsigned) time(&t));

  for(int i = 0; i < n; i++)
  {
    integers[i] = rand() % 100;
  }

  return integers;
}

/* Main program. */

int main(void) {
  int n = 500;
  int *our_list = make_some_integers(n);
  int *our_unsorted_list = malloc(sizeof(int) * n);

//  output_integer_list(our_list, n, "unsorted values");

  memcpy(our_unsorted_list, our_list, sizeof(int) * n);
  bubble_sort(our_unsorted_list, n);

  memcpy(our_unsorted_list, our_list, sizeof(int) * n);
  selection_sort(our_unsorted_list, n);

  memcpy(our_unsorted_list, our_list, sizeof(int) * n);
  quick_sort(our_unsorted_list, n);



  memcpy(our_unsorted_list, our_list, sizeof(int) * n);
  insertion_sort(our_unsorted_list, n);



  memcpy(our_unsorted_list, our_list, sizeof(int) * n);
  merge_sort(our_unsorted_list, n);



  memcpy(our_unsorted_list, our_list, sizeof(int) * n);
  merge_insertion_sort(our_unsorted_list, n);




  free(our_list);
  free(our_unsorted_list);
  return 0;
}