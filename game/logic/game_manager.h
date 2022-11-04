#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "../../network/server_socket.h"
#include "../player/player.h"
#include "../map/map_handler.h"

struct GameManager* createGameManager(int max_clients, int board_height, int board_width);
void removeGameManager(struct GameManager* game);

struct PlayerData* returnPlayer(struct GameManager* game, TYPE playerType);
int isFullPlayer(struct GameManager* game);
int isFullMonster(struct GameManager* game);

// ============== CLIENT HANDLER API ===============
void addNewPlayer(struct GameManager* game, struct ClientHandlerThread* client, struct PlayerData* player, 
                    TYPE playerType, int* valid);
void removePlayer(struct GameManager* game, struct ClientHandlerThread* client, TYPE playerType);

// TODO: implement
void sendMap(struct GameManager* game, struct ClientHandlerThread* client, struct PlayerData* player);

// TODO: implement
void movePlayerUp(struct ClientHandlerThread* client, struct PlayerData* player);
void movePlayerDown(struct ClientHandlerThread* client, struct PlayerData* player);
void movePlayerLeft(struct ClientHandlerThread* client, struct PlayerData* player);
void movePlayerRight(struct ClientHandlerThread* client, struct PlayerData* player);

#endif