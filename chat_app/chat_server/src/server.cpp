// chat server
#include "../hdr/server_network.hpp"

int main (void) {

    ServerNetwork server_network(2525);
    server_network.Run();

    return 0;
}
