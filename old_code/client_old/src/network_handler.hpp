#ifndef NETWORK_HANDLER_HPP_
#define NETWORK_HANDLER_HPP_

#include <SDL_net.h>
#include <logger.hpp>

#define SETTING_SERVER_IP "127.0.0.1"
#define SETTING_SERVER_PORT 3333
#define SETTING_MAX_PACKET_SIZE 1024

class NetworkHandler
{
public:
    NetworkHandler() {
        if (SDLNet_Init() < 0) {
            Logger::error("Couldn't initialize net: {}", SDLNet_GetError());
            throw std::runtime_error(std::format("Couldn't initialize net: {}", SDL_GetError()));
        }
    };
    ~NetworkHandler() {
        SDLNet_UDP_Close(this->clientSocket);
        SDLNet_Quit();
    }
    bool connect()
    {
        if (SDLNet_ResolveHost(&this->serverIP, SETTING_SERVER_IP, SETTING_SERVER_PORT) == -1) {
            Logger::error("SDLNet_ResolveHost: {}", SDLNet_GetError());
            return false;
        }

        this->clientSocket = SDLNet_UDP_Open(0);
        if (!this->clientSocket) {
            Logger::error("SDLNet_UDP_Open: {}", SDLNet_GetError());
            return false;
        }     

        return true;
    }
    void send()
    {
        char buffer[SETTING_MAX_PACKET_SIZE];

        strcpy(buffer, "hello");

        UDPpacket *packet = SDLNet_AllocPacket(SETTING_MAX_PACKET_SIZE);
        packet->address = this->serverIP;
        packet->len = strlen(buffer) + 1;
        memcpy(packet->data, buffer, packet->len);

        Logger::debug(">> {}:{}: {}", SDLNet_ResolveIP(&packet->address), packet->address.port, (char *)packet->data);
        SDLNet_UDP_Send(clientSocket, -1, packet);

        SDLNet_FreePacket(packet);
    }
    void recv()
    {
        char buffer[SETTING_MAX_PACKET_SIZE];
        UDPpacket *packet = SDLNet_AllocPacket(SETTING_MAX_PACKET_SIZE);

        if (SDLNet_UDP_Recv(clientSocket, packet)) {
            Logger::debug("<< {}:{}: {}", SDLNet_ResolveIP(&packet->address), packet->address.port, (char *)packet->data);
        }

        SDLNet_FreePacket(packet);
    }
private:
    UDPsocket clientSocket;
    IPaddress serverIP;
};

#endif // NETWORK_HANDLER_HPP_
