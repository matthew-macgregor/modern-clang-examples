#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>

void while_loop()
{
    puts("while loop");
    int i = 0;
    while (i < 13)
    {
        i++;
    }
    assert(i == 13);
}

/**
 * The do-while loop is useful because it will always run through
 * the loop at least once.
 */
void do_while_loop()
{
    puts("do-while loop");
    int i = 0;
    do {
        i++;
    } while (i < 7);
    assert(i == 7);
}

void for_loop()
{
    puts("for loop");
    int i, sum = 0;
    for (i = 0; i < 10; i++)
    {
        sum += i;
    }
    assert(sum == 45);

    // Since C99
    for (int j = 0; j < 10; j++)
    {
        sum += j;
    }
    assert(sum == 90);

    int k, m;
    sum = 0;
    for (k = 0, m = 0; k < 10; k++, m--)
    {
        sum = k + m;
    }
    assert(sum == 0);

    // for (;;) { } // inifinite loop
}

void break_continue_goto()
{
    int i = 20;
    while (true)
    {
        i++;
        if (i > 30) break;
    }
    assert(i == 31);

    while (true)
    {
        i++;
        if (i < 40) continue;
        goto outta_here;
    }

    outta_here:
    assert(i == 40);
}

int main(int argc, char **argv)
{
    puts("Loops: C Programming Language");
    while_loop();
    do_while_loop();
    for_loop();
    break_continue_goto();
    return 0;
}