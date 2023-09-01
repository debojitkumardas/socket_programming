#include "../hdr/client_network.hpp"
#include <string>

ClientNetwork::ClientNetwork() {
    logl("Chat Slient Started");
}

void ClientNetwork::Connect(const char* address, unsigned short port) {
    if (socket_.connect(address, port) != sf::Socket::Done) {
        logl("Couldn't connect to the server");
    }
    else {
        logl("Connected to the server");
    }
}

void ClientNetwork::ReceivePackets(sf::TcpSocket* socket) {
    while (true) {
        if (socket->receive(last_packet_) == sf::Socket::Done) {
            std::string received_string;
            last_packet_ >> received_string;
            logl(received_string);
        }
    }
}

void ClientNetwork::SendPackets(sf::Packet& packet) {
    if (socket_.send(packet) != sf::Socket::Done) {
        logl("Couldn't send packet");
    }
}

void ClientNetwork::Run() {
    std::thread reception_thread(&ClientNetwork::ReceivePackets, this, &socket_);

    while (true) {
        std::string user_input;
        std::getline(std::cin, user_input);

        sf::Packet reply_packet;
        reply_packet << user_input;

        SendPackets(reply_packet);
    }
}
