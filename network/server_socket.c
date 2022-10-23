#include "server_socket.h"
#include "client_socket.h"


void serverSocketInit(struct server_socket* ss) {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    error_exit(serverSocket < 0, E_OPEN_SOCKET, freeServer, (void*)ss);

    ss->fd = serverSocket;

    int binding = bind(ss->fd, (struct sockaddr*) &(ss->addr), sizeof(ss->addr)) < 0;
    error_exit(binding, E_BIND_SOCKET, serverSocketClose, &ss);

    listen(ss->fd, 5);
}

int serverSocketAccept(struct server_socket* ss) {
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLength = sizeof(clientAddress);

    int clientSocket = accept(ss->fd, (struct sockaddr *) &clientAddress, &clientAddressLength);
    error_info(clientSocket < 0, E_ACCEPT_SOCKET, NULL, NULL);

    if (clientSocket > 0) {
        ss->active_clients++;
    }

    return clientSocket;
}

void serverSocketListen(void* ss) {
    struct server_socket* serverSocket = (struct server_socket*) ss;


    // TODO: create threads
    // TODO: clean up threads
    // TODO: load map on server
    while (serverSocket->active_clients < MAX_CLIENTS) {
        int clientSocket = serverSocketAccept(serverSocket);
        if (clientSocket > 0) {
            struct client_socket* clientSocketStruct = createClient(HOST, PORT);
            printf("Client connected: %d\n", clientSocketStruct->fd);
        }
    }
}

struct sockaddr_in createServerAddress(int port) {
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    return serverAddress;
}

struct server_socket* createServer(int port) {
    struct server_socket* ss = (struct server_socket*)calloc(1, sizeof(struct server_socket));
    ss->port = port;
    ss->active_clients = 0;
    ss->addr = createServerAddress(port);
    serverSocketInit(ss);
    return ss;
}

void freeServer(void* ss) {
    struct server_socket* serverSocket = (struct server_socket*)ss;
    free(serverSocket);
}

void serverSocketClose(void* ss) {
    struct server_socket* serverSocket = (struct server_socket*)ss;
    close(serverSocket->fd);
    freeServer(serverSocket);
}