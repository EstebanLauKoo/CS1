//Esteban Lau koo homework12

#include <stdio.h>

#define SIZE 5
#define PRINT 1

void swap(int* ptrA, int*ptrB);
void print(int array[], int length);
void fillArray(int array[], int length);
void GnomeSort(int gnomes[], int length);
int isSorted(int array[], int length);

int main() {
    int a[SIZE];

    fillArray(a, SIZE);
    if (PRINT) print(a, SIZE);
    GnomeSort(a, SIZE);
    if (PRINT) print(a, SIZE);

    // Print out the final result.
    if (isSorted(a, SIZE))
        printf("The sort worked properly.\n");
    else
        printf("There was a problem with the sort.\n");

    return 0;
}

// Prints out values in array[0]...array[length-1].
void print(int array[], int length) {
    int i;

    for (i=0; i<length; i++)
        printf("%d ", array[i]);
    printf("\n");

    return;
}


// Sorts the items array[0] through array[length-1] using the Gnome Sort algorithm.
void GnomeSort(int gnomes[], int length) {
    // could have used temp to swap the values but just went with swap.
    int temp;
    int pos = 1;
    while (pos < length) {
        if (gnomes[pos] >= gnomes[pos-1]) {
            pos = pos + 1;
        }
        else {

            swap(&gnomes[pos], &gnomes[pos - 1]);

            if (pos > 1) {
                pos = pos -1;
            }

        }
    }
    return;
}

// Swaps the variables pointed to by ptrA and ptrB.
void swap(int* ptrA, int* ptrB) {
    int temp = *ptrA;
    *ptrA = *ptrB;
    *ptrB = temp;
    return;
}

// Fills array[0] through array[length-1] with integers
// from a specified file
void fillArray(int array[], int length) {
    int i;
    char filename[20];
    FILE * ifp = NULL;

    printf("What is the name of the file?\n");
    scanf("%s", filename);
    ifp = fopen(filename, "r");

    for (i=0; i<length; i++)
        fscanf(ifp, "%d", &array[i]);

    fclose(ifp);

    return;
}

// Returns 1 iff array[0] through array[length-1] are
// in sorted order from smallest to largest.
int isSorted(int array[], int length) {
    int i;

    // Return false if a pair of consecutive values is out of order.
    for (i=0; i<length-1; i++)
        if (array[i] > array[i+1])
            return 0;

    return 1;
}
