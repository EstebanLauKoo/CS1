
#include <stdio.h>

#define MAX 100

int findMinIndex(int data[], int low, int high);

int main() {
    int i, loop, n, queries, data[MAX];

    // Read in the schedule data.
    FILE* ifp = fopen("schedule.in", "r");
    fscanf(ifp, "%d", &n);
    for (i=0; i<n; i++)
        fscanf(ifp, "%d", &data[i]);

    // Process each query.
    fscanf(ifp, "%d", &queries);
    for (loop=0; loop<queries; loop++) {
        int low, high;
        fscanf(ifp, "%d%d", &low, &high);
        printf("%d\n", findMinIndex(data, low, high));
    }

    return 0;
}

// Pre-condition:  low <= high and are both valid indexes to data.
// Post-condition: Returns the lowest index in [low, high] storing
//                 the minimum of array[low]�array[high].
int findMinIndex(int data[], int low, int high) {

// starts i and set the minIndex to low    
int i; 
int minIndex = low;

// for loop to go though the array and set min index to i. and returns min indez

for(i = low + 1; i < high; i++){

    if( data[i] < data[minIndex]) {

    minIndex = i;

    }

}

return minIndex;
}

