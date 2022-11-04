#include "client_socket.h"


void clientSocketInit(struct ClientSocket* client_socket, const char* server_ip, int server_port) {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    error_exit(clientSocket < 0, E_OPEN_SOCKET, freeClient, (void*)client_socket);

    client_socket->fd = clientSocket;

    struct hostent* serverHost = gethostbyname(server_ip);
    error_exit(serverHost == NULL, E_HOSTNAME, clientSocketClose, (void*)client_socket);

    client_socket->server_host = serverHost;

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(server_port);
    serverAddress.sin_addr = *((struct in_addr*)client_socket->server_host->h_addr);

    client_socket->server_address = serverAddress;
}

void clientSocketConnect(struct ClientSocket* client_socket) {
    int connection = connect(
        client_socket->fd, 
        (struct sockaddr*) &(client_socket->server_address), 
        sizeof(client_socket->server_address));
    error_exit(connection < 0, E_CONNECT_SOCKET, clientSocketClose, (void*)client_socket);
}

struct ClientSocket* createClient(const char* server_ip, int server_port) {
    struct ClientSocket* client_socket = (struct ClientSocket*)calloc(1, sizeof(struct ClientSocket));
    error_exit(client_socket == NULL, E_ALLOC, NULL, NULL);
    clientSocketInit(client_socket, server_ip, server_port);
    return client_socket;
}

void freeClient(void* cs) {
    struct ClientSocket* client_socket = (struct ClientSocket*)cs;
    free(client_socket);
}

void clientSocketClose(void* cs) {
    struct ClientSocket* client_socket = (struct ClientSocket*)cs;
    close(client_socket->fd);
    freeClient(cs);
}

int sendRequest(int socket, ACTION action, TYPE playerType) {
    char buffer[2] = {action + '0', playerType + '0'};

    return send(socket, buffer, sizeof(buffer), 0);
}