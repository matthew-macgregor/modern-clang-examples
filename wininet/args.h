#include <windows.h>
#include "utils.h"

#ifndef ARGS_H
#define ARGS_H

typedef enum
{
    ArgsError_OK = 0,
    ArgsError_NoUrl,
    ArgsError_UrlTooLong,
    ArgsError_PathTooLong,
    ArgsError_ExtensionTooLong,
    ArgsError_NoFilePath,
    ArgsError_NotEnoughArgs
} ArgsError;

struct {
    unsigned verbose;
    WCHAR extension[EXTENSION_MAX_LENGTH];
    WCHAR url[URL_MAX_LENGTH];
    WCHAR outputFilePath[MAX_PATH];
} args;

ArgsError ProcessArguments(const int argc, const wchar_t* argv[]);

#endif