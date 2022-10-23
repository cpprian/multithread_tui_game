#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#include "../config/config.h"

struct server_socket {
    int fd;
    int port;
    int active_clients;
    struct sockaddr_in addr;
};

struct sockaddr_in createServerAddress(int port);
struct server_socket* createServer(int port);
void freeServer(void* ss);

void serverSocketInit(struct server_socket* ss);
int serverSocketAccept(struct server_socket* ss);
void serverSocketClose(void* ss);

void serverSocketListen(void* ss);

#endif // SERVER_SOCKET_H