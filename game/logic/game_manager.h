#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "../../network/server_socket.h"
#include "../player/player.h"
#include "../map/map_handler.h"

struct GameManager* createGameManager(int max_clients, int board_height, int board_width);
void removeGameManager(struct GameManager* game);

struct PlayerData* returnPlayer(struct GameManager* game, TYPE playerType);

// ============== CLIENT HANDLER API ===============
struct PlayerData* addNewPlayer(struct GameManager* game, struct ClientHandlerThread* client, TYPE playerType, int* valid);
void removePlayer(struct GameManager* game, struct ClientHandlerThread* client, TYPE playerType);

// TODO: implement
void sendMap(struct GameManager* game, struct ClientHandlerThread* client, struct PlayerData* player);

void movePlayerUp(struct GameManager* game, struct ClientHandlerThread* client, struct PlayerData* player);
void movePlayerDown(struct GameManager* game, struct ClientHandlerThread* client, struct PlayerData* player);
void movePlayerLeft(struct GameManager* game, struct ClientHandlerThread* client, struct PlayerData* player);
void movePlayerRight(struct GameManager* game, struct ClientHandlerThread* client, struct PlayerData* player);

#endif