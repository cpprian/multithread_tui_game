#include "../network/server_socket.h"


int main(int argc, char** argv) {
    struct server_socket* ss = createServer(PORT);

    // TODO: load map


    // TODO: game thread loop


    // TODO: keyboard handler loop


    // listen for a new connection -> main thread
    serverSocketListen(ss);

    wait(NULL);

    serverSocketClose(ss);
    printf("Server closed\n");
    return EXIT_SUCCESS;
}