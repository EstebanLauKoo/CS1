#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* This is a global variable.  I'm the instructor, so I get to. */

long long int Times_Called = 0;

/* Recursively determine a Fibonacci number. */

long long int fibonacci(int n) {
    /* Sequence is only determined over the natural numbers. */

    Times_Called++;

    if(n < 0) {
        return 0;
    }

    /* Base cases. */

    if(n == 0 || n == 1) {
        return 1;
    }

    /* Recursive case. */

    return(fibonacci(n-2) + fibonacci(n-1));
}

long long int Fibonacci_Cache[50];

void init_fibocache()
{
    for(int i = 0; i < 50; i++)
    {
        Fibonacci_Cache[i] = -1;
    }
    Fibonacci_Cache[0] = 1;
    Fibonacci_Cache[1] = 1;
}

long long int fibocache(int n) {
    Times_Called++;

    if(Fibonacci_Cache[n] == -1)
    {
        Fibonacci_Cache[n] = fibocache(n - 2) + fibocache(n - 1);
    }

    return Fibonacci_Cache[n];
}

/* Main program. */

int main(void)
{
    int i = 47;
   
    long long int fibo;
    init_fibocache();

    printf("Computing without a cache...\n");
    fibo = fibonacci(i);
    printf("  Fibonacci #%d is %lld.\n", i, fibo);
    printf("  We called fibonacci() a total of %lld times.\n", Times_Called);

    Times_Called = 0;
    printf("Computing with a cache...\n");
    fibo = fibocache(i);
    printf("  Fibonacci #%d is %lld.\n", i, fibo);
    printf("  We called fibonacci() a total of %lld times.\n", Times_Called);
}