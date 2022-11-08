#include "game_manager.h"

struct GameManager* createGameManager(int max_clients, int board_height, int board_width) {
    struct GameManager* game = (struct GameManager*)calloc(1, sizeof(struct GameManager));
    game->max_clients = max_clients;
    game->board_height = board_height;
    game->board_width = board_width;
    game->active_clients = 0;
    game->active_monsters = 0;
    game->end_game = 1;

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

struct PlayerData* addNewPlayer(struct GameManager* game, struct ClientHandlerThread* client, TYPE playerType, int* valid) 
{
    if ((playerType == TYPE_PLAYER && game->active_clients == 4) || 
        (playerType == TYPE_MONSTER && game->active_monsters == 4)) 
    {
        *valid = 0;
        if (playerType != TYPE_MONSTER) {
            sendResponse(client->socket, CONNECTION_FULL);
        }
        return NULL;
    } 

    struct PlayerData* player = returnPlayer(game, playerType);
    if (player == NULL) {
        *valid = 0;
        if (playerType == TYPE_MONSTER) {
            sendResponse(client->socket, CONNECTION_FULL);
        } 
        return NULL;
    }

    player->delay = 0;
    player->deaths = 0;
    player->score_pocket = 0;
    player->score_campsite = 0;
    player->thr = client->pth_player;

    if (playerType == TYPE_PLAYER) {
        pthread_mutex_lock(&game->mutex);
        game->active_clients++;
        pthread_mutex_unlock(&game->mutex);

        setPlayerCordinate(player);
        game->board[player->position_y][player->position_x].type = player->playerElement;
    } else {
        pthread_mutex_lock(&game->mutex);
        game->active_monsters++;
        pthread_mutex_unlock(&game->mutex);

        int positionX;
        int positionY;
        findEmptyPosition(game, &positionX, &positionY);
        player->position_x = positionX;
        player->position_y = positionY;
        player->playerElement = ELEMENT_MONSTER;
        game->board[player->position_y][player->position_x].type = ELEMENT_MONSTER;
        return player;
    }

    sendResponse(client->socket, CONNECTION_SUCCESS);
    return player;
}

struct PlayerData* returnPlayer(struct GameManager* game, TYPE playerType) {

    if (playerType == TYPE_PLAYER) {
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (game->players[i] == NULL) {
                game->players[i] = (struct PlayerData*)calloc(1, sizeof(struct PlayerData));
                game->players[i]->playerElement = (ELEMENT)(i+1);
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

void removePlayer(struct GameManager* game, struct ClientHandlerThread* client, TYPE playerType) {

    if (playerType == TYPE_PLAYER) {
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (game->players[i] != NULL && game->players[i]->thr == client->pth_player) {
                game->board[game->players[i]->position_y][game->players[i]->position_x].type = ELEMENT_SPACE;

                free(game->players[i]);
                game->players[i] = NULL;

                pthread_mutex_lock(&game->mutex);
                game->active_clients--;
                pthread_mutex_unlock(&game->mutex);
                sendResponse(client->socket, CONNECTION_DISCONNECTED);
                return;
            }
        }
    } else if (playerType == TYPE_MONSTER) {
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (game->monsters[i] != NULL && game->monsters[i]->thr == client->pth_player) {
                free(game->monsters[i]);
                game->monsters[i] = NULL;
                return;
            }
        }
    }
}

void sendMap(struct GameManager* game, struct ClientHandlerThread* client, struct PlayerData* player) { 
    
}

void movePlayer(struct GameManager* game, struct PlayerData* player, int positionX, int positionY) {
    if (game->board[player->position_y + positionY][player->position_x + positionX].type == ELEMENT_WALL) {
        return;
    }
    if (player->delay-- > 0) {
        return;
    }

    if (game->board[player->position_y][player->position_x].type == player->playerElement) {
        game->board[player->position_y][player->position_x].type = ELEMENT_SPACE;
    }

    player->position_x += positionX;
    player->position_y += positionY;
    game->board[player->position_y][player->position_x].type = returnPlayerCollision(game, player);
}

ELEMENT returnPlayerCollision(struct GameManager* game, struct PlayerData* player) {
    if (game->board[player->position_y][player->position_x].type == ELEMENT_BUSH) {
        player->delay = 1;
        return ELEMENT_BUSH;
    } else if (game->board[player->position_y][player->position_x].type == ELEMENT_CAMPSITE) {
        player->score_campsite += player->score_pocket;
        player->score_pocket = 0;
        return ELEMENT_CAMPSITE;
    } else if (game->board[player->position_y][player->position_x].type == ELEMENT_COIN_SMALL
                && player->playerElement != ELEMENT_MONSTER) {
        player->score_pocket += COIN_SMALL_VALUE;
    } else if (game->board[player->position_y][player->position_x].type == ELEMENT_COIN_GIANT
                && player->playerElement != ELEMENT_MONSTER) {
        player->score_pocket += COIN_GIANT_VALUE;
    } else if (game->board[player->position_y][player->position_x].type == ELEMENT_TREASURE
                && player->playerElement != ELEMENT_MONSTER) {
        player->score_pocket += TREASURE_VALUE;
    } else if (game->board[player->position_y][player->position_x].type == ELEMENT_DROPPED
                && player->playerElement != ELEMENT_MONSTER) {
        player->score_pocket += game->board[player->position_y][player->position_x].dropped_money;
        game->board[player->position_y][player->position_x].dropped_money = 0;
    } else if (game->board[player->position_y][player->position_x].type == ELEMENT_PLAYER_1 || 
                game->board[player->position_y][player->position_x].type == ELEMENT_PLAYER_2 || 
               game->board[player->position_y][player->position_x].type == ELEMENT_PLAYER_3 || 
               game->board[player->position_y][player->position_x].type == ELEMENT_PLAYER_4) 
    {
        int toSetNewCoordinates = game->board[player->position_y][player->position_x].type - 1;

        if (player->playerElement == ELEMENT_MONSTER) {
            game->players[toSetNewCoordinates]->deaths++;
            setPlayerCordinate(game->players[toSetNewCoordinates]);
        } else {
            int dropped = player->score_pocket + game->players[toSetNewCoordinates]->score_pocket;
            game->board[player->position_y][player->position_x].dropped_money = dropped;

            game->players[toSetNewCoordinates]->score_pocket = 0;
            player->score_pocket = 0;

            game->board[player->position_y][player->position_x].dropped_money = dropped;
            setPlayerCordinate(player);
            setPlayerCordinate(game->players[toSetNewCoordinates]);

            game->board[player->position_y][player->position_x].type = player->playerElement;
            game->board[game->players[toSetNewCoordinates]->position_y][game->players[toSetNewCoordinates]->position_x].type 
                                                            = game->players[toSetNewCoordinates]->playerElement;
            return ELEMENT_DROPPED;
        }
    }
    else if (game->board[player->position_y][player->position_x].type == ELEMENT_MONSTER) {
        if (player->playerElement == ELEMENT_MONSTER) {
            player->deaths++;
            return ELEMENT_SPACE;
        }
        player->deaths++;
        setPlayerCordinate(player);
        return ELEMENT_MONSTER;
    }

    return player->playerElement;
}

void createMonster(struct GameManager* game) {
    struct ClientHandlerThread* client = (struct ClientHandlerThread*)calloc(1, sizeof(struct ClientHandlerThread));
    struct ClientHandlerStruct* clientStruct = (struct ClientHandlerStruct*)calloc(1, sizeof(struct ClientHandlerStruct));
    clientStruct->game = game;
    clientStruct->client = client;

    pthread_create(&client->pth_player, NULL, monsterThread, (void*)clientStruct);
}

void* monsterThread(void* arg) {
    struct ClientHandlerStruct* clientStruct = (struct ClientHandlerStruct*)arg;
    struct GameManager* game = clientStruct->game;
    struct ClientHandlerThread* client = clientStruct->client;

    struct PlayerData* monster = addNewPlayer(game, client, TYPE_MONSTER, (int*)1);
    while (monster->deaths == 0 && game->end_game) {
        moveMonster(game, monster);
        usleep(100000);
    }

    removePlayer(game, client, TYPE_MONSTER);
    free(clientStruct);
    pthread_exit(NULL);
}

void moveMonster(struct GameManager* game, struct PlayerData* monster) {
    int position = rand() % 4;

    switch (position) {
        case 0:
            movePlayer(game, monster, 0, -1);
            break;
        case 1:
            movePlayer(game, monster, 0, 1);
            break;
        case 2:
            movePlayer(game, monster, -1, 0);
            break;
        case 3:
            movePlayer(game, monster, 1, 0);
            break;
    }
}