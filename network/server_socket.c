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

void serverSocketAccept(void* ss) {
    struct server_socket* serverSocket = (struct server_socket*)ss;
    struct client_handler_thread clientHandlerThread;
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLength = sizeof(clientAddress);

    int clientSocket = accept(serverSocket->fd, (struct sockaddr *) &clientAddress, &clientAddressLength);
    error_info(clientSocket < 0, E_ACCEPT_SOCKET, closeThread, NULL);

    if (clientSocket > 0) {
        pthread_mutex_lock(&serverSocket->mtx);
        serverSocket->active_clients++;

        clientHandlerThread.socket = clientSocket;
        clientHandlerThread.port = ntohs(clientAddress.sin_port);

        pthread_mutex_unlock(&serverSocket->mtx);
    }

    pthread_exit(&clientHandlerThread);
}

void serverSocketListen(struct server_socket* serverSocket) {
    while (serverSocket != NULL) {
        struct client_handler_thread* newPlayer = NULL;
        pthread_create(&serverSocket->pth_listen, NULL, serverSocketAccept, (void*)serverSocket);
        pthread_join(serverSocket->pth_listen, &newPlayer);

        if (newPlayer == NULL) {
            continue;
        }

        // after accept new client connection, create new thread to handle client
        if (serverSocket != NULL) {
            pthread_create(&newPlayer->pth_player, NULL, clientHandler, (void*)newPlayer);
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
    error_exit(ss == NULL, E_ALLOC, NULL, NULL);

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