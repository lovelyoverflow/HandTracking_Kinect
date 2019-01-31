#ifndef NETWORKCONTROL_H
#define NETWORKCONTROL_H

//#include <winsock2.h>
#include <cstdlib>
#include <cstdio>
//#include <Ws2tcpip.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#pragma warning(disable:4996)

#define HTTP_REQUEST_PORT 80
#define SET_POS_PORT 6899

class NetworkControl
{
public:
    NetworkControl();
    int connectServer(int port);
    int doLogin(const char *id, const char *pw);
    int doRegister(const char *id, const char *pw);
    int setPOS(int x, int y);
    int cleanFD();
private:
    int fd;
};

#endif // NETWORKCONTROL_H
