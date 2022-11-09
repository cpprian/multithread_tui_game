#include "../network/client_socket.h"

int main(int argc, char** argv) {
    struct ClientSocket* cs = createClient(HOST, PORT);
    clientSocketConnect(cs);

    char buffer[1] = {0};
    sendRequest(cs->fd, ACTION_JOIN, TYPE_PLAYER);
    recv(cs->fd, buffer, sizeof(buffer), 0);
    int conn = buffer[0];
    printf("Connection: %d", conn);
    if (conn == -45) {
        printf("Server is full\n");
        clientSocketClose(cs);
        return EXIT_FAILURE;
    } else if (conn == CONNECTION_FAILURE) {
        printf("Can't connect\n");
        clientSocketClose(cs);
        return EXIT_FAILURE;
    }

    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // TODO: render map thread

    int valid = 1;
    while(valid > 0) {
        unsigned char c = getchar();
        switch(c) {
            case 'w': {
                valid = sendRequest(cs->fd, ACTION_MOVE_UP, TYPE_PLAYER);
                break;
            }
            case 's': {
                valid = sendRequest(cs->fd, ACTION_MOVE_DOWN, TYPE_PLAYER);
                break;
            }
            case 'a': {
                valid = sendRequest(cs->fd, ACTION_MOVE_LEFT, TYPE_PLAYER);
                break;
            }
            case 'd': {
                valid = sendRequest(cs->fd, ACTION_MOVE_RIGHT, TYPE_PLAYER);
                break;
            }
            case 'q': {
                sendRequest(cs->fd, ACTION_LEAVE, TYPE_PLAYER);
                valid = 0;
                break;
            }
            default:
                break;
        }
    }
    
    clientSocketClose(cs);
    printf("Client closed\n");
    return EXIT_SUCCESS;
}