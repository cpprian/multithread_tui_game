#include "map_handler.h"

void findEmptyPosition(struct GameManager* game, int* positionX, int* positionY) {
    
    while (1) {
        *positionX = rand() % game->board_height;
        *positionY = rand() % game->board_width;
        if (game->board[*positionX][*positionY].type == ELEMENT_SPACE) {
            break;
        }
    }
}

void loadMap(struct GameManager* game, char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file");
        return;
    }

    char* value = (char*)calloc(1, sizeof(char));
    int positionX = 0;
    int positionY = 0;
    while ((*value = fgetc(file)) != EOF) {
        if (*value == '\n') {
            positionX = 0;
            positionY++;
            continue;
        }
        game->board[positionY][positionX++].type = returnElementType(value);
    }

    free(value);
    fclose(file);
}

ELEMENT returnElementType(char* value) {

    if (*value -' ' == 0) {
        return ELEMENT_SPACE;
    } else if (*value == '1') {
        return ELEMENT_PLAYER_1;
    } else if (*value == '2') {
        return ELEMENT_PLAYER_2;
    } else if (*value == '3') {
        return ELEMENT_PLAYER_3;
    } else if (*value == '4') {
        return ELEMENT_PLAYER_4;
    } else if (*value == '*') {
        return ELEMENT_MONSTER;
    } else if (*value == 'A') {
        return ELEMENT_CAMPSITE;
    } else if (*value - '#' == 0) {
        return ELEMENT_BUSH;
    } else if (*value == '?') {
        return ELEMENT_WALL;
    } else if (*value == 'c') {
        return ELEMENT_COIN_SMALL;
    } else if (*value == 'C') {
        return ELEMENT_COIN_GIANT;
    } else if (*value == 'T') {
        return ELEMENT_TREASURE;
    } else if (*value == 'D') {
        return ELEMENT_DROPPED;
    } 

    return ELEMENT_UNDEFINED;
}

const char* returnElementTypeChar(ELEMENT value) {

    switch(value) {
        case ELEMENT_PLAYER_1:
            return PLAYER_1;
        case ELEMENT_PLAYER_2:
            return PLAYER_2;
        case ELEMENT_PLAYER_3:  
            return PLAYER_3;
        case ELEMENT_PLAYER_4:
            return PLAYER_4;
        case ELEMENT_MONSTER:
            return MONSTER;
        case ELEMENT_CAMPSITE:
            return CAMPSITE;
        case ELEMENT_BUSH:
            return BUSH;
        case ELEMENT_SPACE:
            return SPACE;
        case ELEMENT_WALL:
            return WALL;
        case ELEMENT_COIN_SMALL:
            return COIN_SMALL;
        case ELEMENT_COIN_GIANT:
            return COIN_GIANT;
        case ELEMENT_TREASURE:
            return TREASURE;
        case ELEMENT_DROPPED:
            return DROPPED;
    }

    return " ";
}

void* printBoard(void* g) {
    struct GameManager* game = (struct GameManager*)g;

    setlocale(LC_ALL, "");
    initscr();
    start_color();
    init_pair(ELEMENT_PLAYER_1, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(ELEMENT_PLAYER_2, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(ELEMENT_PLAYER_3, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(ELEMENT_PLAYER_4, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(ELEMENT_MONSTER, COLOR_RED, COLOR_WHITE);
    init_pair(ELEMENT_CAMPSITE, COLOR_YELLOW, COLOR_GREEN);
    init_pair(ELEMENT_BUSH, COLOR_GREEN, COLOR_BLACK);
    init_pair(ELEMENT_SPACE, COLOR_BLACK, COLOR_BLACK);
    init_pair(ELEMENT_WALL, COLOR_WHITE, COLOR_WHITE);
    init_pair(ELEMENT_COIN_SMALL, COLOR_WHITE, COLOR_YELLOW);
    init_pair(ELEMENT_COIN_GIANT, COLOR_WHITE, COLOR_YELLOW);
    init_pair(ELEMENT_TREASURE, COLOR_WHITE, COLOR_YELLOW);
    init_pair(ELEMENT_DROPPED, COLOR_WHITE, COLOR_YELLOW);

    while (game != NULL) {
        // print map ncurses
        for (int y = 0; y < game->board_height; y++) {
            for (int x = 0; x < game->board_width; x++) {
                attron(COLOR_PAIR(game->board[y][x].type));
                mvprintw(y+5, x+5, "%s", returnElementTypeChar(game->board[y][x].type));
                attroff(COLOR_PAIR(game->board[y][x].type));
            }
        }

        // clear screen
        refresh();
        sleep(1);
        clear();
    }
    endwin();
    printf("Game closed\n");
    return NULL;
}