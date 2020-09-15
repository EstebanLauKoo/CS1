#include <stdio.h>
#include <stdlib.h>

// The structure we're using for a point.

struct point_struct
{
    int count;
    double xval;
    double yval;
    double zval;
    float alpha;
    char name[20];
};

// typedef <real type> <alias>;

typedef struct point_struct point;

int main(void)
{
    point *p;

    /* Initialize our point.  The arrow operator is a one-step dereference of a
       member of a struct being pointed at, so (p->count), (p[0].count) and
       ((*p).count) are all equal. */

    p = malloc(sizeof(point));

    p->count = 4;
    p->xval = 3.0;
    p->yval = 5.0;
    p->zval = 8.0;
    p->alpha = 2.0;
    strcpy(p->name, "Bob");

    // Print our results.

    printf("Hello, world!  We allocated %d bytes.\n", sizeof(point));

    // Destroy our point.

    free(p);
}