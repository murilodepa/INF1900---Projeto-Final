#include "../../../include/models/server/TcpServer.h"
#include <future>

#define MAX_CONNECTED_CLIENTS 1

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

        std::pair<Packet*, Packet*> TcpServer::WaitForTeamPacket(TcpClientPlayer* players[])
        {
            Packet* packetA;
            Packet* packetB;

            std::thread threadPlayerA([this, &packetA, players]() {
                packetA = players[0]->WaitForPacket();
            });

            std::thread threadPlayerB([this, &packetB, players]() {
                packetB = players[1]->WaitForPacket();
            });

            threadPlayerA.join();
            threadPlayerB.join();

            return { packetA, packetB };
        }

        std::vector<TcpClientPlayer*> TcpServer::AcceptPlayers(int numberOfClients)
        {
            if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
                closesocket(serverSocket);
                WSACleanup();
                return players;
            }

            int playerId = 0;
            std::cout << "[SERVER] Waiting for " << numberOfClients << " clients to connect\n";

            while (players.size() < numberOfClients) {
                TcpClientPlayer* client = new TcpClientPlayer(++playerId);
                client->socket = accept(
                    serverSocket,
                    (struct sockaddr*)&client->address,
                    &client->addressSize
                );

                if (client->socket == INVALID_SOCKET) {
                    closesocket(serverSocket);
                    WSACleanup();
                    break;
                }

                players.push_back(client);

                std::cout << "[SERVER] Client " << client->id << " connected\n";
            }

            return players;
        }

        ErrorCode TcpServer::StopAcceptingClients()
        {
            acceptThread.join();
            return Success;
        }

        ErrorCode TcpServer::SendToClients(std::vector<TcpClientPlayer*> players, Packet* packet)
        {
            for (int i = 0; i < players.size(); i++) {
                players[i]->Send(packet);
            }
            return Success;
        }

        ErrorCode TcpServer::Close()
        {
            for (int i = 0; i < players.size(); i++) {
                delete players[i];
            }
            return ErrorCode();
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