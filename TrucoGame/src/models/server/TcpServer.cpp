#include "../../../include/models/server/TcpServer.h"

#define MAX_CONNECTED_CLIENTS 2

namespace TrucoGame {

    namespace Models {
        /* public */
        ErrorCode TcpServer::Open(u_short port)
        {
            serverAddr.sin_family = AF_INET;
            serverAddr.sin_addr.s_addr = INADDR_ANY;
            serverAddr.sin_port = htons(port);

            ErrorCode result = InitializeWinSock();
            if (HAS_FAILED(result)) return result;

            result = CreateSocket(serverSocket);
            if (HAS_FAILED(result)) return result;

            result = BindSocket(serverSocket);
            if (HAS_FAILED(result)) return result;

            return Success;
        }

        ErrorCode TcpServer::StartAcceptingClients()
        {
            if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
                closesocket(serverSocket);
                WSACleanup();
                return SocketError;
            }
            acceptThread = std::thread(&TcpServer::AcceptClients, this);

            if (!acceptThread.joinable()) {
                return ErrorCode::ThreadError;
            }
            return ErrorCode::Success;
        }

        ErrorCode TcpServer::StopAcceptingClients()
        {
            acceptThread.join();
            return Success;
        }

        ErrorCode TcpServer::SendToAllClients(Packet packet)
        {
            for (int i = 0; i < clients.size(); i++) {
                clients[i]->Send(packet);
            }
            return Success;
        }

        ErrorCode TcpServer::SendToAllClientsBut(Packet packet, int clientId)
        {
            for (int i = 0; i < clients.size(); i++) {
                if (clients[i]->id == clientId) {
                    continue;
                }
                clients[i]->Send(packet);
            }
            return Success;
        }

        ErrorCode TcpServer::StartListeningClients()
        {
            //TODO SUBSCRIBE TO CLIENT
            for (int i = 0; i < clients.size(); i++) {
                std::cout << "Reading Socket of client " << clients[i]->id << std::endl;
                clients[i]->StartListening();
            }
            return Success;
        }

        ErrorCode TcpServer::Close()
        {
            for (int i = 0; i < clients.size(); i++) {
                delete clients[i];
            }
            return ErrorCode();
        }

        void TcpServer::AcceptClients()
        {
            int numberOfClients = 0;
            std::cout << "Waiting for " << MAX_CONNECTED_CLIENTS << " clients to connect" << std::endl;

            while (clients.size() < MAX_CONNECTED_CLIENTS) {
                Client* client = new Client(++numberOfClients);
                client->socket = accept(
                    serverSocket,
                    (struct sockaddr*)&client->address,
                    &client->addressSize
                );

                if (client->socket == INVALID_SOCKET) {
                    closesocket(serverSocket);
                    WSACleanup();
                    return;
                }

                clients.push_back(client);

                std::cout << "Client " << client->id << " connected\n";
            }
        }

        /* private */

        ErrorCode TcpServer::InitializeWinSock()
        {
            WSADATA wsaData;
            if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
                return ServerInitializationError;
            }
            return Success;
        }

        ErrorCode TcpServer::CreateSocket(SOCKET& newSocket)
        {
            newSocket = socket(AF_INET, SOCK_STREAM, 0);
            if (newSocket == INVALID_SOCKET) {
                WSACleanup();
                return SocketError;
            }
            return Success;
        }

        ErrorCode TcpServer::BindSocket(SOCKET& socket)
        {
            if (bind(socket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
                closesocket(socket);
                WSACleanup();
                return SocketError;
            }
            return Success;
        }

    }
}