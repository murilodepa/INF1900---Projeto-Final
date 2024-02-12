#include "..\..\..\include\models\client\ClientGameManager.h"
#include <chrono>
#include <random>

#define DEFAULT_PORT 59821

namespace TrucoGame {
    namespace Models {
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
            client.trucoPacketReceived = [this](TrucoPacket packet) {
                OnTrucoPacketReceived(packet);
            };
        }

        void ClientGameManager::GetPlayerInputAndSend()
        {
            int input;
            std::cin >> input;
            if (input < player->hand.size())
            {
                CardPacket p = CardPacket(player->playerId, player->popCardByIndex(input), false);
                client.Send(&p);
            }
            else
            {
                std::cout << std::endl << "Requesting Truco..." << std::endl;
                int id = player->playerId;
                TrucoPacket p(id, (id + 1) % 2, TrucoResult::Raise);
                client.Send(&p);
            }
        }

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
            std::cout << "Hand [";
            for (int i = 0; i < player->hand.size(); i++) {
                std::cout << ":" << player->hand[i].getValue() << " " << player->hand[i].getSuit();
            }
            std::cout << "]" << std::endl;


            GetPlayerInputAndSend();

        }

        void ClientGameManager::OnTrucoPacketReceived(TrucoPacket packet) 
        {
            std::cout << "Received Truco Packet" << std::endl;

            if (packet.result == TrucoResult::Yes) {
                std::cout << "Truco was accepted" << std::endl;
                //Update Stakes
                if (packet.requesterId == player->playerId)
                {
                    std::cout << "I am the player now:" << std::endl;
                    GetPlayerInputAndSend();
                }
            }
            else
            {
                if (packet.responseTeamId == player->playerId % 2)
                {
                    std::cout << "Yes : 0 | No : 1 | Raise : 2" << std::endl;
                    int input;
                    std::cin.clear();
                    std::cin >> input;
                    packet.result = (TrucoResult)input;
                    packet.responseTeamId = !packet.responseTeamId;
                    client.Send(&packet);

                }
            }
        }

        
    }
}
