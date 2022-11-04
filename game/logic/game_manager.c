#include "game_manager.h"

struct GameManager* createGameManager(int max_clients, int board_height, int board_width) {
    struct GameManager* game = (struct GameManager*)calloc(1, sizeof(struct GameManager));
    game->max_clients = max_clients;
    game->board_height = board_height;
    game->board_width = board_width;

    game->board = (struct GameElement**)calloc(game->board_height, sizeof(struct GameElement*));
    for (int i = 0; i < board_height; i++) {
        game->board[i] = (struct GameElement*)calloc(game->board_width, sizeof(struct GameElement));
    }
    return game;
}

void removeGameManager(struct GameManager* game) {
    for (int i = 0; i < game->board_height; i++) {
        free(game->board[i]);
    }
    free(game->board);
    free(game);
}

void addNewPlayer(struct GameManager* game, struct ClientHandlerThread* client, 
                    struct PlayerData* player, TYPE playerType, int* valid) 
{
    if ((playerType == TYPE_PLAYER && isFullPlayer(game)) ||
        (playerType == TYPE_MONSTER && isFullMonster(game))) 
    {
        *valid = 0;
        sendResponse(client->socket, CONNECTION_FULL);
        return;
    } 

    player = returnPlayer(game, playerType);
    if (player == NULL) {
        *valid = 0;
        sendResponse(client->socket, CONNECTION_FULL);
        return;
    }

    int positionX;
    int positionY;
    findEmptyPosition(game, &positionX, &positionY);

    player->position_x = positionX;
    player->position_y = positionY;
    player->delay = 0;
    player->deaths = 0;
    player->score_pocket = 0;
    player->score_campsite = 0;
    player->playerType = playerType;
    player->thr = client->pth_player;

    game->board[positionX][positionY].type = ELEMENT_PLAYER_1;

    sendResponse(client->socket, CONNECTION_SUCCESS);
}

void removePlayer(struct GameManager* game, struct ClientHandlerThread* client, TYPE playerType) {
    if (playerType == TYPE_PLAYER) {
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (game->players[i] != NULL && game->players[i]->thr == client->pth_player) {
                free(game->players[i]);
                game->players[i] = NULL;
                sendResponse(client->socket, CONNECTION_DISCONNECTED);
                return;
            }
        }
    } else if (playerType == TYPE_MONSTER) {
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (game->monsters[i] != NULL && game->monsters[i]->thr == client->pth_player) {
                free(game->monsters[i]);
                game->monsters[i] = NULL;
                sendResponse(client->socket, CONNECTION_DISCONNECTED);
                return;
            }
        }
    }
}

void sendMap(struct GameManager* game, struct ClientHandlerThread* client, struct PlayerData* player) { 
    
}

void movePlayerUp(struct ClientHandlerThread* client, struct PlayerData* player) {

}

void movePlayerDown(struct ClientHandlerThread* client, struct PlayerData* player) {

}

void movePlayerLeft(struct ClientHandlerThread* client, struct PlayerData* player) {

}

void movePlayerRight(struct ClientHandlerThread* client, struct PlayerData* player) {

}

struct PlayerData* returnPlayer(struct GameManager* game, TYPE playerType) {

    if (playerType == TYPE_PLAYER) {
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (game->players[i] == NULL) {
                game->players[i] = (struct PlayerData*)calloc(1, sizeof(struct PlayerData));
                return game->players[i];
            }
        }
    } else if (playerType == TYPE_MONSTER) {
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (game->monsters[i] == NULL) {
                game->monsters[i] = (struct PlayerData*)calloc(1, sizeof(struct PlayerData));
                return game->monsters[i];
            }
        }
    }

    return NULL;
}

int isFullPlayer(struct GameManager* game) {
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (game->players[i] == NULL) {
            return 1;
        }
    }

    return 0;
}

int isFullMonster(struct GameManager* game) {
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (game->monsters[i] == NULL) {
            return 1;
        }
    }

    return 0;
}