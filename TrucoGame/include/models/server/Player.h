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

        class Player {
        public:
            int id;
            SOCKET socket;
            sockaddr_in address;
            int addressSize = sizeof(address);

            Player(int id) : id(id) {}
            ErrorCode StartListening();
            ErrorCode Send(Packet* packet);

            Packet* WaitForPacket();

            void Listen();
        private:
            std::thread mListenThread;
        };
    }
}
