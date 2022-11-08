#ifndef TYPE_H
#define TYPE_H

#include "config.h"

typedef enum CONNECTION{
    CONNECTION_SUCCESS=1,
    CONNECTION_FAILURE,
    CONNECTION_FULL,
    CONNECTION_DISCONNECTED
} CONNECTION;

typedef enum TYPE{
    TYPE_PLAYER=1,
    TYPE_MONSTER,
} TYPE;

typedef enum ACTION{
    ACTION_JOIN=1,
    ACTION_LEAVE,
    ACTION_SEND_MAP,
    ACTION_MOVE_UP,
    ACTION_MOVE_DOWN,
    ACTION_MOVE_LEFT,
    ACTION_MOVE_RIGHT,
} ACTION;

typedef enum ELEMENT{
    ELEMENT_PLAYER_1=1,
    ELEMENT_PLAYER_2,
    ELEMENT_PLAYER_3,
    ELEMENT_PLAYER_4,
    ELEMENT_MONSTER,
    ELEMENT_CAMPSITE,
    ELEMENT_BUSH,
    ELEMENT_SPACE,
    ELEMENT_WALL,
    ELEMENT_COIN_SMALL,
    ELEMENT_COIN_GIANT,
    ELEMENT_TREASURE,
    ELEMENT_DROPPED,
    ELEMENT_UNDEFINED
} ELEMENT;

struct PlayerData {
    int position_x;
    int position_y;

    int delay;
    int deaths;

    int score_pocket;
    int score_campsite;

    TYPE playerType;
    ELEMENT playerElement;

    pthread_t thr;
};

struct GameElement{
    ELEMENT type;
    int dropped_money; // only for ELEMENT_DROPPED;
};

struct GameManager{
    int board_height;
    int board_width;
    int max_clients;
    int active_clients;
    int active_monsters;

    int end_game;

    pthread_mutex_t mutex;

    struct GameElement** board;

    struct PlayerData* players[MAX_CLIENTS];
    struct PlayerData* monsters[MAX_CLIENTS];
};

// core server struct that manage game
struct ServerSocket {
    int fd;
    int port;
    int active_clients;
    int closed;
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
struct ClientHandlerThread {
    int socket;
    int port;
    pthread_t pth_player;
};

struct ClientHandlerStruct {
    struct ClientHandlerThread* client;
    struct GameManager* game;
};

struct KeyboardHandlerStruct {
    struct ServerSocket* server;
    struct GameManager* game;
};

#endif // TYPE_H