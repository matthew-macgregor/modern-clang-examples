#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#define INIT_SZ 10
#define OK 0
#define tprintf(...) printf("  >> " __VA_ARGS__)
#define begin(s) puts("BEGIN ::" s)
#define end(s) puts("END   ::" s)

struct S1
{
    int foo;
    int bar;
} S1;

bool cmp_s1(struct S1 *s1, struct S1 *s2)
{
    return s1->bar == s2->bar && s1->foo == s2->foo;
}

int dyn_alloc_block_array()
{
    begin("dyn_alloc_block_array");
    // Dynamically allocated array of 10 S1 structs
    struct S1 *s1_arr = calloc(INIT_SZ, sizeof S1);
    // Now that we've allocated the memory, we can loop through it
    for (int i = 0; i < INIT_SZ; i++)
    {
        s1_arr[i].foo = i;
        s1_arr[i].bar = i + 2;
    }

    for (int i = 0; i < INIT_SZ; i++)
    {
        assert(s1_arr[i].foo == i);
        assert(s1_arr[i].bar == i + 2);
    }

    // Free the whole block at once
    free(s1_arr);
    s1_arr = NULL;

    end("dyn_alloc_block_array");
    return OK;
}

int array_copy_of_element(struct S1 s1_arr[])
{
    begin("array_copy_of_element");
    // Get a *copy* the first element (by val)
    struct S1 s1 = s1_arr[0];  
    s1.foo = 0;
    s1.bar = 0;
    assert(cmp_s1(&s1, s1_arr) == false);
    assert(cmp_s1(&s1, &s1_arr[0]) == false); // Equivalent of the above
    tprintf("Value at first index in array has not been initialized: %d\n", s1_arr[0].foo);
    end("array_copy_of_element");
    return OK;
}

int array_pointer_to_element(struct S1 s1_arr[])
{
    begin("array_pointer_to_element");
    // Get a pointer to an element (by ref)
    struct S1 *s11 = s1_arr; // Pointer to the start of the array
    s11->foo = 1;
    s11->bar = 2;
    assert(s11->foo == s1_arr[0].foo);
    assert(s1_arr[0].foo == 1);
    assert(s1_arr[0].bar == 2);
    tprintf("Value at first index in array is initialized: %d\n", s1_arr[0].foo);
    end("array_pointer_to_element");
    return OK;
}

int array_pointer_arithmetic(struct S1 s1_arr[])
{
    begin("array_pointer_arithmetic");
    struct S1 *s11 = s1_arr; // Address of first item
    struct S1 *s12 = &s1_arr[1]; // Address of second item
    tprintf("Pointer to second element of array: %p %lld\n", s12, s12-s11);
    assert(s1_arr[1].foo == (s1_arr + 1)->foo);
    // Equivalent of the above
    struct S1 *s12_1 = (s1_arr + 1);
    tprintf("Pointers equal: %p == %p\n", s12, s12_1);
    assert(s12_1 == s12);
    end("array_pointer_arithmetic");
    return OK;
}

int array_of_pointers_to_structs()
{
    begin("array_of_pointers_to_structs");
    struct S1 **s1_ptr_arr;
    s1_ptr_arr = calloc(INIT_SZ, sizeof (struct S1*)); // 10 pointers
    // s1_ptr_arr now points to the beginning of a block of 
    // memory reserved for pointers to S1 structs
    for (int i = 0; i < INIT_SZ; i++)
    {
        s1_ptr_arr[i] = calloc(INIT_SZ, sizeof (struct S1));
        s1_ptr_arr[i]->foo = i;
        s1_ptr_arr[i]->bar = i+1;
    }

    tprintf("Pointer to first element in array: %p\n", s1_ptr_arr);

    assert(*s1_ptr_arr == s1_ptr_arr[0]);

    // Let's check that the contents of the memory location are what
    // we think that they should be
    for (int i = 0; i < INIT_SZ; i++)
    {
        assert(s1_ptr_arr[i]->foo == i);
        assert(s1_ptr_arr[i]->bar == i+1);
        assert(s1_ptr_arr[i] == *(s1_ptr_arr + i));
        // Haha, never do this at home, but here are two equivalent
        // dereferences for the S1 struc array. Nightmare of parens, though.
        assert(cmp_s1(&(*s1_ptr_arr[i]), &(**(s1_ptr_arr + i))));
    }
    end("array_of_pointers_to_structs");
    return OK;
}

int _swap(struct S1 *s1, struct  S1 *s2)
{
    int x, y = 0;
    x = s1->foo;
    y = s1->bar;
    s1->foo = s2->foo;
    s1->bar = s2->bar;
    s2->foo = x;
    s2->bar = y;
    return OK;
}

int pass_by_ref ()
{
    begin("pass_by_ref");
    struct S1 s1 = { .foo = 0, .bar = 1 };
    struct S1 s2 = { .foo = 23, .bar = 42 };
    struct S1 _s1 = s1; // This works because structs get copied
    struct S1 _s2 = s2;
    _swap(&s1, &s2);
    assert(cmp_s1(&s1, &_s2) == true);
    assert(cmp_s1(&s2, &_s1) == true);
    end("pass_by_ref");
    return OK;
}

void _pp_param (struct S1 **pArg)
{
    *pArg = malloc(sizeof(struct S1));
    (*pArg)->foo = 1;
    (*pArg)->bar = 2;
    assert((**pArg).foo == 1);
}

int pointer_to_pointer_param ()
{
    struct S1 *s1 = NULL;
    // Pass in the location of the pointer s1, and not the pointer itself.
    _pp_param(&s1);
    assert(s1->foo == 1);
    assert(s1->bar == 2);
    return OK;
}

int address_of ()
{
    begin("address_of");
    const int i = 0;
    const int *pi = &i;
    assert(pi == &i);
    const int **j = &pi; // j now contains the *address* of the pointer pi
    printf("J: %p\n", j);
    assert(j == &pi);
    end("address_of");
    assert(*j == pi);
    assert(**j == i);
    return OK;
}

int arrays()
{
    begin("arrays");
    struct S1 s1_arr[INIT_SZ];
    tprintf("Sizeof S1: %zu bytes\n", sizeof(S1));
    tprintf("Pointer to start of array: %p\n", s1_arr);
    end("arrays");

    array_copy_of_element(s1_arr);
    array_pointer_to_element(s1_arr);
    array_pointer_arithmetic(s1_arr);
    array_of_pointers_to_structs();

    return OK;
}

int main(int argc, char **argv) {
    assert(address_of() == OK);
    assert(arrays() == OK);
    assert(dyn_alloc_block_array() == OK);
    assert(pass_by_ref() == OK);
    assert(pointer_to_pointer_param() == OK);
    tprintf("Success.\n");
    return 0;
}
