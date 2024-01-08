#pragma once
#include <winsock2.h>
#include <cstring>
#include <iostream>
#include <thread>
#include <vector>

#include "../ErrorCode.h"
#include "../Packet.h"
#include <nlohmann/json.hpp>
#include "Client.h"

#pragma comment(lib,"WS2_32")
#pragma warning(disable:4996)

namespace TrucoGame {

    namespace Models {

        class TcpServer {
        private:
            SOCKET serverSocket;
            sockaddr_in serverAddr;
            std::thread acceptThread;
            bool running;

        public:
            std::vector<Client*> clients;
            std::vector<std::thread> clientsThreads;

            ErrorCode Open(u_short);
            ErrorCode StartAcceptingClients();
            ErrorCode StartListeningClients();
            ErrorCode StopAcceptingClients();
            ErrorCode SendToAllClients(Packet packet);
            ErrorCode SendToAllClientsBut(Packet packet, int clientId);

            //ErrorCode SendMessageToClient(Client*);
            //ErrorCode SendMessageToClient(int id);


            ErrorCode Close();
            void AcceptClients();

        private:
            ErrorCode InitializeWinSock();
            ErrorCode CreateSocket(SOCKET& socket);
            ErrorCode BindSocket(SOCKET& socket);
        };
    }
}