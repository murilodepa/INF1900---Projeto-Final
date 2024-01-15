#include "../../../include/models/client/TcpClient.h"

namespace TrucoGame {
    namespace Models {

        ErrorCode TcpClient::Connect(const char* ipAddress, u_short port)
        {
            ErrorCode result = InitializeWinSock();
            if (HAS_FAILED(result)) return result;

            result = CreateSocket(clientSocket);
            if (HAS_FAILED(result)) return result;

            serverAddr.sin_family = AF_INET;
            serverAddr.sin_addr.s_addr = inet_addr(ipAddress);
            serverAddr.sin_port = htons(port);

            if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
                std::cerr << "Error when trying to connect to server\n";
                closesocket(clientSocket);
                WSACleanup();
                return SocketError;
            }
            std::cout << "Connected to server\n";
            return result;
        }

        ErrorCode TcpClient::Send(const char* message)
        {
            send(clientSocket, message, strlen(message), 0);
            char buffer[1024];
            size_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
            if (bytesRead > 0) {
                std::cout << "Server Answer: " << std::string(buffer, bytesRead) << "\n";
            }
            return Success;
        }

        ErrorCode TcpClient::Send(const Packet& packet)
        {
            nlohmann::json jsonPacket;
            packet.ToJson(jsonPacket);
            std::string jsonString = jsonPacket.dump();

            int result = send(clientSocket, jsonString.c_str(), jsonString.size(), 0);
            if (result == SOCKET_ERROR) {
                std::cerr << "Error sending data: " << WSAGetLastError() << std::endl;
                return SocketError;
            }

            return ErrorCode();
        }

        ErrorCode TcpClient::StartListening()
        {
            mListenThread = std::thread(&TcpClient::Listen, this);
            if (!mListenThread.joinable()) {
                return ErrorCode::ThreadError;
            }
            return Success;
        }

        void TcpClient::Listen()
        {
            char buffer[1024];
            int bytesRead;
            Packet receivedPacket;

            while ((bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
                std::string receivedData(buffer, bytesRead);
                try {
                    nlohmann::json receivedJson = nlohmann::json::parse(receivedData);
                    Packet receivedPacket;
                    receivedPacket.FromJson(receivedJson);

                    std::cout << "Received packet type" << receivedPacket.packetType
                        << " from server" << std::endl;
                }
                catch (const std::exception& e) {
                    std::cerr << "Error parsing JSON: " << e.what() << std::endl;
                }
            }
        }

        /*private*/
        ErrorCode TcpClient::InitializeWinSock()
        {
            WSADATA wsaData;
            if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
                std::cerr << "Error while initializing Winsock\n";
                return ServerInitializationError;
            }
            return Success;
        }

        ErrorCode TcpClient::CreateSocket(SOCKET& newSocket)
        {
            newSocket = socket(AF_INET, SOCK_STREAM, 0);
            if (newSocket == INVALID_SOCKET) {
                std::cerr << "Error while creating socket\n";
                WSACleanup();
                return SocketError;
            }
            return Success;
        }
    }
}