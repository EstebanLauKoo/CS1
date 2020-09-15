#include <stdio.h>
#include <stdlib.h>

struct point_struct {
    int count;
    double xval;
    double yval;
    double zval;
    float alpha;
    char name[20];
};
// type def basically lets you call it point p and also declares. Think alias or nickname

typedef struct point_struct point;


int main(void) {

    point *p;
    point *p_array;

    

    // Initialize our point. the arrow operator is a one-step dereference of a member of a struct being pointed at 

    // malloc (memory allocation) takes a little bit of memory and assigns it and returns a pointer to that memory.
    // point p; gets a memory space. static memory.
    // point *p; pointer variable thats points at a variable

    // homie malloc needs space he must go first.
    p = malloc(sizeof(point));
    
    // ((*p).count)
    // same as p -> count = 4
    // p[0].count = 4;
    

    // -> saying dereferencing
    p -> count = 4;
    p -> xval = 3.0;
    p -> yval = 5.0;
    p -> zval = 8.0;
    strcpy(p -> name, "Bob");

    // do whatever needs done

    // shift alt f to reformat (vscode only I believe)=

    // Free your homie malloc or malloc will crash your pc

    // print our results

    printf("Hello World! We allocated %d bytes. \n", sizeof(point));

    free(p);

    // Let's try the same thing with an array 
    // this lets you allocated 3 iterations of the struct point
    p_array = malloc(3 * sizeof(point));

    for (int i = 0; i < 3; i++) {
        p_array[i].count = i;
        p_array[i].xval = 3.0 * i;
    }


    printf("Hello World! We allocated %d bytes. \n", 3 * sizeof(point));

    free(p_array);

    
}