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
#include "../error/error_wrapper.h"
#include "../error/message.h"

// ============ THREAD INCLUDE =============
#include <pthread.h>
#include <sys/wait.h>
#include "../util/thread_util.h"

// ============ NCURSES INCLUDE =============
#include <ncurses.h>
#include <wchar.h>
#include <locale.h>

// ============== NETWORK CONFIG =============
#define HOST "localhost"
#define PORT 8888

// ============== GAME CONFIG =============
#define MAX_CLIENTS     4

#define BOARD_HEIGHT    25
#define BOARD_WIDTH     52

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

#endif // CONFIG_H