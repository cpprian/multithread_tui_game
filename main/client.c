#include "../network/client_socket.h"

int main(int argc, char** argv) {
    struct client_socket* cs = createClient(HOST, PORT);
    clientSocketConnect(cs);

    printf("socket id: %d", cs->fd);
    clientSocketClose(cs);
    return EXIT_SUCCESS;
}