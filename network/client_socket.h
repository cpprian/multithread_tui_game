#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

#include "../config/config.h"
#include "../config/type.h"

struct ClientSocket {
    int fd;
    struct hostent* server_host;
    struct sockaddr_in server_address;
};

struct ClientSocket* createClient(const char* server_ip, int server_port);
void freeClient(void* client_socket);

void clientSocketInit(struct ClientSocket* client_socket, const char* server_ip, int server_port);
void clientSocketConnect(struct ClientSocket* client_socket);
void clientSocketClose(void* client_socket);

int sendRequest(int socket, ACTION action, TYPE playerType);

#endif // CLIENT_SOCKET_H