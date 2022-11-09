#include "server_socket.h"


void serverSocketInit(struct ServerSocket* ss) {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    error_exit(serverSocket < 0, E_OPEN_SOCKET, freeServer, (void*)ss);

    ss->fd = serverSocket;
    ss->closed = 1;

    int binding = bind(ss->fd, (struct sockaddr*) &(ss->addr), sizeof(ss->addr)) < 0;
    error_exit(binding, E_BIND_SOCKET, serverSocketClose, &ss);

    listen(ss->fd, 5);
}

void* serverSocketAccept(void* ss) {
    struct ServerSocket* serverSocket = (struct ServerSocket*)ss;
    struct ClientHandlerThread* clientHandlerThread = (struct ClientHandlerThread*)calloc(1, sizeof(struct ClientHandlerThread));
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLength = sizeof(clientAddress);

    int clientSocket = accept(serverSocket->fd, (struct sockaddr *)&clientAddress, &clientAddressLength);
    error_info(clientSocket < 0, E_ACCEPT_SOCKET, closeThread, NULL);

    if (clientSocket > 0) {
        pthread_mutex_lock(&serverSocket->mtx);
        serverSocket->active_clients++;

        clientHandlerThread->socket = clientSocket;
        clientHandlerThread->port = ntohs(clientAddress.sin_port);

        pthread_mutex_unlock(&serverSocket->mtx);
    }

    pthread_exit(clientHandlerThread);
}

void serverSocketListen(struct ServerSocket* serverSocket, struct GameManager* game) {
    while (serverSocket != NULL || game->end_game) {
        struct ClientHandlerThread* newPlayer = NULL;
        pthread_create(&serverSocket->pth_listen, NULL, serverSocketAccept, (void*)serverSocket);
        pthread_join(serverSocket->pth_listen, (void*)&newPlayer);
        
        if (newPlayer == NULL) {
            continue;
        }

        // after accept new client connection, create new thread to handle client
        if (serverSocket != NULL) {
            struct ClientHandlerStruct* args = (struct ClientHandlerStruct*)calloc(1, sizeof(struct ClientHandlerStruct));
            args->client = newPlayer;
            args->game = game;
            pthread_create(&newPlayer->pth_player, NULL, clientHandler, (void*)args);
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

struct ServerSocket* createServer(int port) {
    struct ServerSocket* ss = (struct ServerSocket*)calloc(1, sizeof(struct ServerSocket));
    error_exit(ss == NULL, E_ALLOC, NULL, NULL);

    ss->port = port;
    ss->active_clients = 0;
    ss->addr = createServerAddress(port);

    serverSocketInit(ss);
    return ss;
}

void freeServer(void* ss) {
    struct ServerSocket* serverSocket = (struct ServerSocket*)ss;
    free(serverSocket);
}

void serverSocketClose(void* ss) {
    struct ServerSocket* serverSocket = (struct ServerSocket*)ss;
    close(serverSocket->fd);
    freeServer(serverSocket);
}

void* clientHandler(void* args) {
    struct ClientHandlerStruct* clientHandlerStruct = (struct ClientHandlerStruct*)args;
    struct ClientHandlerThread* handleClient = clientHandlerStruct->client;
    struct GameManager* gameManager = clientHandlerStruct->game;

    struct PlayerData* player = NULL;
    char buffer[2] = {0};
    int valid = 1;

    while(valid) {
        int valRecv = recv(handleClient->socket, buffer, sizeof(buffer), 0);
        if (valRecv <= 0) {
            if (player != NULL) {
                removePlayer(gameManager, handleClient, player->playerType);
            }

            // kill client_handler thread
            closeThread();
        }

        ACTION action = buffer[0] - '0';
        TYPE playerType = buffer[1] - '0';

        // clear buffer
        memset(buffer, 0, sizeof(buffer));

        // choose action
        switch(action) {
            case ACTION_JOIN: {
                player = addNewPlayer(gameManager, handleClient, playerType, &valid);
                if (player == NULL) {
                    valid = 0;
                }
                break;
            }
            case ACTION_LEAVE: {
                removePlayer(gameManager, handleClient, playerType);
                valid = 0;
                break;
            }
            case ACTION_SEND_MAP: {
                sendMap(gameManager, handleClient, player);
                break;
            }
            case ACTION_MOVE_UP: {
                movePlayer(gameManager, player, 0, -1);
                break;
            }
            case ACTION_MOVE_DOWN: {
                movePlayer(gameManager, player, 0, 1);
                break;
            }
            case ACTION_MOVE_LEFT: {
                movePlayer(gameManager, player, -1, 0);
                break;
            }
            case ACTION_MOVE_RIGHT: {
                movePlayer(gameManager, player, 1, 0);
                break;
            }
            default:
                break;
        }
    }
    
    free(clientHandlerStruct);
    pthread_exit(NULL);
}

int sendResponse(int socket, CONNECTION conn) {
    char buffer[1] = {(char)conn};

    return send(socket, buffer, sizeof(buffer), 0);
}