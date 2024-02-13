#include "../../../include/models/server/TcpClientPlayer.h"

namespace TrucoGame {

    namespace Models {

        ErrorCode TcpClientPlayer::StartListening()
        {
            mListenThread = std::thread(&TcpClientPlayer::Listen, this);
            if (!mListenThread.joinable()) {
                return ErrorCode::ThreadError;
            }
            return Success;
        }

        void TcpClientPlayer::Listen()
        {
            char buffer[1024];
            int bytesRead;

            while ((bytesRead = recv(socket, buffer, sizeof(buffer), 0)) > 0) {
                std::string receivedData(buffer, bytesRead);
                try {
                    nlohmann::json receivedJson = nlohmann::json::parse(receivedData);
                    Packet receivedPacket(receivedJson);

                }
                catch (const std::exception& e) {
                    std::cerr << "Error parsing JSON: " << e.what() << std::endl;
                }
            }
        }

        ErrorCode TcpClientPlayer::Send(Packet* packet)
        {
            nlohmann::json jsonPacket;
            packet->ToJson(jsonPacket);
            std::string jsonString = jsonPacket.dump();
            jsonString += "\n";

            int result = send(socket, jsonString.c_str(), jsonString.size(), 0);
            if (result == SOCKET_ERROR) {
                std::cerr << "Error sending data: " << WSAGetLastError() << std::endl;
                return SocketError;
            }
            return Success;
        }

        Packet* TcpClientPlayer::WaitForPacket() {
            char buffer[1024];
            int bytesRead;
            
            while ((bytesRead = recv(socket, buffer, sizeof(buffer), 0)) > 0) {
                std::string receivedData(buffer, bytesRead);
                try {
                    nlohmann::json receivedJson = nlohmann::json::parse(receivedData);
                    Packet* receivedPacket = new Packet(receivedJson);

                    return receivedPacket;
                    
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