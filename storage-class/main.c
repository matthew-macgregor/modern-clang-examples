#include <stdio.h>
#include <assert.h>
#include <string.h>

// EXTERN
extern int exported;
extern int exported_func(void);

// This won't work:
// extern int internal_func(void);
// Try to use it and you'll get 'unresolved external symbol'

// AUTO
int auto_var ()
{
    // Auto is the default
    auto int autoVar;
    // Same as...
    int autoVar2;
    return 1;
}

// REGISTER
// Don't use it in modern code.

// STATIC
int test_static (int i)
{
    static int o = 0;
    return o += i;
}

// VOLATILE
// Tells the compiler that a variable might be changed from outside,
// avoids having it optimized away. An example of where this might
// be useful is if a hardware device changes memory directly.
volatile int vvar = 0;

int main (void)
{
    assert(exported == 42);
    assert(auto_var());
    assert(exported_func() == 5);
    test_static(5);
    assert(test_static(3) == 8);
    return 0;
}