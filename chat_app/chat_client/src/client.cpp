// chat client
#include "../hdr/client_network.hpp"

int main (void) {

    ClientNetwork client_network;
    client_network.Connect("localhost", 2525);
    client_network.Run();

    return 0;
}
