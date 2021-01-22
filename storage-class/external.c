
int exported = 42;
// internal available only in this compilation unit (file)
static int internal = 5;

// internal_func not exported
static int internal_func ()
{
    return internal;
}

int exported_func ()
{
    return internal_func();
}

