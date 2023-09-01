#pragma once

#include <iostream>
#include <thread>
#include <vector>
#include <SFML/Network.hpp>

#define logl(x) std::cout << x << "\n"

class ServerNetwork {
private:
    sf::TcpListener listener_;
    std::vector<sf::TcpSocket*> client_list_;
    unsigned short listen_port_;

public:
    ServerNetwork(unsigned short port);
    void ConnectClients(std::vector<sf::TcpSocket*> client_list);
    void DisconnectClient(sf::TcpSocket* socket, size_t position);
    void ManagePackets();
    void Run();
};
