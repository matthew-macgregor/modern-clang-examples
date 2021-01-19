#include <stdio.h>
#include <assert.h>
#include <stdarg.h>

int prototype(int b);

// Simple Function
// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

int sum(int a, int b)
{
    return a + b;
}

// Void Params
// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

/*
* In C, a function that does not have a void param list
* accepts any number of parameters. This differs from C++.
*/
void void_params1() 
{
    // Accepts unknown number of parameters
    printf("Unknown\n");
}

void void_params2(void) 
{
    // Accepts zero parameters
    printf("Zero parameters\n");
}

// Variable Param Lists
// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
int sum_vargs(int count, ...) 
{
    va_list args;
    int sum = 0, i = 0;
    va_start(args, count);
    for (i = 0; i < count; i++)
    {
        sum += va_arg(args, int);
    }

    va_end(args); // important: frees the memory
    return sum;
}

void pass_by_value(int n)
{
    n++;
}

void pass_by_reference(int *n)
{
    (*n)++;
}

int main(void)
{
    assert(sum(1, 2) == 3);
    void_params1(1,2,3);
    void_params2(1234);     // <= Generates a warning
    assert(prototype(3) == 9);
    // 4 params, values(1,2,3,4)
    assert(sum_vargs(4, /* <- Count */ 1, 2, 3, 4) == 10);
    int f = 4;
    pass_by_value(f);
    assert(f == 4);
    pass_by_reference(&f);
    assert(f == 5);
    return 0;
}

/* Implementation */
int prototype(int b)
{
    return b * b;
}