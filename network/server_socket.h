#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#include "../config/config.h"
#include "client_socket.h"
#include "connection_handler.h"

// core server struct that manage game
struct server_socket {
    int fd;
    int port;
    int active_clients;
    struct sockaddr_in addr;

    // mutex
    pthread_mutex_t mtx;

    // game loop thread to handle game logic
    pthread_t pth_game;

    // keyboard handler thread to handle keyboard input from terminal
    pthread_t pth_keyboard;

    // thread to handle client connections
    pthread_t pth_listen;
};

// server handler to send and receive data from clients
struct client_handler_thread {
    int socket;
    int port;
    pthread_t pth_player;
};


// initialize server socket
struct server_socket* createServer(int port);

// create new socket and bind with server_socket struct
void serverSocketInit(struct server_socket* ss);

// create new sockaddr_in struct with given port
struct sockaddr_in createServerAddress(int port);

// delete server_socket struct
void freeServer(void* ss);

// clean up server socket
void serverSocketClose(void* ss);

// accept new client connection
void serverSocketAccept(void* ss);

// listen for new client connections
void serverSocketListen(struct server_socket* serverSocket);

#endif // SERVER_SOCKET_H