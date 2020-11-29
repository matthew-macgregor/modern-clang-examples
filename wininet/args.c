#include <assert.h>
#include <stdio.h>
#include <wchar.h>
#include "args.h"

static wchar_t* GetUrlFile (wchar_t *url)
{
    wchar_t* needle = wcsrchr(url, '/');
    return ++needle;
}

static wchar_t* GetUrlExtension (wchar_t *url)
{
    wchar_t* needle = wcsrchr(url, '.');
    return ++needle;
}

static void DisplayUsage()
{
    LPCWSTR usage = L"Wininet Simple Downloader (dlz)\n"
    "Copyright \xa9 2020 Matthew MacGregor\n"
    "License: Mit License\n\n"
    "Usage: dlz [url] [options]\n"
    "    --out, -o      Output file name (optional)\n"
    "    --url, -u      Url to download\n"
    "    --verbose, -v  Enable verbose output\n"
    "    --ext, -e      Add the given extension to the downloaded file\n\n"
    "Examples: \n"
    "    dlz --url http://foo.com --out name.html\n"
    "    dlz --url http://foo.com\n"
    "    dlz http://foo.com/image.jpg\n"
    "    dlz http://foo.com/image.jpg --out myimage.jpg\n\n";
    wprintf(usage);
}

ArgsError ProcessArguments(const int argc, const wchar_t *argv[])
{
    if (argc ==  1)
    {
        DisplayUsage();
        wputs(L"Error: Not enough arguments");
        return ArgsError_NotEnoughArgs;
    }

    args.url[0] = 0;
    args.outputFilePath[0] = 0;

    int i;
    for (i = 0; i < argc; i++)
    {   
        const wchar_t *arg = argv[i];
        if(_STR_EQ(arg, L"--url") || _STR_EQ(arg, L"-u"))
        {
            arg = argv[++i];
            if (i >= argc) break;
            if (wcslen(arg) >= _countof(args.url)) 
            {
                wputs(L"ERROR: Url is too long");
                return ArgsError_UrlTooLong;
            }
            #pragma warning(disable:4996) // wcsncpy_s 
            wcsncpy(args.url, arg, _countof(args.url));
        }
        else if (_STR_EQ(arg, L"--out") || _STR_EQ(arg, L"-o"))
        {
            arg = argv[++i];
            if (i >= argc) break;
            if (wcslen(arg) >= _countof(args.outputFilePath)) 
            {
                wputs(L"ERROR: File path exceeds MAX_PATH");
                return ArgsError_PathTooLong;
            }
            wcsncpy(args.outputFilePath, arg, _countof(args.outputFilePath));
        }
        else if (_STR_EQ(arg, L"--ext") || _STR_EQ(arg, L"-e"))
        {
            arg = argv[++i];
            if (i >= argc) break;
            int count = _countof(args.extension);
            wchar_t* dotloc = wcsrchr(arg, L'.');

            if (dotloc == NULL || dotloc != arg)
            {
                count--; // Make room to add the dot
                wcscat(args.extension, L".");
            }

            if (wcslen(arg) >= count)
            {
                wputs(L"ERROR: Extension is too long");
                return ArgsError_ExtensionTooLong;
            }

            wcscat(args.extension, arg);
            assert(wcslen(args.extension) < _countof(args.extension));
        }
        else if (_STR_EQ(arg, L"--verbose") || _STR_EQ(arg, L"-v"))
        {
            args.verbose = TRUE;
        }
    }

    if (args.verbose)
    {
        wprintf(L"%s => %s\n", args.url, args.outputFilePath);
    }

    if (_EMPTY(args.url) && !_EMPTY(argv[1]))
    {
        if (args.verbose) puts("Using url as positional argument");
        wcsncpy(args.url, argv[1], _countof(args.url));
    }

    if (_EMPTY(args.url))
    {
        wputs(L"ERROR: Url is required");
        return ArgsError_NoUrl;
    }

    if (_EMPTY(args.outputFilePath))
    {
        wchar_t* urlFile = GetUrlFile(args.url);
        wcsncpy(args.outputFilePath, urlFile, _countof(args.outputFilePath));
    }

    if (_EMPTY(args.outputFilePath))
    {
        wputs(L"ERROR: Output file path is required");
        return ArgsError_NoFilePath;
    }

    wprintf(L"==> %s", GetUrlFile(args.url));
    return ArgsError_OK;
}