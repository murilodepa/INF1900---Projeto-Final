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
                std::cerr << "[CLIENT] Error when trying to connect to server\n";
                closesocket(clientSocket);
                WSACleanup();
                return SocketError;
            }
            std::cout << "[CLIENT] Connected to server\n";
            return result;
        }

        ErrorCode TcpClient::Send(const char* message)
        {
            send(clientSocket, message, strlen(message), 0);
            char buffer[1024];
            size_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
            if (bytesRead > 0) {
                std::cout << "[CLIENT] Server Answer: " << std::string(buffer, bytesRead) << "\n";
            }
            return Success;
        }

        ErrorCode TcpClient::Send(const Packet* packet)
        {
            nlohmann::json jsonPacket;
            packet->ToJson(jsonPacket);
            std::string jsonString = jsonPacket.dump();

            int result = send(clientSocket, jsonString.c_str(), jsonString.size(), 0);
            if (result == SOCKET_ERROR) {
                std::cerr << "[CLIENT] Error sending data: " << WSAGetLastError() << std::endl;
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

        std::vector<std::string> customSplit(std::string str, char separator) {
            int startIndex = 0, endIndex = 0;
            std::vector<std::string> strings;
            for (int i = 0; i <= str.size(); i++) {

                // If we reached the end of the word or the end of the input.
                if (str[i] == separator || i == str.size()) {
                    endIndex = i;
                    std::string temp;
                    temp.append(str, startIndex, endIndex - startIndex);
                    strings.push_back(temp);
                    startIndex = endIndex + 1;
                }
            }
            return strings;
        }

        void TcpClient::Listen()
        {
            char buffer[1024];
            int bytesRead;

            while ((bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
                std::string receivedData(buffer, bytesRead);
                auto jsonStrings = customSplit(receivedData, '\n');
                for(int i = 0; i < jsonStrings.size()-1; i++)
                {
                    receivedData = jsonStrings[i];
                    try {
                        nlohmann::json receivedJson = nlohmann::json::parse(receivedData);
                        Packet receivedPacket(receivedJson);
                        
                        switch (receivedPacket.packetType)
                        {
                        case StartGame:
                        {
                            StartGamePacket startGamePacket(receivedPacket.payload);
                            std::cout << startGamePacket.playerId << " " << startGamePacket.teamId;
                            if (startGamePacketReceived)
                                startGamePacketReceived(startGamePacket);
                            break;
                        }
                        case StartRound:
                        {
                            StartRoundPacket startRoundPacket(receivedPacket.payload);
                            std::cout << "Hand [";
                            std::cout << startRoundPacket.handCards[0].getValue() << " " << startRoundPacket.handCards[0].getSuit();
                            std::cout << ":" << startRoundPacket.handCards[1].getValue() << " " << startRoundPacket.handCards[1].getSuit();
                            std::cout << ":" << startRoundPacket.handCards[2].getValue() << " " << startRoundPacket.handCards[2].getSuit() << "]" << std::endl;
                            std::cout << "Table Card: " << startRoundPacket.tableCard.getValue() << " " << startRoundPacket.tableCard.getSuit();
                            if (startRoundPacketReceived)
                                startRoundPacketReceived(startRoundPacket);
                            break;
                        }
                        case EndRound:
                        {
                            EndRoundPacket endRoundPacket(receivedPacket.payload);
                            break;
                        }
                        case EndTurn:
                        {
                            EndTurnPacket endTurn(receivedPacket.payload);
                            break;
                        }
                        case PlayerPlay:
                        {
                            PlayerPlayPacket playPacket(receivedPacket.payload);
                            if (playerPlayPacketReceived)
                                playerPlayPacketReceived(playPacket);
                            break;
                        }
                        case PlayerCard:
                        {
                            CardPacket cardPacket(receivedPacket.payload);
                            break;
                        }
                        case Truco:
                        {
                            TrucoPacket truco(receivedPacket.payload);
                            trucoPacketReceived(truco);
                            break;
                        }
                        default:
                            break;
                        }
                        std::cout << std::endl;
                    }
                    catch (const std::exception& e) {
                        std::cerr << "[CLIENT] Error parsing JSON: " << e.what() << std::endl;
                    }
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