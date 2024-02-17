#pragma once
#include <winsock2.h>
#include <thread>
#include <iostream>

#include "../ErrorCode.h"
#include "../packets/Packet.h"
#include "../packets/CardPacket.h"
#include "../packets/TrucoPacket.h"

#pragma comment(lib,"WS2_32")

namespace TrucoGame {

    namespace Models {

        class TcpClientPlayer {
        public:
            int id;
            SOCKET socket;
            sockaddr_in address;
            int addressSize = sizeof(address);

            TcpClientPlayer(int id) : id(id) {}
            virtual ErrorCode StartListening();
            virtual ErrorCode Send(Packet* packet);

            virtual Packet* WaitForPacket();

            virtual void Listen();
        private:
            std::thread mListenThread;
        };
    }
}
