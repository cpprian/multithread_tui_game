#include "error_wrapper.h"


void error_exit(int condition, const char* message, 
        void (*errorHandler)(void*), void* arg) 
{
    if (condition) {
        if (errorHandler != NULL) {
            errorHandler(arg);
        }

        if (message != NULL) {
            printf("%s\n", message);
        }
        exit(EXIT_FAILURE);
    }
}

void error_info(int condition, const char* message,
                void (*errorHandler)(void*), void* arg)
{
    if (condition) {
        if (errorHandler != NULL) {
            errorHandler(arg);
        }

        if (message != NULL) {
            printf("%s\n", message);
        }
    }
}