#include "map_handler.h"

void findEmptyPosition(struct GameManager* game, int* positionX, int* positionY) {
    
    while (1) {
        *positionX = rand() % game->board_width;
        *positionY = rand() % game->board_height;
        if (game->board[*positionY][*positionX].type == ELEMENT_SPACE) {
            break;
        }
    }
}

void setPlayerCordinate(struct PlayerData* player) {
    if (player->playerElement == ELEMENT_PLAYER_1) {
        player->position_x = PLAYER_1_X;
        player->position_y = PLAYER_1_Y;
    } else if (player->playerElement == ELEMENT_PLAYER_2) {
        player->position_x = PLAYER_2_X;
        player->position_y = PLAYER_2_Y;
    } else if (player->playerElement == ELEMENT_PLAYER_3) {
        player->position_x = PLAYER_3_X;
        player->position_y = PLAYER_3_Y;
    } else {
        player->position_x = PLAYER_4_X;
        player->position_y = PLAYER_4_Y;
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
    init_pair(ELEMENT_MONSTER, COLOR_RED, COLOR_BLACK);
    init_pair(ELEMENT_CAMPSITE, COLOR_WHITE, COLOR_BLUE);
    init_pair(ELEMENT_BUSH, COLOR_GREEN, COLOR_BLACK);
    init_pair(ELEMENT_SPACE, COLOR_BLACK, COLOR_BLACK);
    init_pair(ELEMENT_WALL, COLOR_WHITE, COLOR_WHITE);
    init_pair(ELEMENT_COIN_SMALL, COLOR_WHITE, COLOR_YELLOW);
    init_pair(ELEMENT_COIN_GIANT, COLOR_WHITE, COLOR_YELLOW);
    init_pair(ELEMENT_TREASURE, COLOR_WHITE, COLOR_YELLOW);
    init_pair(ELEMENT_DROPPED, COLOR_WHITE, COLOR_YELLOW);


    long round = 0;
    while (game->end_game) {
        // print map ncurses
        for (int y = 0; y < game->board_height; y++) {
            for (int x = 0; x < game->board_width; x++) {
                attron(COLOR_PAIR(game->board[y][x].type));
                attron(A_BOLD);
                mvprintw(y+5, x+5, "%s", returnElementTypeChar(game->board[y][x].type));
                attroff(A_BOLD);
                attroff(COLOR_PAIR(game->board[y][x].type));

                if (game->board[y][x].type == ELEMENT_CAMPSITE) {
                    attron(COLOR_PAIR(ELEMENT_PLAYER_1));
                    attron(A_BOLD);
                    mvprintw(SERVER_INFO_Y+2, SERVER_INFO_X, "Campsite X/Y: %d/%d", x, y);
                    attroff(A_BOLD);
                    attroff(COLOR_PAIR(ELEMENT_PLAYER_1));
                }
            }
        }

        // print Server's pid
        attron(COLOR_PAIR(ELEMENT_PLAYER_1));
        attron(A_BOLD);
        mvprintw(SERVER_INFO_Y, SERVER_INFO_X, "Server's pid: %d", getpid());
        mvprintw(SERVER_INFO_Y+1, SERVER_INFO_X, "Round number: %ld", round++);
        mvprintw(SERVER_INFO_Y+5, SERVER_INFO_X, "Parameter:");
        mvprintw(SERVER_INFO_Y+6, SERVER_INFO_X, "PID");
        mvprintw(SERVER_INFO_Y+7, SERVER_INFO_X, "Curr X/Y");
        mvprintw(SERVER_INFO_Y+8, SERVER_INFO_X, "Deaths");
        mvprintw(SERVER_INFO_Y+9, SERVER_INFO_X, "Coins");
        mvprintw(SERVER_INFO_Y+10, SERVER_INFO_X+2, "carried");
        mvprintw(SERVER_INFO_Y+11, SERVER_INFO_X+2, "brought");
        attroff(A_BOLD);
        attroff(COLOR_PAIR(ELEMENT_PLAYER_1));


        // print players info   
        for (int i = 0; i < game->max_clients; i++) {
            if (game->players[i] != NULL) {
                attron(A_BOLD);
                mvprintw(SERVER_INFO_Y+5, SERVER_INFO_X+12*(i+1), "Player %d:", i+1);
                mvprintw(SERVER_INFO_Y+6, SERVER_INFO_X+12*(i+1), "%d/%d", game->players[i]->position_x, game->players[i]->position_y);
                mvprintw(SERVER_INFO_Y+7, SERVER_INFO_X+12*(i+1), "%d", game->players[i]->deaths);
                mvprintw(SERVER_INFO_Y+9, SERVER_INFO_X+12*(i+1), "%d", game->players[i]->score_pocket);
                mvprintw(SERVER_INFO_Y+10, SERVER_INFO_X+12*(i+1), "%d", game->players[i]->score_campsite);
                attroff(A_BOLD);
            } else {
                attron(A_BOLD);
                mvprintw(SERVER_INFO_Y+5, SERVER_INFO_X+12*(i+1), "Player %d:", i+1);
                mvprintw(SERVER_INFO_Y+6, SERVER_INFO_X+12*(i+1), "--/--");
                mvprintw(SERVER_INFO_Y+7, SERVER_INFO_X+12*(i+1), "-");
                mvprintw(SERVER_INFO_Y+9, SERVER_INFO_X+12*(i+1), "0");
                mvprintw(SERVER_INFO_Y+10, SERVER_INFO_X+12*(i+1), "0");
                attroff(A_BOLD);
            }
        }

        // clear screen
        refresh();
        usleep(50000);
        clear();
    }
    endwin();
    return NULL;
}