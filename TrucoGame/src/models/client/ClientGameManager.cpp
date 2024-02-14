#include "..\..\..\include\models\client\ClientGameManager.h"
#include <chrono>
#include <random>

#define DEFAULT_PORT 59821

namespace TrucoGame {
    namespace Models {
        ClientGameManager::ClientGameManager()
        {
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
            client.elevenHandPacketReceived = [this](ElevenHandPacket packet) {
                OnElevenHandPacketReceived(packet);
            };
        }

        void ClientGameManager::Start(std::string ip) 
        {
            std::cout << "[CLIENT] Starting client Thread" << std::endl;

            ErrorCode result = ErrorCode::SocketError;

            while (HAS_FAILED(result)) {
                result = client.Connect(ip.c_str(), DEFAULT_PORT);
                std::this_thread::sleep_for(std::chrono::seconds(2));
            }
            client.StartListening();
        }

        void ClientGameManager::GetPlayerInputAndSend()
        {
            std::cin.clear();
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
            std::cout << "Table Card: " << packet.tableCard.getValue() << " " << packet.tableCard.getSuit();
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
            std::cout << "Received Truco Packet " << packet.result << std::endl;

            if (packet.result == TrucoResult::Yes) {
                std::cout << "Truco was accepted" << std::endl;
                //Update Stakes
                if (packet.requesterId == player->playerId)
                {
                    std::cout << "I am the player now:" << std::endl;
                    GetPlayerInputAndSend();
                }
            }
            else if(packet.result == TrucoResult::Raise)
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
        void ClientGameManager::OnElevenHandPacketReceived(ElevenHandPacket packet) 
        {
            std::cout << "Table Card: " << packet.tableCard.getValue() << " " << packet.tableCard.getSuit();
            player->hand = packet.handCards;

            std::cout << "My hand [";
            for (int i = 0; i < packet.handCards.size(); i++) {
                std::cout << ":" << packet.handCards[i].getValue() << " " << packet.handCards[i].getSuit();
            }
            std::cout << "]" << std::endl << std::endl;

            std::cout << "My partner hand [";
            for (int i = 0; i < packet.partnerHand.size(); i++) {
                std::cout << ":" << packet.partnerHand[i].getValue() << " " << packet.partnerHand[i].getSuit();
            }
            std::cout << "]" << std::endl << std::endl;

            std::cout << "Yes : 1 | No : 0" << std::endl;
            int input;
            std::cin.clear();
            std::cin >> input;
            ElevenHandResponsePacket response(input);
            client.Send(&response);
        }

        
    }
}
