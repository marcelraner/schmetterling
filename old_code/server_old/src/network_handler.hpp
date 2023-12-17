#ifndef NETWORK_HANDLER_HPP_
#define NETWORK_HANDLER_HPP_

#include <SDL_net.h>

#include <logger.hpp>

#define SETTING_PORT 3333
#define SETTING_MAX_PACKET_SIZE 1024

struct ClientConnection
{
    IPaddress serverIP;
};

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
        SDLNet_Quit();
    }
    bool open()
    {
        if (SDLNet_ResolveHost(&this->serverIP, NULL, SETTING_PORT) == -1) {
            Logger::error("SDLNet_ResolveHost: {}", SDLNet_GetError());
            return false;
        }
        Logger::debug("server ip is: {}:{}", serverIP.host, serverIP.port);

        this->serverSocket = SDLNet_UDP_Open(SETTING_PORT);
        if(!this->serverSocket) {
            Logger::error("SDLNet_UDP_Open: {}", SDLNet_GetError());
            return false;
        }
        Logger::debug("listening on 0.0.0.0:{}", SETTING_PORT);

        

        return true;
    }

    void echo()
    {
        char buffer[SETTING_MAX_PACKET_SIZE];
        UDPpacket *packet = SDLNet_AllocPacket(SETTING_MAX_PACKET_SIZE);

        while (SDLNet_UDP_Recv(serverSocket, packet)) {
            Logger::debug("<< {}:{}: {}", SDLNet_ResolveIP(&packet->address), packet->address.port, (char *)packet->data);

            // Echo the message back to the client
            SDLNet_UDP_Send(serverSocket, -1, packet);
        }

        SDLNet_FreePacket(packet);
    }
private:
    UDPsocket serverSocket;
    IPaddress serverIP;
    std::vector<ClientConnection> client_connections;
};

#endif // NETWORK_HANDLER_HPP_
