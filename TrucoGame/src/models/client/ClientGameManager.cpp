#include "..\..\..\include\models\client\ClientGameManager.h"
#include <chrono>

#define DEFAULT_PORT 59821

namespace TrucoGame {
    namespace Models {
        
        void ClientGameManager::OnStartGamePacketReceived(StartGamePacket packet)
        {
            player = new Player(packet.playerId, "Player " + packet.playerId);
        }
        void ClientGameManager::OnStartRoundPacketReceived(StartRoundPacket packet)
        {
            player->hand = packet.handCards;
            //set table card
        }
        void ClientGameManager::OnPlayPacketReceived(PlayerPlayPacket packet)
        {
            CardPacket p = CardPacket(player->playerId, player->popCardByIndex(0), false);
            client.Send(&p);
        }

        ClientGameManager::ClientGameManager()
        {
            std::cout << "[CLIENT] Starting client Thread" << std::endl;

            ErrorCode result = ErrorCode::SocketError;

            while (HAS_FAILED(result)) {
                result = client.Connect("127.0.0.1", DEFAULT_PORT);
                std::this_thread::sleep_for(std::chrono::seconds(2));
            }
            client.StartListening();

            client.startGamePacketReceived = [this](StartGamePacket packet) {
                OnStartGamePacketReceived(packet);
            };
            client.startRoundPacketReceived = [this](StartRoundPacket packet) {
                OnStartRoundPacketReceived(packet);
            };
            client.playerPlayPacketReceived = [this](PlayerPlayPacket packet) {
                OnPlayPacketReceived(packet);
            };

            while (true) {}
        }

        
    }
}
