#include "../hdr/server_network.hpp"

ServerNetwork::ServerNetwork(unsigned short port) : listen_port_(port) {
    logl("Chat Server Started");
}

void ServerNetwork::ConnectClients(std::vector<sf::TcpSocket*> client_list) {
    while (true) {
        logl("Listening connections");
        if (listener_.listen(listen_port_) == sf::TcpSocket::Done) {
            logl("Couldn't listen");
        }

        sf::TcpSocket* new_client = new sf::TcpSocket();

        if (listener_.accept(*new_client) == sf::Socket::Done) {
            new_client->setBlocking(false);
            client_list.push_back(new_client);
            logl("Added Client" << new_client->getRemoteAddress() << " : " << new_client->getRemotePort() << " on slot " << client_list.size());
        }
        else {
            logl("Couldn't add the new client");
        }
    }
}

void ServerNetwork::DisconnectClient(sf::TcpSocket* socket, size_t position) {
    logl("Removed Client" << socket->getRemoteAddress() << " : " << socket->getRemotePort() << " disconnected, removing ");

    delete socket;
    client_list_.erase(client_list_.begin() + position);
}

void ServerNetwork::ManagePackets() {
    while (true) {
        for (size_t iterator = 0; iterator < client_list_.size(); ++iterator) {
            sf::TcpSocket* client = client_list_[iterator];

            sf::Packet received_packet;
            if (client->receive(received_packet) == sf::Socket::Disconnected) {
                DisconnectClient(client, iterator);
                break;
            }

            if (received_packet.getDataSize() > 0) {
                std::string received_message;
                received_packet >> received_message;
                logl(received_message);
            }
        }
    }
}

void ServerNetwork::Run() {
    std::thread connection_thread(&ServerNetwork::ConnectClients, this, client_list_);

    ManagePackets();
}
