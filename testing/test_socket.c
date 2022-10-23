#include "../network/server_socket.h"
#include "../network/client_socket.h"
#include <criterion/criterion.h>

struct server_socket* ss;
struct client_socket* cs;

void setup(void) {
    ss = createServer(PORT);
    cs = createClient(HOST, PORT);
}

void teardown(void) {
    clientSocketClose(cs);
    serverSocketClose(ss);
}

Test(socket_connection, test_server_config_data, .init=setup, .fini=teardown) {
    cr_assert_not_null(ss);
    cr_assert_eq(ss->port, PORT);
    cr_assert_eq(ss->active_clients, 0);
    cr_assert_eq(ss->addr.sin_family, AF_INET);
    cr_assert_eq(ss->addr.sin_addr.s_addr, INADDR_ANY);
    cr_assert_eq(ss->addr.sin_port, htons(PORT));
}

Test(socket_connection, test_client_connection_config_data, .init=setup, .fini=teardown) {
    cr_assert_not_null(cs);
    cr_assert_not_null(cs->server_host);
    cr_assert_eq(cs->server_host->h_addrtype, AF_INET);
    cr_assert_eq(cs->server_host->h_length, 4);
    cr_assert_eq(cs->server_address.sin_family, AF_INET);
    cr_assert_eq(cs->server_address.sin_port, htons(PORT));
}