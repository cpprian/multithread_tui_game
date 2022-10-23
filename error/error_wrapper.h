#ifndef ERROR_WRAPPER_H
#define ERROR_WRAPPER_H

#include <stdio.h>
#include <stdlib.h>
#include "message.h"

void error_exit(int condition, const char* message, void (*errorHandler)(void*), void* arg);
void error_info(int condition, const char* message, void (*errorHandler)(void*), void* arg);

#endif // ERROR_WRAPPER_H