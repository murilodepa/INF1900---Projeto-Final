#pragma once
#include <winsock2.h>
#include <thread>
#include <iostream>

#include "../ErrorCode.h"
#include "../Packet.h"

#pragma comment(lib,"WS2_32")

namespace TrucoGame {

    namespace Models {

        class Client {
        public:
            int id;
            SOCKET socket;
            sockaddr_in address;
            int addressSize = sizeof(address);

            Client(int id) : id(id) {}
            ErrorCode StartListening();
            ErrorCode Send(Packet packet);

            void Listen();
        private:
            std::thread mListenThread;
        };
    }
}
