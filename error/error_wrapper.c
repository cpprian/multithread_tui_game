#include "error_wrapper.h"


void error_exit(int condition, const char* message, 
        void (*errorHandler)(void*), void* arg) 
{
    char* err;
    if (condition) {
        if (errorHandler != NULL) {
            errorHandler(arg);
        }

        char* err;
        sprintf(err, "%s%s", MSG_ERROR_EXIT, message);
        exit(EXIT_FAILURE);
    }
}

void error_info(int condition, const char* message,
                void (*errorHandler)(void*), void* arg)
{
    char* err;
    if (condition) {
        if (errorHandler != NULL) {
            errorHandler(arg);
        }
        sprintf(err, "%s%s", MSG_ERROR_EXIT, message);
    }
}