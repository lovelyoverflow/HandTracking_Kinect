#include "networkcontrol.h"
#include <winsock2.h>
#include <Ws2tcpip.h>

NetworkControl::NetworkControl()
{
    fd = connectServer(SET_POS_PORT);
}

int NetworkControl::connectServer(int port)
{
    struct sockaddr_in server_addr;
    WSADATA wsaData;

    int Result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (Result != NO_ERROR) {
        return -1;
    }

    SOCKET fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);


    if (fd == INVALID_SOCKET) {
        perror("SOCKET");
        return -1;
    }


    memset(&server_addr, 0x00, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("167.179.68.132");
    server_addr.sin_port = htons(port);

    if (connect(fd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        return -1;
    }

    return fd;
}

int NetworkControl::doLogin(const char *id, const char *pw)
{
    char *header = (char *)malloc(0x400);
    memset(header, 0, 0x400);
    snprintf(header, 0x400, "POST /login HTTP/1.1\r\n"\
        "Host: 108.61.127.142:8083\r\n" \
        "Accept: */*\r\n" \
        "User-Agent: c2w2m2\r\n" \
        "Content-Length: %d\r\n" \
        "Content-Type: application/x-www-form-urlencoded\r\n" \
        "\r\nid=%s&pw=%s\r\n", (7 + strlen(id) + strlen(pw)), id, pw);

    send(fd, header, strlen(header), 0);

    char *result = (char *)malloc(0x400);
    memset(result, 0, 0x400);
    recv(fd, result, 0x400, 0);
    char *ptr = strstr(result, "\r\n\r\n") + 4 + 9 + 1;
    int res_code = (int)ptr[0] - (int)'0';

    free(header);
    free(result);

    return res_code;
}

int NetworkControl::doRegister(const char *id, const char *pw)
{
    char *header = (char *)malloc(0x400);

    memset(header, 0, 0x400);

    snprintf(header, 0x400, "POST /register HTTP/1.1\r\n"\
        "Host: 108.61.127.142:8083\r\n" \
        "Accept: */*\r\n" \
        "User-Agent: c2w2m2\r\n" \
        "Content-Length: %d\r\n" \
        "Content-Type: application/x-www-form-urlencoded\r\n" \
        "\r\nid=%s&pw=%s\r\n", (7 + strlen(id) + strlen(pw)), id, pw);

    send(fd, header, strlen(header), 0);

    char *result = (char *)malloc(0x400);

    memset(result, 0, 0x400);

    recv(fd, result, 0x400, 0);
    char *ptr = strstr(result, "\r\n\r\n") + 4 + 9 + 1;
    int res_code = (int)ptr[0] - (int)'0';

    free(header);
    free(result);

    return res_code;
}

int NetworkControl::setPOS(int x, int y)
{
    char *header = (char *)malloc(0x20);

    memset(header, 0, 0x20);
    snprintf(header, 0x20, "%d %d;", x, y);

    send(fd, header, strlen(header), 0);
    free(header);

    return 0;
}

int NetworkControl::cleanFD()
{
    WSACleanup();
    closesocket(fd);
    return 0;
}
