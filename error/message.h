#ifndef MESSAGE_H
#define MESSAGE_H

// ============== BASIC MESSAGES ==============
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0
#define E_ALLOC "Error allocating memory"
#define MSG_ERROR_INFO "Error info: "
#define MSG_ERROR_EXIT "Error exit: "

// ============== OPEN / CLOSE ==============
#define E_OPEN_SOCKET "Error opening socket"
#define E_CLOSE_SOCKET "Error closing socket"
#define E_BIND_SOCKET "Error binding socket"

// ============== CONNECTION ==============
#define E_LISTEN_SOCKET "Error listening socket"
#define E_ACCEPT_SOCKET "Error accepting socket"
#define E_CONNECT_SOCKET "Error connecting socket"
#define E_HOSTNAME "Error getting hostname"

// ============== SEND / RECEIVE ==============
#define E_SEND_SOCKET "Error sending socket"
#define E_RECV_SOCKET "Error receiving socket"

// =============== THREAD ===============
#define E_CREATE_THREAD "Error creating thread"
#define E_JOIN_THREAD "Error joining thread"

#endif