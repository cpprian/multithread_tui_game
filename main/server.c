#include "../network/server_socket.h"


int main(int argc, char** argv) {
    struct server_socket* ss = createServer(PORT);

    while(1) {
        serverSocketListen((void*)ss);
        
    }
    serverSocketClose(ss);
    return 0;
}