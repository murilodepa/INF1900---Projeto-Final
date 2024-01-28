#include "../../../include/models/server/Player.h"

namespace TrucoGame {

    namespace Models {

        ErrorCode Player::StartListening()
        {
            mListenThread = std::thread(&Player::Listen, this);
            if (!mListenThread.joinable()) {
                return ErrorCode::ThreadError;
            }
            return Success;
        }

        void Player::Listen()
        {
            char buffer[1024];
            int bytesRead;

            while ((bytesRead = recv(socket, buffer, sizeof(buffer), 0)) > 0) {
                std::string receivedData(buffer, bytesRead);
                try {
                    nlohmann::json receivedJson = nlohmann::json::parse(receivedData);
                    Packet receivedPacket(receivedJson);

                    std::cout << "Received packet type" << receivedPacket.packetType
                        << " from client " << id << std::endl;
                }
                catch (const std::exception& e) {
                    std::cerr << "Error parsing JSON: " << e.what() << std::endl;
                }
            }
        }

        ErrorCode Player::Send(Packet* packet)
        {
            nlohmann::json jsonPacket;
            packet->ToJson(jsonPacket);
            std::string jsonString = jsonPacket.dump();

            int result = send(socket, jsonString.c_str(), jsonString.size(), 0);
            if (result == SOCKET_ERROR) {
                std::cerr << "Error sending data: " << WSAGetLastError() << std::endl;
                return SocketError;
            }
            return Success;
        }

        Packet* Player::WaitForPacket() {
            char buffer[1024];
            int bytesRead;
            
            while ((bytesRead = recv(socket, buffer, sizeof(buffer), 0)) > 0) {
                std::string receivedData(buffer, bytesRead);
                try {
                    nlohmann::json receivedJson = nlohmann::json::parse(receivedData);
                    Packet receivedPacket(receivedJson);

                    std::cout << "Received packet type " << receivedPacket.packetType
                        << " from client " << id << std::endl;

                    switch (receivedPacket.packetType)
                    {
                    case PlayerCard:
                    {
                        CardPacket* cardPacket = new CardPacket(receivedPacket.payload);
                        return cardPacket;
                    }
                    case Truco:
                    {
                        TrucoPacket* truco = new TrucoPacket(receivedPacket.payload);
                        return truco;
                    }
                    default:
                        continue;
                    }
                    
                }
                catch (const std::exception& e) {
                    std::cerr << "Error parsing JSON: " << e.what() << std::endl;
                    return nullptr;
                }
            }
            return nullptr;
        }
    }
}