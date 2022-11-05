#ifndef MONSTER_H
#define MONSTER_H

#include "../../config/config.h"
#include "../../config/type.h"

// ==================== MONSTER MOVE API ====================
void moveMonsterUp(struct GameManager* game, struct ClientHandlerThread* client, struct PlayerData* player);
void moveMonsterDown(struct GameManager* game, struct ClientHandlerThread* client, struct PlayerData* player);
void moveMonsterLeft(struct GameManager* game, struct ClientHandlerThread* client, struct PlayerData* player);
void moveMonsterRight(struct GameManager* game, struct ClientHandlerThread* client, struct PlayerData* player);

#endif // MONSTER_H