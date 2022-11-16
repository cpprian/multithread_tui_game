#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============ NETWORK INCLUDE =============
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>

// ============ ERROR INCLUDE =============
#include "error_wrapper.h"
#include "message.h"

// ============ THREAD INCLUDE =============
#include <pthread.h>
#include <sys/wait.h>
#include "thread_util.h"

// ============ NCURSES INCLUDE =============
#include <ncurses.h>
#include <wchar.h>
#include <locale.h>
#include <termios.h>

// ============== NETWORK CONFIG =============
#define HOST "localhost"
#define PORT 8888

// ============== GAME CONFIG =============
#define MAX_CLIENTS         4
#define MAX_PLAYER_VIEW     5

#define BOARD_HEIGHT        25
#define BOARD_WIDTH         52
#define SERVER_INFO_X       65
#define SERVER_INFO_Y       5

#define PLAYER_1        "\x31"
#define PLAYER_2        "\x32"
#define PLAYER_3        "\x33"
#define PLAYER_4        "\x34"
#define MONSTER         "\x2A"
#define CAMPSITE        "\x41"
#define BUSH            "\x23"
#define SPACE           "\x20"
#define WALL            "\xE2\x96\x88"
#define COIN_SMALL      "\x63"
#define COIN_GIANT      "\x43"
#define TREASURE        "\x54"
#define DROPPED         "\x44"
#define UNDEFINED       "\x3F"

#define COLOR_BLACK       0
#define COLOR_RED         1   
#define COLOR_GREEN       2
#define COLOR_YELLOW      3
#define COLOR_BLUE        4
#define COLOR_MAGENTA     5
#define COLOR_CYAN        6
#define COLOR_WHITE       7

#define PLAYER_1_X      37
#define PLAYER_1_Y      15
#define PLAYER_2_X      16
#define PLAYER_2_Y      21
#define PLAYER_3_X      4
#define PLAYER_3_Y      3
#define PLAYER_4_X      40
#define PLAYER_4_Y      5

#define COIN_GIANT_VALUE    10
#define COIN_SMALL_VALUE    1
#define TREASURE_VALUE      50

#endif // CONFIG_H