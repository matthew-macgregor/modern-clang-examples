#define UNICODE 1
#define _UNICODE 1

#include <stdio.h>
#include <windows.h>
#include <wininet.h>
#include <wchar.h>
#include <fcntl.h>
#include <io.h>

#include "utils.h"
#include "args.h"

#pragma comment(lib, "wininet.lib") // Wininet Library

int wmain(const int argc, const wchar_t *argv[], wchar_t *envp[])
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    ArgsError argsError = ProcessArguments(argc, argv);
    if (argsError != ArgsError_OK)
    {
        return argsError;
    }
    
    if (args.verbose)
    {
        wprintf(L"URL: %s\n", args.url);
        wprintf(L"Path: %s\n", args.outputFilePath);
    }

    LPCWSTR userAgent = L"Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/51.0.2704.103 Safari/537.36";
    // InternetOpen gets the internal data structures set up correctly.
    // https://docs.microsoft.com/en-us/windows/win32/api/wininet/nf-wininet-internetopenw
    HINTERNET hInternet = InternetOpen(userAgent, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hInternet == NULL) 
    {
        GetErrorMessage(errorMsgBuffer, GetLastError());
        wprintf(L"InternetOpen failed with error: %s\n", errorMsgBuffer);
        goto error_CloseInternet;
    }

    LPCWSTR headers = 
        // L"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/jpg,image/png,*/*;q=0.8\r\n"
        L"Accept-Encoding: gzip, deflate, br\r\n"
        L"Accept-Language: en-US,en;q=0.9\r\n";

    BOOL b = TRUE;
    InternetSetOption(hInternet, INTERNET_OPTION_HTTP_DECODING, &b, sizeof(b));

    FILE *outfile = NULL;
    HINTERNET hUrlFile = InternetOpenUrl(hInternet, args.url, headers, (DWORD) wcslen(headers), 0, 0);
    if (hUrlFile == NULL) 
    {
        DWORD lastError = GetLastError();
        GetErrorMessage(errorMsgBuffer, lastError);
        wprintf(L"InternetOpenUrl failed with error: %d %s\n", lastError, errorMsgBuffer);
        goto error_CloseUrlFile;
    }

    #pragma warning(disable:4996) // fopen_s
    wchar_t filePath[_countof(args.outputFilePath) + _countof(args.extension)];
    wcscpy(filePath, args.outputFilePath);
    wcsncat(filePath, args.extension, _countof(args.extension));
    outfile = _wfopen(filePath, L"wb");
    if (outfile == NULL)
    {
        int lastError = GetLastError();
        GetErrorMessage(errorMsgBuffer, lastError);
        wprintf(L"Opening outfile failed with error: %d %s\n", lastError, errorMsgBuffer);
        goto error_CloseUrlFile;
    }

    DWORD bytes_read;
    char buffer[1024];
    size_t bufferSize = sizeof(buffer);
    int finished = 0;
    while (!finished) 
    {
        if (InternetReadFile(hUrlFile, buffer, (DWORD) bufferSize, &bytes_read)) 
        {
            if (bytes_read > 0) 
            {
                fwrite(buffer, bytes_read, 1, outfile);
            } else {
                if (args.verbose) wprintf(L"Downloaded %s\n", args.url);
                finished = 1;
            }
        }
        else 
        {
            wprintf(L"InternetReadFile failed\n");
            finished = 1;
        }
    }

    return 0;

    error_CloseUrlFile:
    InternetCloseHandle(hUrlFile);

    error_CloseInternet:
    InternetCloseHandle(hInternet);

    if (outfile != NULL) fclose(outfile);
   
    return 42;
}