#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>

void primitive_types ()
{
    // Size of data types is implementation-dependent
    // The standard specifies the minimum range, not the size
    // Integer types must be at least as large as the preceding type
    char c = '1'; // 1 byte
    short s = 2; // 2 bytes
    int i = 4; // usually 4 bytes
    long l = 4; // 4 or 8 bytes
    long long ll = 8; // 8 bytes -- added in C99
    float f = 4; // 4 bytes
    double d = 8; // 8 bytes
    long double ld = 8; // 8 or 16 bytes;
    long double *ptr = &ld;
    long a = 1023*1024;
    size_t sz = sizeof a; // uint 32
    int dec = 50;
    int oct = 062;
    int hex = 0x32;

    printf("char  %c (%i) == %zu bytes\n", c, c, sizeof c);
    printf("short %d == %zu bytes\n", s, sizeof s);
    printf("int   %d == %zu bytes\n", i, sizeof i);
    printf("long  %ld == %zu bytes\n", l, sizeof l);
    printf("long long %lld == %zu bytes\n", ll, sizeof ll);
    printf("float %f == %zu bytes\n", f, sizeof f);
    printf("double %f == %zu bytes\n", d, sizeof d);
    printf("long double %Lf == %zu bytes\n", ld, sizeof ld);
    printf("pointer %p == %zu bytes\n", ptr, sizeof ptr);
    printf("hex %x == %zu bytes\n", a, sizeof a);
    printf("size_t %zu bytes\n", sz);
    printf("dec %d, oct %d, hex %d\n", dec, oct, hex);
}

void exact_width_integers ()
{
    // Exact-width integers
    int8_t small = (1 << 7) - 1;
    uint8_t usmall = (1 << 8) - 1;
    int16_t medium = (1 << 15) - 1;
    uint16_t umedium = (1 << 16) - 1;
    int32_t large = (1 << 31) - 1;
    uint32_t ularge =  ((uint64_t)1 << 32) - 1; // Need the cast because the shift overflows a word
    int64_t huge = ((uint64_t)1 << 63) - 1;
    uint64_t uhuge = ((uint64_t)1 << 64) - 1;   // warning C4293

    printf("int8_t %d == %zu\n", small, sizeof small);
    printf("uint8_t %d == %zu\n", usmall, sizeof usmall);
    printf("int16_t %d == %zu\n", medium, sizeof medium);
    printf("uint16_t %d == %zu\n", umedium, sizeof umedium);
    printf("int32_t %d == %zu\n", large, sizeof large);
    printf("uint32_t %lu == %zu\n", ularge, sizeof ularge);
    printf("int64_t %lld == %zu\n", huge, sizeof huge);
    printf("uint64_t %llu == %zu\n", uhuge, sizeof uhuge);
}

void floating_point_types ()
{
    float f; // ~ 7 digits
    double d; // ~ 15 digits
    long double ld; // ~ 15 digits (typically)

    f = 12345.678;
    printf("float: %f\n", f);
    printf("float w/ 2 decimals: %.2f\n", f);

    double exp = 3e2; // 3*10^2
    printf("exp: %f\n", exp);
}

void literal_suffixes ()
{
    // Compiler treats values as ints by default.
    int i = 10;
    long l = 10L;
    unsigned long ul = 10UL;

    printf("%lu == %ld == %d\n", l, ul, i);
    assert(l == ul  && i == l);

    // Floating point literals are treated as a double
    float f = 1.23F;
    double d = 1.23;
    long double dd = 1.23L;

    // https://stackoverflow.com/questions/3988821/comparison-of-float-and-double-variables
    // Due to how floats/doubles are represented internally (base 2)
    // comparing them is tricky. By using epsilon, we basically say "close enough"
    float epsilon = 0.000000001;
    assert(abs(f - d) < epsilon && abs(d - dd) < epsilon);
}

void bool_type ()
{
    // Introduced in C99
    _Bool b = 0; // 1 (true), 0 (false)
    bool bb = true;
    assert(bb == 1 && b == 0);
}

int main (int argc, char *argv)
{
    primitive_types();
    exact_width_integers();
    floating_point_types();
    literal_suffixes();
    bool_type();


    return 0;
}