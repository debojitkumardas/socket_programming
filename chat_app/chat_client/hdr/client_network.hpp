#pragma once

#include <iostream>
#include <thread>
#include <SFML/Network.hpp>

#define logl(x) std::cout << x << "\n"

class ClientNetwork {
private:
    sf::TcpSocket socket_;
    sf::Packet last_packet_;

public:
    ClientNetwork();
    void Connect(const char* address, unsigned short port);
    void ReceivePackets(sf::TcpSocket* socket);
    void SendPackets(sf::Packet& packet);
    void Run();
};
