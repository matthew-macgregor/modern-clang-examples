#include <stdio.h>
#include <assert.h>

void basic_array() 
{
    int arr[3]; // contiguous memory sized for 3 int on stack
    for (int i = 0; i < 3; i++)
    {
        arr[i] = i * i;
        printf("Array[%d] = %d\n", i, arr[i]);
    }

    int arr1[3] = { 1, 3, 5 };
    int arr2[] = { 1, 3, 5 };  // Equivalent to example above

    for (int i = 0; i < 3; i++)
    {
        printf("Array[%d] %d == %d\n", i, arr1[i], arr2[i]);
        assert(arr2[i] == arr1[i]);
    }
}

void multi_dim_array()
{
    int marr[2][2] = { { 0, 1 }, { 2, 3 } };
    // Alternative
    int marr2[2][2] = { 0, 1, 2, 3 };

    assert(marr[0][0] == 0);
    assert(marr[1][1] == 3);
    assert(marr2[1][1] == 3);
}

void array_as_pointer()
{
    // An array is a const pointer to the first element
    int marr[4] = { 0, 1, 2, 3 };
    assert(*(marr + 3) == 3);
    int *ptr = (int*) &marr;
    printf("Array addr: %p\n", ptr);
    ptr++;
    printf("Array addr: %p\n", ptr);
    assert((int) &marr != (int) ptr);
}

void sizeof_array()
{
    // Statically allocated array can be sized with sizeof
    int arr[4];
    int l = sizeof(arr) / sizeof(int);
    assert(l == 4); // ints
    printf("Size of arr[4] %d\n", sizeof(arr));
}

int main(int argc, char **argv)
{
    basic_array();
    multi_dim_array();
    array_as_pointer();
    sizeof_array();
    return 0;
}