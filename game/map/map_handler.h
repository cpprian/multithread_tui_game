#ifndef MAP_HANDLER_H
#define MAP_LOADER_H

#include "game_manager.h"
#include "ncurses.h"

void findEmptyPosition(struct GameManager* game, int* positionX, int* positionY);
void setPlayerCordinate(struct PlayerData* player);

void loadMap(struct GameManager* game, char* filename);
void* printBoard(void* game);
void* printClientBoard(void* clientData);
ELEMENT returnElementType(char* value);
const char* returnElementTypeChar(ELEMENT value);

#endif // MAP_LOADER_H