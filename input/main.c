#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

#ifdef __linux__
    #include <unistd.h>
#else
    #define access _access
#endif

// Required for Visual Studio to avoid compiler warnings
// Ideally, using the _s functions is better but not as portable
#define _CRT_SECURE_NO_DEPRECATE

void strip_endl(char *buffer) 
{
    if (buffer[strlen(buffer)-1] == '\n') 
    {
        buffer[strlen(buffer)-1] = '\0';
    }
}

#ifdef INPUT_KEYBOARD
// scanf is susceptible to overflow, so you shouldn't use it
// use fgets instead
void ex_scanf()
{
    int num;
    printf("Input num >>");
    scanf("%d", &num);
    printf("Num is %d; ok\n", num);
    getchar(); // consume the newline character in stdin
}

void ex_fgets()
{
    char color[20];
    printf("What is your favorite color?\n");
    fgets(color, 20, stdin);
    // fgets keeps the newline as part of the string
    strip_endl(color);
    printf("Color '%s' is your favorite?\n", color);
}
#endif

void ex_fprintf()
{
    errno = 0;
    char *fn = "test-file.txt";
    FILE *f = fopen(fn, "w+");
    if (f == NULL)
    {
        perror("File open failed");
        assert(false);
    }
    fprintf(f, "%s\n", "v1.0.0");
    fclose(f);
    if (access(fn, 0) == 0)
    {
        assert(true);
        remove(fn);
    }
    else
    {
        assert(false);
    }
}

void ex_fgets_f()
{
    errno = 0;
    char *fn = "test-file2.txt";
    const char *version = "v1.0.0";
    FILE *f = fopen(fn, "w+");
    if (f == NULL)
    {
        perror("File read failed");
        assert(false);
    }
    fprintf(f, "%s\n", version);
    fclose(f);

    char buffer[25];
    f = fopen(fn, "r");
    while (fgets(buffer, 25, f) != NULL)
    {
        assert(strcmp(buffer, version) == 0);
    }

    remove(fn);
}

int main(void)
{
    #ifdef INPUT_KEYBOARD
    ex_scanf();
    ex_fgets();
    #endif

    ex_fprintf();

    return 0;
}