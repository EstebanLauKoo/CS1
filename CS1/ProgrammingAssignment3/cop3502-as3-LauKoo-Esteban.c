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

typedef struct monster
{
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

    srand((unsigned)time(&t));

    for (int i = 0; i < n; i++)
    {
        monsters[i].id = i;
        sprintf(monsters[i].name, "Monster #%d", rand());
        sprintf(monsters[i].element, "Element #%d", rand());
        monsters[i].population = rand();
        monsters[i].weight = 500.0 * ((double)rand() / (double)RAND_MAX);
    }

    return monsters;
}

void ofp_print(FILE *ofp, monster *list, int n)
{

    for (int i = 0; i < n; i++)
    {

        fprintf(ofp, "  Monster %d: %s %s %d %lf\n", i, list[i].name, list[i].element, list[i].population, list[i].weight);
    }
    fprintf(ofp, "\n");
}

void output_monster_list(monster *list, int n, char *title)
{
    printf("List %s:\n", title);
    for (int i = 0; i < n; i++)
    {
        printf("  Monster %d: %s %s %d %lf\n", list[i].id, list[i].name, list[i].element, list[i].population, list[i].weight);
    }
    printf("\n");
}

void print_clocks(clock_t clocks)
{
    printf("  %lfs CPU time used\n", ((double)clocks) / CLOCKS_PER_SEC);
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

    /* compares a monster to another to make sure its in order returns
  a 0 or 1 depending if its true or. */

    if (use_weight == 1)
    {

        if (m1->weight <= m2->weight)
        {

            return 0;
        }

        else
        {

            return 1;
        }
    }

    /* manipulates the string so that it takes only the integer, then compares the integer
  to check if they are in order */

    else if (use_name == 1)
    {

        char *s1 = m1->name;
        char *s2 = m2->name;

        char *tokens1 = strtok(s1, "Monster #");
        char *tokens2 = strtok(s2, "Monster #");

        int s1Atoi = atoi(tokens1);
        int s2Atoi = atoi(tokens2);

        if (use_name == 1)
        {

            if (s1Atoi <= s2Atoi)
            {

                return 0;
            }

            else
            {

                return 1;
            }
        }

        else
        {

            printf("incorrect arguments for the compare monsters\n");

            return 1;
        }

        return 1;
    }
    return 1;
}

void check_monster_sort(monster *list, int n, int use_name, int use_weight)
{
    for (int i = 1; i < n; i++)
    {
        if (compare_monsters(list + i - 1, list + i, use_name, use_weight) > 0)
        {
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

    /* partitions around the pivot value and swaps accordingly compares weights, returns the pivot index 
  after*/

    if (use_weight == 1)
    {

        monster pivot_value = list[high_index];

        int i = low_index;

        for (int j = low_index; j < high_index; j++)
        {

            (*comparisons)++;
            if (list[j].weight < pivot_value.weight)
            {

                (*swaps)++;
                swap_monsters(list, i, j);
                i++;
            }
        }

        swaps++;
        swap_monsters(list, i, high_index);
        return i;
    }

    /* partitions around the pivot value and swaps accordingly compares name*/

    else if (use_name == 1)
    {

        monster pivot_value = list[high_index];

        char *s1 = pivot_value.name;
        char *tokens1 = strtok(s1, "Monster #");
        int s1Atoi = atoi(tokens1);

        int i = low_index;

        for (int j = low_index; j < high_index; j++)
        {

            char *s2 = list[j].name;
            char *tokens2 = strtok(s2, "Monster #");
            int s2Atoi = atoi(tokens2);

            (*comparisons)++;
            if (s2Atoi < s1Atoi)
            {

                (*swaps)++;
                swap_monsters(list, i, j);
                i++;
            }
        }

        swaps++;
        swap_monsters(list, i, high_index);
        return i;
    }

    return 0;
}

/* Recursive function for quick sort. */

void quick_sort_recursive(monster *list, int low_index, int high_index, int *comparisons, int *swaps,
                          int use_name, int use_weight)
{
    // YOUR CODE GOES HERE.
    /* recursively calls the function depending the condition and finds the pivot index */
    int pivot_index = repartition(list, low_index, high_index, comparisons, swaps, use_name, use_weight);

    if (pivot_index - 1 > low_index)
    {

        quick_sort_recursive(list, low_index, pivot_index - 1, comparisons, swaps, use_name, use_weight);
    }

    if (high_index > pivot_index + 1)
    {

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
    quick_sort_recursive(list, 0, n - 1, &comparisons, &swaps, use_name, use_weight);
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

    /* basic bubble sort compares the list with the one above it and checks if its higher and goes through
  the whole list */

    if (use_weight == 1)
    {
        for (i = n - 1; i >= 0; i--)
        {
            for (j = 0; j < i; j++)
            {
                comparisons++;
                if (list[j].weight > list[j + 1].weight)
                {
                    swaps++;
                    swap_monsters(list, j, j + 1);
                }
            }
        }
    }

    /* name variation for the bubble sort */

    else if (use_name == 1)
    {

        for (i = n - 1; i >= 0; i--)
        {
            for (j = 0; j < i; j++)
            {
                char *s1 = list[j].name;
                char *s2 = list[j + 1].name;

                char *tokens1 = strtok(s1, "Monster #");
                char *tokens2 = strtok(s2, "Monster #");

                int s1Atoi = atoi(tokens1);
                int s2Atoi = atoi(tokens2);

                comparisons++;

                if (s1Atoi > s2Atoi)
                {
                    swaps++;
                    swap_monsters(list, j, j + 1);
                }
            }
        }
    }

    else
    {

        printf("incorrect arguments passed to bubble sort\n");
    }

    end_cpu = clock();
    printf("Sort complete with %d comparisons and %d swaps.\n", comparisons, swaps);
    print_clocks(end_cpu - start_cpu);
}

/* Highest-value finder for selection sort. */

int find_highest(monster *list, int n, int *comparisons, int use_name, int use_weight)
{

    if (use_weight == 1)
    {

        double highest_val = INT_MIN;
        int highest_loc = -1;
        int i;

        for (i = 0; i <= n; i++)
        {
            (*comparisons)++;
            if (list[i].weight > highest_val)
            {
                highest_loc = i;
                highest_val = list[i].weight;
            }
        }

        return highest_loc;
    }

    else if (use_name == 1)
    {

        int highest_val = INT_MIN;
        int highest_loc = -1;
        int i;

        for (i = 0; i <= n; i++)
        {
            (*comparisons)++;

            char *s1 = list[i].name;
            char *tokens1 = strtok(s1, "Monster #");
            int s1Atoi = atoi(tokens1);

            if (s1Atoi > highest_val)
            {
                highest_loc = i;
                highest_val = s1Atoi;
            }
        }

        return highest_loc;
    }

    else
    {

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

    /* first finds the highest and if the current i is not the same position as highest it swaps them. */

    for (i = n - 1; i >= 0; i--)
    {
        highest = find_highest(list, i, &comparisons, use_name, use_weight);
        if (highest != i)
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

    /* you set the position to the high index and then compare the values until 
  either the array reaches below the low index or the weight is not higher than the key. 
  key is defined as i which is 1 above the lowe index that is sent in the arguments. 
  it'll lower both the position and comparisonIndex ints until the conditions are false 
  and then return the position for the key that we are looking at.*/
    int position;
    int ComparisonIndex;

    ComparisonIndex = high_index - 1;

    position = high_index;

    if (use_weight == 1)
    {

        while (ComparisonIndex >= low_index && list[ComparisonIndex].weight > (k->weight))
        {

            position--;
            ComparisonIndex--;
            (*comparisons)++;
        }

        return position;
    }

    else if (use_name == 1)
    {

        char *s1 = list[ComparisonIndex].name;
        char *s2k = k->name;

        char *tokens1 = strtok(s1, "Monster #");
        char *tokens2 = strtok(s2k, "Monster #");

        int s1Atoi = atoi(tokens1);
        int s2kAtoi = atoi(tokens2);

        while (ComparisonIndex >= low_index && s1Atoi > s2kAtoi)
        {

            position--;

            ComparisonIndex--;
            (*comparisons)++;

            s1 = list[ComparisonIndex].name;
            tokens1 = strtok(s1, "Monster #");
            s1Atoi = atoi(tokens1);
        }

        return position;
    }

    else
    {

        printf("incorrect arguments passed to insertion_sort_find_position \n");
    }
    return 0;
}

/* Implement insertion sort. */

void insertion_sort_internal(monster *list, int n, int *comparisons, int *copies, int *block_copies, int use_name, int use_weight)
{
    // YOUR CODE GOES HERE.
    int i, j;
    int position;
    monster key;
    int tempArraySize;

    j = 0;

    /* creates a key and sets position equal to the function find_position, then memcopies
both the temp key and the block copy. memmoves the data and places temp back in. */
    for (i = 1; i < n; i++)
    {

        key = list[i];

        position = insertion_sort_find_position(list, j, i, &key, comparisons, use_name, use_weight);

        tempArraySize = i - position;

        monster *listTemp = malloc(sizeof(monster) * tempArraySize);
        monster *temp = malloc(sizeof(monster) * 1);

        memcpy(temp, list + i, sizeof(monster));
        memcpy(listTemp, list + position, tempArraySize * sizeof(monster));

        (*copies)++;
        (*block_copies)++;
        (*copies) += (tempArraySize * 2);

        memmove(list + position + 1, listTemp, tempArraySize * sizeof(monster));
        memmove(list + position, temp, sizeof(monster));

        free(listTemp);
        free(temp);
    }
}

/* Shell for insertion sort. */

void insertion_sort(monster *list, int n, int use_name, int use_weight)
{
    int comparisons = 0;
    int block_copies = 0;
    int total_copies = 0;
    clock_t start_cpu, end_cpu;
    printf("Insertion sort %d monsters by %s...\n", n, use_name ? "name" : "weight");
    start_cpu = clock();

    insertion_sort_internal(list, n, &comparisons, &total_copies, &block_copies, use_name, use_weight);

    end_cpu = clock();
    printf("Sort complete with %d comparisons and %d block copies (%d total copies).\n", comparisons, block_copies, total_copies);
    print_clocks(end_cpu - start_cpu);
    return;
}

/* Merge function for merge sort.  Merges sub-arrays [l1..h1] and [l2..h2].
   Must have l2 = l1 + 1 or bad things will happen. */

void merge_sort_merge(monster *list, int l1, int h1, int l2, int h2,
                      int *comparisons, int *copies, int *block_copies, int *mallocs,
                      int use_name, int use_weight)
{
    // YOUR CODE GOES HERE.

    /* mallocs left right and partial arrays, memcpys from list to the auxArrays depending 
    on the index values given in arguments, compares the right array to the left array and copies
    it to the partial full array fills in the rest of the left and right array into the full */

    if (use_weight == 1)
    {

        int i, j, k;
        int leftArraySize = h1 - l1 + 1;
        int rightArraySize = h2 - h1;
        int fullArraySize = h2 + 1;

        monster *auxArrayL = malloc(sizeof(monster) * leftArraySize);
        monster *auxArrayR = malloc(sizeof(monster) * rightArraySize);
        monster *auxFullArray = malloc(sizeof(monster) * fullArraySize);
        (*mallocs)++;

        memcpy(auxArrayL, list + l1, leftArraySize * sizeof(monster));
        (*block_copies)++;
        memcpy(auxArrayR, list + h1 + 1, rightArraySize * sizeof(monster));
        (*block_copies)++;

        i = 0;
        j = 0;
        k = l1;

        while (i < leftArraySize && j < rightArraySize)
        {

            if (auxArrayL[i].weight <= auxArrayR[j].weight)
            {
                (*comparisons)++;
                auxFullArray[k] = auxArrayL[i];
                (*copies)++;
                i++;
            }

            else
            {
                (*comparisons)++;
                auxFullArray[k] = auxArrayR[j];
                (*copies)++;
                j++;
            }
            k++;
        }

        while (i < leftArraySize)
        {

            auxFullArray[k] = auxArrayL[i];
            (*copies)++;
            i++;
            k++;
        }

        while (j < rightArraySize)
        {

            auxFullArray[k] = auxArrayR[j];
            (*copies)++;
            j++;
            k++;
        }

        for (i = l1; i <= h2; i++)
        {
            (*copies)++;
            list[i] = auxFullArray[i];
        }
    }

    else if (use_name == 1)
    {

        int i, j, k;
        int leftArraySize = h1 - l1 + 1;
        int rightArraySize = h2 - h1;
        int fullArraySize = h2 + 1;

        monster *auxArrayL = malloc(sizeof(monster) * leftArraySize);
        monster *auxArrayR = malloc(sizeof(monster) * rightArraySize);
        monster *auxFullArray = malloc(sizeof(monster) * fullArraySize);
        (*mallocs)++;

        memcpy(auxArrayL, list + l1, leftArraySize * sizeof(monster));
        (*block_copies)++;
        memcpy(auxArrayR, list + h1 + 1, rightArraySize * sizeof(monster));
        (*block_copies)++;

        i = 0;
        j = 0;
        k = l1;

        while (i < leftArraySize && j < rightArraySize)
        {

            char *s1 = auxArrayL[i].name;
            char *s2 = auxArrayR[j].name;

            char *tokens1 = strtok(s1, "Monster #");
            char *tokens2 = strtok(s2, "Monster #");

            int s1Atoi = atoi(tokens1);
            int s2Atoi = atoi(tokens2);

            if (s1Atoi <= s2Atoi)
            {
                (*comparisons)++;
                auxFullArray[k] = auxArrayL[i];
                i++;
                (*copies)++;
            }

            else
            {
                (*comparisons)++;
                auxFullArray[k] = auxArrayR[j];
                j++;
                (*copies)++;
            }
            k++;
        }

        while (i < leftArraySize)
        {

            auxFullArray[k] = auxArrayL[i];
            i++;
            k++;
            (*copies)++;
        }

        while (j < rightArraySize)
        {

            auxFullArray[k] = auxArrayR[j];
            j++;
            k++;
            (*copies)++;
        }

        for (i = l1; i <= h2; i++)
        {
            (*copies)++;
            list[i] = auxFullArray[i];
        }
    }

    else
    {

        printf("incorrect arguments passed to merge_sort \n");
    }
}

/* Recursive function for merge sort. */

void merge_sort_recursive(monster *list, int low_index, int high_index,
                          int *comparisons, int *copies, int *block_copies, int *mallocs,
                          int use_name, int use_weight)
{
    // YOUR CODE GOES HERE.
    /* checks to see if the index is 1 if it is, it goes back up the recursion. recursively calls
    itself and then merges them */
    if (high_index <= low_index)
    {
        return;
    }

    else
    {

        int half = (low_index + high_index) / 2;

        merge_sort_recursive(list, low_index, half, comparisons, copies, block_copies, mallocs, use_name, use_weight);
        merge_sort_recursive(list, half + 1, high_index, comparisons, copies, block_copies, mallocs, use_name, use_weight);

        merge_sort_merge(list, low_index, half, half + 1, high_index, comparisons, copies, block_copies, mallocs, use_name, use_weight);
    }
}

/* Implement merge sort. */

void merge_sort(monster *list, int n, int use_name, int use_weight)
{
    int comparisons = 0;
    int copies = 0;
    int block_copies = 0;
    int mallocs = 0;
    clock_t start_cpu, end_cpu;

    printf("Merge sort %d monsters...\n", n);

    start_cpu = clock();
    merge_sort_recursive(list, 0, n - 1, &comparisons, &copies, &block_copies, &mallocs,
                         use_name, use_weight);
    end_cpu = clock();

    printf("Sort complete with %d comparisons, %d block copies, %d total copies, %d mallocs.\n", comparisons, block_copies, copies, mallocs);
    print_clocks(end_cpu - start_cpu);
}

/* Recursive function for merge-insertion sort. */

void merge_insertion_sort_recursive(monster *list, int low_index, int high_index,
                                    int *comparisons, int *copies, int *block_copies, int *mallocs,
                                    int use_name, int use_weight)
{
    // YOUR CODE GOES HERE.

    /* checks to see if the size of the list is <= 25, if it is then it will run through
    insertion_sort_find_position from the low index - high index. if it isn't it will continue to
    call itself until the list are small enough  */

    int n = 1;
    n = high_index - low_index + 1;

    int half = (low_index + high_index) / 2;

    if (n <= 25)
    {

        int i;
        monster key;
        int position;

        for (i = low_index + 1; i < high_index + 1; i++)
        {

            char *s1 = list[low_index].name;
            char *tokens1 = strtok(s1, "Monster #");
            key = list[i];

            position = insertion_sort_find_position(list, low_index, i, &key, comparisons, use_name, use_weight);

            int tempArraySize = i - position;

            monster *listTemp = malloc(sizeof(monster) * tempArraySize);
            monster *temp = malloc(sizeof(monster) * 1);
            (*copies)++;
            memcpy(temp, list + i, sizeof(monster));

            memcpy(listTemp, list + position, tempArraySize * sizeof(monster));
            (*block_copies)++;
            (*copies) += (tempArraySize * 2);

            memmove(list + position + 1, listTemp, tempArraySize * sizeof(monster));

            memmove(list + position, temp, sizeof(monster));
        }

        return;
    }

    else
    {

        merge_insertion_sort_recursive(list, low_index, half, comparisons, copies, block_copies, mallocs, use_name, use_weight);
        merge_insertion_sort_recursive(list, half + 1, high_index, comparisons, copies, block_copies, mallocs, use_name, use_weight);
    }

    merge_sort_merge(list, low_index, half, half + 1, high_index, comparisons, copies, block_copies, mallocs, use_name, use_weight);
}

/* Implement merge sort. */

void merge_insertion_sort(monster *list, int n, int use_name, int use_weight)
{

    int comparisons = 0;
    int copies = 0;
    int block_copies = 0;
    int mallocs = 0;
    clock_t start_cpu, end_cpu;

    printf("Merge-insertion sort %d monsters...\n", n);

    start_cpu = clock();
    merge_insertion_sort_recursive(list, 0, n - 1, &comparisons, &copies, &block_copies, &mallocs,
                                   use_name, use_weight);
    end_cpu = clock();

    printf("Sort complete with %d comparisons, %d block copies, %d total copies, %d mallocs.\n", comparisons, block_copies, copies, mallocs);
    print_clocks(end_cpu - start_cpu);
}

/* Main program. */

void run_all_sorts(int n, int only_fast, int use_name, int use_weight)
{

    monster *our_list = make_some_monsters(n);
    monster *our_unsorted_list = malloc(sizeof(monster) * n);

    printf("SORT SET: n = %d, %s, by %s\n\n", n, only_fast ? "fast sorts only" : "all sorts", use_name ? "name" : "weight");

    if (only_fast == 0)
    {

        memcpy(our_unsorted_list, our_list, sizeof(monster) * n);
        bubble_sort(our_unsorted_list, n, use_name, use_weight);
        check_monster_sort(our_unsorted_list, n, use_name, use_weight);

        memcpy(our_unsorted_list, our_list, sizeof(monster) * n);
        selection_sort(our_unsorted_list, n, use_name, use_weight);
        check_monster_sort(our_unsorted_list, n, use_name, use_weight);

        memcpy(our_unsorted_list, our_list, sizeof(monster) * n);
        insertion_sort(our_unsorted_list, n, use_name, use_weight);
        check_monster_sort(our_unsorted_list, n, use_name, use_weight);
    }

    memcpy(our_unsorted_list, our_list, sizeof(monster) * n);
    quick_sort(our_unsorted_list, n, use_name, use_weight);
    check_monster_sort(our_unsorted_list, n, use_name, use_weight);

    memcpy(our_unsorted_list, our_list, sizeof(monster) * n);
    merge_sort(our_unsorted_list, n, use_name, use_weight);
    check_monster_sort(our_unsorted_list, n, use_name, use_weight);

    memcpy(our_unsorted_list, our_list, sizeof(monster) * n);
    merge_insertion_sort(our_unsorted_list, n, use_name, use_weight);
    check_monster_sort(our_unsorted_list, n, use_name, use_weight);

    printf("SORT SET COMPLETE\n\n");

    free(our_list);
    free(our_unsorted_list);
}

int main(void)
{

    run_all_sorts(50, 0, 0, 1);
    run_all_sorts(50, 0, 1, 0);
    run_all_sorts(500, 0, 0, 1);
    run_all_sorts(500, 0, 1, 0);
    run_all_sorts(5000, 0, 0, 1);
    run_all_sorts(5000, 0, 1, 0);
    run_all_sorts(50000, 1, 0, 1);
    run_all_sorts(50000, 1, 1, 0);
    run_all_sorts(500000, 1, 0, 1);
    run_all_sorts(500000, 1, 1, 0);
}
