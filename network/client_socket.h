#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

#include "../config/config.h"

struct client_socket {
    int fd;
    struct hostent* server_host;
    struct sockaddr_in server_address;
};

struct client_socket* createClient(const char* server_ip, int server_port);
void freeClient(void* client_socket);

void clientSocketInit(struct client_socket* client_socket, const char* server_ip, int server_port);
void clientSocketConnect(struct client_socket* client_socket);
void clientSocketClose(void* client_socket);

#endif // CLIENT_SOCKET_H