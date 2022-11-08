#include "../network/server_socket.h"
#include "../game/map/map_handler.h"

int main(int argc, char** argv) {
    srand(time(NULL));  
    struct ServerSocket* ss = createServer(PORT);

    struct GameManager* game = createGameManager(MAX_CLIENTS, BOARD_HEIGHT, BOARD_WIDTH);
    loadMap(game, "./static/map.txt");

    // print board -> game thread
    pthread_create(&(ss->pth_game), NULL, printBoard, (void*)game);

    // keyboard input -> keyboard thread
    struct KeyboardHandlerStruct* keyboardHandlerStruct = (struct KeyboardHandlerStruct*)calloc(1, sizeof(struct KeyboardHandlerStruct));
    keyboardHandlerStruct->server = ss;
    keyboardHandlerStruct->game = game;
    pthread_create(&(ss->pth_keyboard), NULL, serverKeyboardHandler, (void*)keyboardHandlerStruct);

    // listen for a new connection -> main thread
    serverSocketListen(ss, game);

    // free the game manager
    removeGameManager(game);

    // close server socket
    serverSocketClose(ss);
    return EXIT_SUCCESS;
}