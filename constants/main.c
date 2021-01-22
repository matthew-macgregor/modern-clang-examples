#include <stdio.h>
#include <assert.h>
#include <string.h>

int constant_vars ()
{
    const int myvar = 42;
    // myvar = 15; // compiler error!
    return myvar;
}

int constant_pointers ()
{
    const int myvar = 32;
    const int myvar2 = 5;
    const int* p = &myvar;
    // can change the address
    p = &myvar2; 
    // can't change the value
    // *p = 75; // compiler error!

    int* const pp = &myvar;
    // cannot change the address
    // pp = &myvar2;
    // can change the value
    *pp = myvar2;

    const int* const ppp = &myvar2;
    // cannot change the address
    // ppp = &myvar2;
    // cannot change the value
    // *ppp = 5;

    return *p + *pp + *ppp;
}

int constant_params (const int* var)
{
    return *var;
    // *var = 15; // compiler error!
}

int main(void)
{
    assert(constant_vars());
    assert(constant_pointers() == 15);
    int v = 15;
    assert(constant_params(&v) == 15);
    return 0;
}