#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdlib.h>

// ============ NETWORK INCLUDE =============
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>

// ============ ERROR INCLUDE =============
#include "../error/error_wrapper.h"
#include "../error/message.h"

// ============ THREAD INCLUDE =============
#include <pthread.h>


// ============== NETWORK CONFIG =============
#define HOST "localhost"
#define PORT 8888

// ============== GAME CONFIG =============
#define MAX_CLIENTS 4

#endif // CONFIG_H