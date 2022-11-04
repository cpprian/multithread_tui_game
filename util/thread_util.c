#include "thread_util.h"

void closeThread() {
    pthread_exit(NULL);
}