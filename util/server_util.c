#include "server_util.h"

void* serverKeyboardHandler(void* arg) {
    struct KeyboardHandlerStruct* keyboardHandlerStruct = (struct KeyboardHandlerStruct*)arg;
    struct ServerSocket* server = keyboardHandlerStruct->server;
    struct GameManager* game = keyboardHandlerStruct->game;

    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    int positionX = 0;
    int positionY = 0;
    while (game->end_game) {
        unsigned char c = getchar();
        findEmptyPosition(game, &positionX, &positionY);

        switch (c) {
            case 'Q':
            case 'q': {
                game->end_game = 0;
                server->closed = 0;

                // create temp connection with server
                struct ClientSocket* cs = createClient(HOST, PORT);

                // send request to server
                sendRequest(cs->fd, ACTION_LEAVE, TYPE_PLAYER);
                
                // remove temp connection
                clientSocketClose(cs);
                break;
            }
            case 'c': {
                game->board[positionY][positionX].type = ELEMENT_COIN_SMALL;
                break;
            }
            case 'C': {
                game->board[positionY][positionX].type = ELEMENT_COIN_GIANT;
                break;
            }
            case 'T': {
                game->board[positionY][positionX].type = ELEMENT_TREASURE;
                break;
            }
            case 'b':
            case 'B': {
                game->board[positionY][positionX].type = ELEMENT_MONSTER;
                break;
            }
            default:
                break;
        }
    }

    pthread_exit(NULL);
}