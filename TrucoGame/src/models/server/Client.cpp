#include "../../../include/models/server/Client.h"

namespace TrucoGame {

    namespace Models {

        ErrorCode Client::StartListening()
        {
            mListenThread = std::thread(&Client::Listen, this);
            if (!mListenThread.joinable()) {
                return ErrorCode::ThreadError;
            }
            return Success;
        }

        void Client::Listen()
        {
            char buffer[1024];
            int bytesRead;
            Packet receivedPacket;

            while ((bytesRead = recv(socket, buffer, sizeof(buffer), 0)) > 0) {
                std::string receivedData(buffer, bytesRead);
                try {
                    nlohmann::json receivedJson = nlohmann::json::parse(receivedData);
                    Packet receivedPacket;
                    receivedPacket.FromJson(receivedJson);

                    std::cout << "Received packet type" << receivedPacket.packetType
                        << " from client " << id << std::endl;
                }
                catch (const std::exception& e) {
                    std::cerr << "Error parsing JSON: " << e.what() << std::endl;
                }
            }
        }

        ErrorCode Client::Send(Packet packet)
        {
            nlohmann::json jsonPacket;
            packet.ToJson(jsonPacket);
            std::string jsonString = jsonPacket.dump();

            int result = send(socket, jsonString.c_str(), jsonString.size(), 0);
            if (result == SOCKET_ERROR) {
                std::cerr << "Error sending data: " << WSAGetLastError() << std::endl;
                return SocketError;
            }
            return Success;
        }

    }
}