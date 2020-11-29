#include "utils.h"

int wputs(const wchar_t *str)
{
    return wprintf(L"%s\n", str);
}

void GetErrorMessage(wchar_t buffer[ERROR_MSG_LENGTH], DWORD errorId)
{
    FormatMessageW(
        FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, errorId, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
        buffer, ERROR_MSG_LENGTH, NULL
    );
}