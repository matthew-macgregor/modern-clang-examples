#include <windows.h>
#include <wchar.h>

#ifndef UTILS_H
#define UTILS_H

#define URL_MAX_LENGTH 4096
#define ERROR_MSG_LENGTH 256
#define EXTENSION_MAX_LENGTH 12

// Helpful Macros
#define _STR_EQ(A, B) wcscmp(A, B) == 0
#define _EMPTY(A) wcscmp(A, L"") == 0

wchar_t errorMsgBuffer[ERROR_MSG_LENGTH];
void GetErrorMessage(wchar_t buffer[ERROR_MSG_LENGTH], DWORD errorId);

int wputs(const wchar_t *str);

#endif