// all-monster-sorts.c - Sort monsters by name and weight.

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

/* Monster structure and helper functions - DO NOT MODIFY THESE. */

typedef struct monster {
	int id;
	char name[64];
	char element[64];
	int population;
	double weight;
} monster;

monster *make_some_monsters(int n)
{
  monster *monsters = malloc(sizeof(monster) * n);

  time_t t;

  srand((unsigned) time(&t));

  for(int i = 0; i < n; i++)
  {
    monsters[i].id = i;
    sprintf(monsters[i].name, "Monster #%d", rand());
    sprintf(monsters[i].element, "Element #%d", rand());
    monsters[i].population = rand();
    monsters[i].weight = 500.0 * ((double) rand() / (double) RAND_MAX);
  }

  return monsters;
}

void ofp_print(FILE *ofp, monster *list, int n) {

  for(int i = 0; i < n; i++) {
    
    fprintf(ofp,"  Monster %d: %s %s %d %lf\n", i, list[i].name, list[i].element, list[i].population, list[i].weight);
  }
  fprintf(ofp,"\n");

}

void output_monster_list(monster *list, int n, char *title) {
  printf("List %s:\n", title);
  for(int i = 0; i < n; i++) {
    printf("  Monster %d: %s %s %d %lf\n", i, list[i].name, list[i].element, list[i].population, list[i].weight);
  }
  printf("\n");
}

void print_clocks(clock_t clocks) {
  printf("  %lfs CPU time used\n", ((double) clocks) / CLOCKS_PER_SEC);
}

void swap_monsters(monster *list, int i, int j)
{
  monster temp;

  memcpy(&temp, list + i, sizeof(monster));
  memcpy(list + i, list + j, sizeof(monster));
  memcpy(list + j, &temp, sizeof(monster));
}

/* The core comparison function. */

int compare_monsters(monster *m1, monster *m2, int use_name, int use_weight)
{
  // YOUR CODE GOES HERE.
  if (use_weight == 1) {

    if (m1->weight <= m2->weight) {

      return 0;

    }

    else {

      return 1;
    
    } 


  }

  // how to compare char strings?

  else if (use_name == 1) {

        char *s1 = m1->name;
        char *s2 = m2->name;

        char * tokens1 = strtok(s1, "Monster #");
        char * tokens2 = strtok(s2, "Monster #");


        int s1Atoi = atoi(tokens1);
        int s2Atoi = atoi(tokens2);

  if (use_name == 1) {


    if (s1Atoi <= s2Atoi) {

      return 0;

    }

    else {

      return 1;
    
    }

      
  } 

  else {

    printf("incorrect arguments for the compare monsters\n");

    return 0;

  }

  return 0;


}

}

void check_monster_sort(monster *list, int n, int use_name, int use_weight)
{
  for(int i = 1; i < n; i++) {
    if(compare_monsters(list + i - 1, list + i, use_name, use_weight) > 0) {
      printf("*** The list is NOT sorted.\n\n");
      return;
    }
  }
  printf("The list is sorted.\n\n");
}

/* The core comparison function. */



/* Implement ascending quick sort. */

int repartition(monster *list, int low_index, int high_index, int *comparisons, int *swaps,
                int use_name, int use_weight)
{
  // YOUR CODE GOES HERE.
if (use_weight == 1 ) {


  monster pivot_value = list[high_index];

  int i = low_index;
  
  for (int j = low_index; j < high_index; j++) {

    (*comparisons)++;
    if(list[j].weight < pivot_value.weight) {

      (*swaps)++;
      swap_monsters(list, i, j);
      i++;

    }

  }

  swaps++;
  swap_monsters(list, i, high_index);
  return i;   

  }

  else if (use_name == 1) {



  monster pivot_value = list[high_index];

  char *s1 = pivot_value.name;
  char * tokens1 = strtok(s1, "Monster #");
  int s1Atoi = atoi(tokens1);

  int i = low_index;
  
  for (int j = low_index; j < high_index; j++) {

  char *s2 = list[j].name;
  char * tokens2 = strtok(s2, "Monster #");
  int s2Atoi = atoi(tokens2);  

    (*comparisons)++;
    if(s2Atoi < s1Atoi) {

      (*swaps)++;
      swap_monsters(list, i, j);
      i++;

    }

  } 

  swaps++;
  swap_monsters(list, i, high_index);
  return i;   


  }



}

/* Recursive function for quick sort. */

void quick_sort_recursive(monster *list, int low_index, int high_index, int *comparisons, int *swaps,
                          int use_name, int use_weight)
{
  // YOUR CODE GOES HERE.
  int pivot_index = repartition(list, low_index, high_index, comparisons, swaps, use_name, use_weight);

  if (pivot_index - 1 > low_index) {

    quick_sort_recursive(list,low_index,pivot_index - 1, comparisons, swaps, use_name, use_weight);

  }

  if(high_index > pivot_index + 1) {

    quick_sort_recursive(list, pivot_index + 1, high_index, comparisons, swaps, use_name, use_weight);

  }

}

/* Shell function for quick sort. */

void quick_sort(monster *list, int n, int use_name, int use_weight)
{
  int comparisons = 0;
  int swaps = 0;
  clock_t start_cpu, end_cpu;

  printf("Quick sort %d monsters by %s...\n", n, use_name ? "name" : "weight");

  start_cpu = clock();
  quick_sort_recursive(list, 0, n-1, &comparisons, &swaps, use_name, use_weight);
  end_cpu = clock();

  printf("Sort complete with %d comparisons and %d swaps.\n", comparisons, swaps);
  print_clocks(end_cpu - start_cpu);
}

/* Implement ascending bubble sort. */

void bubble_sort(monster *list, int n, int use_name, int use_weight) 
{
  int i;
  int j;
  int temp;
  int comparisons = 0;
  int swaps = 0;
  clock_t start_cpu, end_cpu;

  printf("Bubble sort %d monsters by %s...\n", n, use_name ? "name" : "weight");

  start_cpu = clock();

  // YOUR CODE GOES HERE.
  if (use_weight == 1 ) {
    for(i = n-1; i >= 0; i--)
    {
      for(j = 0; j < i; j++)
      {
        comparisons++;
        if(list[j].weight > list[j+1].weight) // Are our elements out of order?
        {
          swaps++;
          swap_monsters(list, j, j+1);
        }
      }
  }
    

  }

  else if (use_name == 1) {

    

    for(i = n-1; i >= 0; i--)
    {
      for(j = 0; j < i; j++)
      {
        char *s1 = list[j].name;
        char *s2 = list[j + 1].name;

        char * tokens1 = strtok(s1, "Monster #");
        char * tokens2 = strtok(s2, "Monster #");


        int s1Atoi = atoi(tokens1);
        int s2Atoi = atoi(tokens2);

        comparisons++;

      if(s1Atoi > s2Atoi) 
      {
        swaps++;
        swap_monsters(list, j, j+1);
      }

        // int ret = strcmp(list[j].name, list[j+1].name);

        //   if (ret > 0) {
        //   swaps++;
        //   swap_monsters(list, j+1, j);
          
        //   }
        
      }
  }



  }

  else {

    printf("incorrect arguments passed to bubble sort\n");

  }


  end_cpu = clock();
  printf("Sort complete with %d comparisons and %d swaps.\n", comparisons, swaps);
  print_clocks(end_cpu - start_cpu);
}

/* Highest-value finder for selection sort. */

int find_highest(monster *list, int n, int *comparisons, int use_name, int use_weight)
{

  if (use_weight == 1 ) {

  double highest_val = INT_MIN;
  int highest_loc = -1;
  int i;
  
  for(i = 0; i <= n; i++)
  {
    (*comparisons)++;
    if(list[i].weight > highest_val)
    {
      highest_loc = i;
      highest_val = list[i].weight;
    }
  }

  return highest_loc; 
    

  }

  else if (use_name == 1) {

    int highest_val = INT_MIN;
    int highest_loc = -1;
    int i;


    for(i = 0; i <= n; i++)
    {
      (*comparisons)++;

      char *s1 = list[i].name;
      char * tokens1 = strtok(s1, "Monster #");
      int s1Atoi = atoi(tokens1);

      if(s1Atoi > highest_val)
      {
        highest_loc = i;
        highest_val = s1Atoi;
      }
    }

    return highest_loc; 
      

  }

  else {

    printf("incorrect arguments passed to find_highest \n");

  }
  
  // YOUR CODE GOES HERE.
}

/* Implement ascending selection sort. */

void selection_sort(monster *list, int n, int use_name, int use_weight)
{
  int i;
  int highest;
  int comparisons = 0;
  int swaps = 0;
  clock_t start_cpu, end_cpu;

  printf("Selection sort %d monsters by %s...\n", n, use_name ? "name" : "weight");
  start_cpu = clock();

  // YOUR CODE GOES HERE.

  for(i = n-1; i >= 0; i--)
  {
    highest = find_highest(list, i, &comparisons, use_name, use_weight);
    if(highest != i)
    {
      swaps++;
      swap_monsters(list, highest, i);
    }
  }  

  end_cpu = clock();
  printf("Sort complete with %d comparisons and %d swaps.\n", comparisons, swaps);
  print_clocks(end_cpu - start_cpu);
}

/* Find position for insertion sort. */

int insertion_sort_find_position(monster *list, int low_index, int high_index, monster *k, int *comparisons, int use_name, int use_weight)
{
  // YOUR CODE GOES HERE.

  if (use_weight == 1 ) {
    // printf("testing arguments low_index: %d, high_index: %d \n", low_index, high_index );

    // printf("Monster key: name: %s weight:%f\n", k->name, k->weight);

    int position;
    // int lowerLimiter = low_index;
    int ComparisonIndex = high_index - 1;
    
    position = high_index;

    // this part is for the merge

    // printf("%d \n", lowerLimiter);


    while (ComparisonIndex >= low_index && list[ComparisonIndex].weight > (k->weight)) {

        list[ComparisonIndex + 1] = list[ComparisonIndex]; 
        position--;
        // printf("Before: low index + 1: name %s weight: %f\n", list[low_index + 1].name, list[low_index + 1].weight);
        ComparisonIndex--;
        (*comparisons)++;

    }

    list[ComparisonIndex + 1] = *k;
    return position;


    // while ((low_index >= 0) && (list[low_index].weight) > (k->weight)) {

    //     // printf("%f > %f \n", list[low_index].weight, k->weight);
    //     // printf("low_index %d, high_index %d\n", low_index, high_index);
    //     // printf("low index weight: %f low index -1 weight: %f\n" ,list[low_index].weight, list[low_index-1].weight);

    //     list[low_index + 1] = list[low_index]; 
    //     position--;
    //     // printf("Before: low index + 1: name %s weight: %f\n", list[low_index + 1].name, list[low_index + 1].weight);
    //     low_index--;
    //     (*comparisons)++;


    //     // printf("comparisons: %d\n", *comparisons);
        
    // }
  

    // list[low_index + 1] = *k;
    // return position;
    // printf("low index %d:\n", k);

    // printf("low index + 1: name %s weight: %f\n", list[low_index + 1].name, list[low_index + 1].weight);

  }

  else if (use_name == 1) {


    int position;
    int ComparisonIndex = high_index - 1;
    
    position = high_index;

    char *s1 = list[ComparisonIndex].name; // lowindex
    char *s2k = k->name; // key


    char * tokens1 = strtok(s1, "Monster #");
    char * tokens2 = strtok(s2k, "Monster #");

    int s1Atoi = atoi(tokens1);
    int s2kAtoi = atoi(tokens2);


    // this part is for the merge

    // printf("%d \n", lowerLimiter);


    while (ComparisonIndex >= low_index && s1Atoi > s2kAtoi) {

        list[ComparisonIndex + 1] = list[ComparisonIndex]; 
        position--;
        // printf("Before: low index + 1: name %s weight: %f\n", list[low_index + 1].name, list[low_index + 1].weight);
        ComparisonIndex--;
        (*comparisons)++;

        s1 = list[ComparisonIndex].name;
        tokens1 = strtok(s1, "Monster #");
        s1Atoi = atoi(tokens1);   

    }

    list[ComparisonIndex + 1] = *k;
    return position;

    // printf("KEY MOTHER FUCKER!: i %d name: %d \n",high_index , s2kAtoi);

    // if (low_index >= 0 && s1Atoi > s2kAtoi) {
    //       printf("%d > %d \n", s1Atoi, s2kAtoi);
    // }
    // else {
    //   printf("no change\n");
    // }

    // while (low_index >= 0 && s1Atoi > s2kAtoi) {


    //     // printf("low_index: %d, string1: %d \n", low_index, s1Atoi);

    //     (*comparisons)++;
    //     position--;
    //     // printf("%s is moving to %d\n", list[low_index].name, low_index + 1 );
    //     list[low_index + 1] = list[low_index]; 
        
    //     low_index = low_index - 1;

    //     s1 = list[low_index].name;
    //     tokens1 = strtok(s1, "Monster #");
    //     s1Atoi = atoi(tokens1);      

    // }

    // list[low_index + 1] = *k;
    // return position;
  }

  else {

    printf("incorrect arguments passed to find_highest \n");

  }


}

/* Implement insertion sort. */

void insertion_sort_internal(monster *list, int n, int *comparisons, int *copies, int *block_copies, int use_name, int use_weight, FILE *ofp)
{
  // YOUR CODE GOES HERE.
  int i, j;
  monster key;
  // printf("testing arguments n: %d, comparisons: %d, copies: %d, block copies: %d, usename: %d, useweight: %d \n", n, *comparisons, *copies, *block_copies, use_name, use_weight);
    j = 0;

    for (i = 1; i < n; i++) {
          // char *s1 = list[low_index].name; // lowindex
          //     char * tokens1 = strtok(s1, "Monster #");
      key = list[i];

      insertion_sort_find_position(list, j, i, &key, comparisons, use_name, use_weight);

    }
    // fprintf(ofp, "insertion sort\n");
    // fprintf(ofp, "-----------------------------\n");
    // for (i = 0; i < n; i++) {

    //   fprintf(ofp, "id :%d %s\n", i , list[i].name);

    // }

    

}

/* Shell for insertion sort. */

void insertion_sort(monster *list, int n, int use_name, int use_weight, FILE *ofp)
{
  int comparisons = 0;
  int block_copies = 0;
  int total_copies = 0;
  clock_t start_cpu, end_cpu;
  printf("Insertion sort %d monsters by %s...\n", n, use_name ? "name" : "weight");
  start_cpu = clock();

  insertion_sort_internal(list, n, &comparisons, &total_copies, &block_copies, use_name, use_weight,ofp);

  end_cpu = clock();
  printf("Sort complete with %d comparisons and %d block copies (%d total copies).\n", comparisons, block_copies, total_copies);
  print_clocks(end_cpu - start_cpu);
  return;
}

/* Merge function for merge sort.  Merges sub-arrays [l1..h1] and [l2..h2].
   Must have l2 = l1 + 1 or bad things will happen. */

void merge_sort_merge(monster *list, int l1, int h1, int l2, int h2, 
                      int *comparisons, int *copies, int *block_copies, int *mallocs,
                      int use_name, int use_weight, FILE *ofp)
{
  // YOUR CODE GOES HERE.

  // printf("merge sort merge running\n");
  if (use_weight == 1 ) {



  int i, j ,k;
  int leftArraySize = h1 - l1 + 1;
  int rightArraySize = h2 - h1;
  int fullArraySize = h2 + 1;



  // printf("l1: %d, h1 %d, l2 %d, h2 %d\n", l1, h1, l2, h2);
  // printf("size of arrays: n1: %d, n2 %d\n", n1, n2);

  monster *auxArrayL = malloc(sizeof(monster) * leftArraySize);
  (*mallocs)++;
  monster *auxArrayR = malloc(sizeof(monster) * rightArraySize);
  (*mallocs)++;
  monster *auxFullArray = malloc(sizeof(monster) * fullArraySize);
  (*mallocs)++;


  for (i = 0; i < leftArraySize; i++) {

    auxArrayL[i] = list[l1 + i]; 
    // printf("leftArray: index: %d weight: %f\n", i, auxArrayL[i].weight);

  }

  for (j = 0; j < rightArraySize; j++) {

    auxArrayR[j] = list[h1 + 1 + j];
    // printf("rightArray: index: %d number: %f\n", j, auxArrayR[j].weight);

  }

  // printf("\n");
  // printf("end of fork\n");

  i = 0;
  j = 0;
  k = l1;

  while ( i < leftArraySize && j < rightArraySize) {

    if (auxArrayL[i].weight <= auxArrayR[j].weight) {
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

    
  //   printf("fake array list: index: %d number: %f\n", i, auxFullArray[i].weight);

  // }

  for (i = l1; i <= h2; i++) {
     list[i] = auxFullArray[i];
  }

  // printf("l1: %d, h1 %d, l2 %d, h2 %d\n", l1, h1, l2, h2);

  // printf("actualist\n");
  // for (i = 0; i < 5; i++) {

    
  //   printf("list: index: %d number: %f\n", i, list[i].weight);

  // }

    

  }

  else if (use_name == 1) {

  int i, j ,k;
  int leftArraySize = h1 - l1 + 1;
  int rightArraySize = h2 - h1;
  int fullArraySize = h2 + 1;



  // printf("l1: %d, h1 %d, l2 %d, h2 %d\n", l1, h1, l2, h2);
  // printf("size of arrays: n1: %d, n2 %d\n", n1, n2);

  monster *auxArrayL = malloc(sizeof(monster) * leftArraySize);
  (*mallocs)++;
  monster *auxArrayR = malloc(sizeof(monster) * rightArraySize);
  (*mallocs)++;  
  monster *auxFullArray = malloc(sizeof(monster) * fullArraySize);
  (*mallocs)++;

  for (i = 0; i < leftArraySize; i++) {

    auxArrayL[i] = list[l1 + i]; 
    // printf("leftArray: index: %d weight: %f\n", i, auxArrayL[i].weight);

  }

  for (j = 0; j < rightArraySize; j++) {

    auxArrayR[j] = list[h1 + 1 + j];
    // printf("rightArray: index: %d number: %f\n", j, auxArrayR[j].weight);

  }

  // printf("\n");
  // printf("end of fork\n");

  i = 0;
  j = 0;
  k = l1;

  while ( i < leftArraySize && j < rightArraySize) {

    char *s1 = auxArrayL[i].name;
    char *s2 = auxArrayR[j].name;

    char * tokens1 = strtok(s1, "Monster #");
    char * tokens2 = strtok(s2, "Monster #");


    int s1Atoi = atoi(tokens1);
    int s2Atoi = atoi(tokens2);


    if (s1Atoi <= s2Atoi) {
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

    
  //   printf("fake array list: index: %d number: %f\n", i, auxFullArray[i].weight);

  // }

  for (i = l1; i <= h2; i++) {
     list[i] = auxFullArray[i];
  }

  // printf("l1: %d, h1 %d, l2 %d, h2 %d\n", l1, h1, l2, h2);

  // fprintf(ofp, "actualist\n");
  // for (i = 0; i < 50; i++) {

    
  //   fprintf(ofp, "list:id: %d name: %s \n", i, list[i].name);

  // }


  }

  else {

    printf("incorrect arguments passed to find_highest \n");

  }
}

/* Recursive function for merge sort. */

void merge_sort_recursive(monster *list, int low_index, int high_index, 
                          int *comparisons, int *copies, int *block_copies, int *mallocs,
                          int use_name, int use_weight, FILE *ofp)
{
  // YOUR CODE GOES HERE.

  if (high_index <= low_index) {
    return;
  }

  else {

  int half = (low_index + high_index) / 2;

  merge_sort_recursive(list, low_index, half, comparisons, copies, block_copies, mallocs, use_name, use_weight, ofp);
  merge_sort_recursive(list, half + 1, high_index, comparisons, copies, block_copies, mallocs, use_name, use_weight, ofp);

  merge_sort_merge(list, low_index, half, half + 1, high_index, comparisons, copies, block_copies, mallocs, use_name, use_weight, ofp);

  }
}

/* Implement merge sort. */

void merge_sort(monster *list, int n, int use_name, int use_weight, FILE *ofp)
{
  int comparisons = 0;
  int copies = 0;
  int block_copies = 0;
  int mallocs = 0;
  clock_t start_cpu, end_cpu;

  printf("Merge sort %d monsters...\n", n);

  start_cpu = clock();
  merge_sort_recursive(list, 0, n-1, &comparisons, &copies, &block_copies, &mallocs,
                       use_name, use_weight, ofp);
  end_cpu = clock();

  printf("Sort complete with %d comparisons, %d block copies, %d total copies, %d mallocs.\n", comparisons, block_copies, copies, mallocs);
  print_clocks(end_cpu - start_cpu);
}

/* Recursive function for merge-insertion sort. */

void merge_insertion_sort_recursive(monster *list, int low_index, int high_index, 
                                    int *comparisons, int *copies, int *block_copies, int *mallocs,
                                    int use_name, int use_weight, FILE *ofp)
{
  // YOUR CODE GOES HERE.
  // printf("high_index %d low_index %d\n", high_index, low_index);

  // if (high_index - low_index > 25 ) {
  //   printf("switched to insertion sort internal\n");
  //   insertion_sort_internal(list, high_index + 1, comparisons, copies, block_copies, use_name, use_weight);
  // }

  // else {

  // int half = (low_index + high_index) / 2;

  // merge_sort_recursive(list, low_index, half, comparisons, copies, block_copies, mallocs, use_name, use_weight);
  // merge_sort_recursive(list, half + 1, high_index, comparisons, copies, block_copies, mallocs, use_name, use_weight);

  // merge_sort_merge(list, low_index, half, half + 1, high_index, comparisons, copies, block_copies, mallocs, use_name, use_weight);

  // }
  int n = 1;
  n = high_index - low_index;
  // printf("n : %d\n", n);
  int half = (low_index + high_index) / 2;
  // printf("n : %d\n", n);
  if ( n > 25 ) {
    merge_insertion_sort_recursive(list, low_index, half, comparisons, copies, block_copies, mallocs, use_name, use_weight, ofp);
    merge_insertion_sort_recursive(list, half + 1, high_index, comparisons, copies, block_copies, mallocs, use_name, use_weight, ofp);
    merge_sort_merge(list, low_index, half, half + 1, high_index, comparisons, copies, block_copies, mallocs, use_name, use_weight, ofp);
  }

  else {

    // insertion_sort_internal(list, high_index + 1, comparisons, copies, block_copies, use_name, use_weight, ofp);

    int i, j;
    monster key;
    
        for (i = 1  ; i < high_index +1 ; i++) {

          // printf("i %d\n", i);

          // char *s1 = list[low_index].name; // lowindex
          //     char * tokens1 = strtok(s1, "Monster #");
      
      key = list[i];

      insertion_sort_find_position(list, low_index, i, &key, comparisons, use_name, use_weight);



    }
  // printf("comparisons %d\n", *comparisons);  
   
  // insertion_sort_internal(list, high_index + 1, comparisons, copies, block_copies, use_name, use_weight, ofp);




  } 

  



}

/* Implement merge sort. */

void merge_insertion_sort(monster *list, int n, int use_name, int use_weight, FILE *ofp)
{


  int comparisons = 0;
  int copies = 0;
  int block_copies = 0;
  int mallocs = 0;
  clock_t start_cpu, end_cpu;


  printf("Merge-insertion sort %d monsters...\n", n);

  start_cpu = clock();
  merge_insertion_sort_recursive(list, 0, n-1, &comparisons, &copies, &block_copies, &mallocs,
                                 use_name, use_weight, ofp);
  end_cpu = clock();

  printf("Sort complete with %d comparisons, %d block copies, %d total copies, %d mallocs.\n", comparisons, block_copies, copies, mallocs);
  print_clocks(end_cpu - start_cpu);
}

/* Main program. */

void run_all_sorts(int n, int only_fast, int use_name, int use_weight) {

  // introducing file ofp to see the data and not clog terminal 
  FILE *ofp;
  FILE *ifp;

  ofp = fopen("cop3502-as3-out-test-LauKoo-Esteban", "w");    

  monster *our_list = make_some_monsters(n);
  monster *our_unsorted_list = malloc(sizeof(monster) * n);

  printf("SORT SET: n = %d, %s, by %s\n\n", n, only_fast ? "fast sorts only" : "all sorts", use_name ? "name" : "weight");

  if(only_fast == 0) {


    // memcpy(our_unsorted_list, our_list, sizeof(monster) * n);
    // ofp_print(ofp, our_unsorted_list, n);
    // fprintf(ofp, "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
    // bubble_sort(our_unsorted_list, n, use_name, use_weight);
    // check_monster_sort(our_unsorted_list, n, use_name, use_weight);
    // fprintf(ofp, "Bubble sort list\n");
    // ofp_print(ofp, our_unsorted_list, n);


    // memcpy(our_unsorted_list, our_list, sizeof(monster) * n);
    // ofp_print(ofp, our_unsorted_list, n);
    // fprintf(ofp, "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
    // selection_sort(our_unsorted_list, n, use_name, use_weight);
    // check_monster_sort(our_unsorted_list, n, use_name, use_weight);
    // fprintf(ofp, "Selection sort list\n");
    // ofp_print(ofp, our_unsorted_list, n);


    memcpy(our_unsorted_list, our_list, sizeof(monster) * n);
    // ofp_print(ofp, our_unsorted_list, n);
    // fprintf(ofp, "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
    insertion_sort(our_unsorted_list, n, use_name, use_weight,ofp);
    check_monster_sort(our_unsorted_list, n, use_name, use_weight);
    // fprintf(ofp, "Insertion sort list\n");
    // ofp_print(ofp, our_unsorted_list, n);

  }

  // memcpy(our_unsorted_list, our_list, sizeof(monster) * n);
  // ofp_print(ofp, our_unsorted_list, n);
  // fprintf(ofp, "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
  // quick_sort(our_unsorted_list, n, use_name, use_weight);
  // check_monster_sort(our_unsorted_list, n, use_name, use_weight);
  // fprintf(ofp, "Quick sort list\n");
  // ofp_print(ofp, our_unsorted_list, n);

  // memcpy(our_unsorted_list, our_list, sizeof(monster) * n);
  // ofp_print(ofp, our_unsorted_list, n);
  // fprintf(ofp, "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
  // merge_sort(our_unsorted_list, n, use_name, use_weight, ofp);
  // check_monster_sort(our_unsorted_list, n, use_name, use_weight);
  // fprintf(ofp, "Merge sort list\n");
  // ofp_print(ofp, our_unsorted_list, n);

  // memcpy(our_unsorted_list, our_list, sizeof(monster) * n);
  // ofp_print(ofp, our_unsorted_list, n);
  // fprintf(ofp, "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
  // merge_insertion_sort(our_unsorted_list, n, use_name, use_weight, ofp);
  // check_monster_sort(our_unsorted_list, n, use_name, use_weight);
  // fprintf(ofp, "Quick sort list\n");
  // ofp_print(ofp, our_unsorted_list, n);

  printf("SORT SET COMPLETE\n\n");

  fclose(ofp);

  free(our_list);
  free(our_unsorted_list);
}

int main(void) {
  run_all_sorts(50, 0, 0, 1);
  // run_all_sorts(50, 0, 1, 0);
  // run_all_sorts(500, 0, 1, 0);
  // run_all_sorts(500, 0, 1, 0);
  // run_all_sorts(5000, 0, 0, 1);
  // run_all_sorts(5000, 0, 1, 0);
  // run_all_sorts(50000, 1, 0, 1);
  // run_all_sorts(50000, 1, 1, 0);
  // run_all_sorts(500000, 1, 0, 1);
  // run_all_sorts(500000, 1, 1, 0);
}