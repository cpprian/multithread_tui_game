#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#include "config.h"
#include "type.h"
#include "game_manager.h"
#include "server_util.h"
#include "client_socket.h"

// initialize server socket
struct ServerSocket* createServer(int port);

// create new socket and bind with server_socket struct
void serverSocketInit(struct ServerSocket* ss);

// create new sockaddr_in struct with given port
struct sockaddr_in createServerAddress(int port);

// delete server_socket struct
void freeServer(void* ss);

// clean up server socket
void serverSocketClose(void* ss);

// accept new client connection
void* serverSocketAccept(void* ss);

// listen for new client connections
void serverSocketListen(struct ServerSocket* serverSocket,struct GameManager* game);

void* clientHandler(void* args);  

int sendResponse(int socket, CONNECTION conn); 

#endif // SERVER_SOCKET_H