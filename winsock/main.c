/*
* Example code using the Winsock Win32 Library.
*/
#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib") //Winsock Library

#define VERSION "1.0.0"

#define IP_ADDR_BUFFER_LEN 46
#define DEFAULT_BUFLEN 512
#define WHITE_TEXT_BLACK_BACKGROUND FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN

HANDLE hConsole = NULL;

/**
 * Win32 API method for setting the console color has been superseded by
 * https://docs.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences
 */
void set_console_color(UINT32 color)
{
    if (hConsole == NULL) hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE)
    {
        DWORD err = GetLastError();
        printf("Invalid console handle %i\n", err);
    }

    SetConsoleTextAttribute(hConsole, color);
}

void clear_console_color()
{
    SetConsoleTextAttribute(hConsole, WHITE_TEXT_BLACK_BACKGROUND);
    if (hConsole != NULL) CloseHandle(hConsole);
}

void print_usage()
{
    puts("Winsock Sample Program v" VERSION);
    set_console_color(FOREGROUND_GREEN);
    printf(
        
        "Usage:\n"
        "\twinsock.exe {hostname} {port}\n\n"
        "Example:\n\twinsock.exe google.com 80"
    );
    set_console_color(WHITE_TEXT_BLACK_BACKGROUND);
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {

        print_usage();
        set_console_color(FOREGROUND_RED);
        puts("\nERROR: Missing args {hostname} and {port}.\n");
        clear_console_color();
        return 1;
    }

    WSADATA wsaData;
    int result;

    struct addrinfo *addr_result = NULL, *ptr = NULL, hints;

    char *hostname = argv[1];
    char *port = argv[2];

    result = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (result != 0)
    {
        printf("WSAStartup failed with error code: %d\n", result);
        return result;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    result = getaddrinfo(hostname, port, &hints, &addr_result);
    if (result != 0)
    {
        printf("getaddrinfo failed: %d\n", result);
        WSACleanup();
        return result;
    }

    SOCKET ConnectSocket = INVALID_SOCKET;
    ptr = addr_result;
    ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    if (ConnectSocket == INVALID_SOCKET)
    {
        int err = WSAGetLastError();
        printf("Error at socket(): %ld\n", err);
        freeaddrinfo(addr_result);
        WSACleanup();
        return err;
    }

    result = connect(ConnectSocket, ptr->ai_addr, (int) ptr->ai_addrlen);
    if (result == SOCKET_ERROR)
    {
        closesocket(ConnectSocket);
        ConnectSocket = INVALID_SOCKET;
    }

    freeaddrinfo(addr_result);
    if (ConnectSocket == INVALID_SOCKET) 
    {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return 1;
    }

    const char *sendbuf = "GET / HTTP/1.1\r\nConnection: close\r\n\r\n";
    char recbuf[DEFAULT_BUFLEN];

    result = send(ConnectSocket, sendbuf, (int) strlen(sendbuf), 0);
    if (result == SOCKET_ERROR)
    {
        printf("Send failed: %d\b", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    result = shutdown(ConnectSocket, SD_SEND);
    if (result == SOCKET_ERROR)
    {
        printf("Shutdown socket failed: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    do {
        ZeroMemory(recbuf, DEFAULT_BUFLEN);
        result = recv(ConnectSocket, recbuf, DEFAULT_BUFLEN, 0);
        if (result > 0)
        {
            char buffer[DEFAULT_BUFLEN + 1];
            #pragma warning(disable:4996) 
            strncpy(buffer, recbuf, result);
            buffer[result] = '\0';
            printf("%s", buffer);
        }
        else if (result == 0)
        {
            printf("\nConnection is closed\n");
        }
        else
        {
            printf("Receive failed with error code: %d\n", WSAGetLastError());
        }
    } while (result > 0);


    result = shutdown(ConnectSocket, SD_SEND);
    if (result == SOCKET_ERROR)
    {
        printf("shutdown failed: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }
}