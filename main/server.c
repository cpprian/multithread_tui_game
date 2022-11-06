#include "../network/server_socket.h"
#include "../game/map/map_handler.h"

int main(int argc, char** argv) {
    srand(time(NULL));  
    struct ServerSocket* ss = createServer(PORT);

    struct GameManager* game = createGameManager(MAX_CLIENTS, BOARD_HEIGHT, BOARD_WIDTH);
    loadMap(game, "./static/map.txt");

    // print board -> game thread
    pthread_create(&(ss->pth_game), NULL, printBoard, (void*)game);

    // TODO: keyboard handler loop


    // listen for a new connection -> main thread
    serverSocketListen(ss, game);

    removeGameManager(game);
    serverSocketClose(ss);
    return EXIT_SUCCESS;
}