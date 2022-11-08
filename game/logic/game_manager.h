#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "../../network/server_socket.h"
#include "../map/map_handler.h"

struct GameManager* createGameManager(int max_clients, int board_height, int board_width);
void removeGameManager(struct GameManager* game);

struct PlayerData* returnPlayer(struct GameManager* game, TYPE playerType);

// ============== CLIENT HANDLER API ===============
struct PlayerData* addNewPlayer(struct GameManager* game, struct ClientHandlerThread* client, TYPE playerType, int* valid);
void removePlayer(struct GameManager* game, struct ClientHandlerThread* client, TYPE playerType);

// TODO: implement
void sendMap(struct GameManager* game, struct ClientHandlerThread* client, struct PlayerData* player);

void movePlayer(struct GameManager* game, struct PlayerData* player, int positionX, int positionY);
ELEMENT returnPlayerCollision(struct GameManager* game, struct PlayerData* player);

#endif