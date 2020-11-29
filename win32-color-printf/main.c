#include <stdio.h>
#include <windows.h>

// Inspired by: https://stackoverflow.com/questions/8765938/colorful-text-using-printf-in-c
#define WHITE_TEXT_BLACK_BACKGROUND FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN

/**
 * Note: Microsoft now recommends using the new virtual terminal sequences for any new
 * development. This example shows off the old way to set terminal colors via the Win32 API.
 * 
 * Read more on virtual terminal sequences here:
 * https://docs.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences
 */
int main(int argc, char *argv)
{
    HANDLE hConsole;
    int i;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE)
    {
        DWORD err = GetLastError();
        printf("Invalid console handle %i\n", err);
        return 1;
    }

    for (i = 1; i < 255; i++)
    {
        SetConsoleTextAttribute(hConsole, i);
        printf("%3d  %s\n", i, "In a hole in the ground, there lived a Hobbit.\n");
    }

    // getchar();
    SetConsoleTextAttribute(hConsole, WHITE_TEXT_BLACK_BACKGROUND);
    CloseHandle(hConsole); // Is this necessary?
    return 0;
}