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
            client.cardPacketReceived = [this](CardPacket packet) {
                OnCardPacketReceived(packet);
            };
            client.endRoundPacketReceived = [this](EndRoundPacket packet) {
                OnEndRoundPacketReceived(packet);
            };
            client.endTurnPacketReceived = [this](EndTurnPacket packet) {
                OnEndTurnPacketReceived(packet);
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

        void ClientGameManager::OnStartGamePacketReceived(StartGamePacket packet)
        {
            player = new Player(packet.playerId, "Player " + packet.playerId);
        }

        void ClientGameManager::OnStartRoundPacketReceived(StartRoundPacket packet)
        {
            std::cout << "Table Card: " << packet.tableCard.getValue() << " " << packet.tableCard.getSuit();
            player->hand = packet.handCards;

            if (score.team0GameScore + 1 == POINT_TO_WIN && score.team1GameScore + 1 == POINT_TO_WIN) {
                if (ironHandRoundStarted)
                    ironHandRoundStarted(packet.tableCard);
            }
            else {
                if (roundStarted)
                    roundStarted(packet.tableCard, packet.handCards);
            }
            
        }

        void ClientGameManager::OnPlayPacketReceived(PlayerPlayPacket packet)
        {
            std::cout << "Hand [";
            for (int i = 0; i < player->hand.size(); i++) {
                std::cout << ":" << player->hand[i].getValue() << " " << player->hand[i].getSuit();
            }
            std::cout << "]" << std::endl;

            if(myTurnStarted)
                myTurnStarted(packet.canRequestTruco);
        }

        void ClientGameManager::OnTrucoPacketReceived(TrucoPacket packet) 
        {
            std::cout << "Received Truco Packet " << packet.result << std::endl;
            lastTrucoRequesterId = packet.requesterId;
            lastTrucoReponseTeamId = packet.responseTeamId;
            if (packet.result == TrucoResult::Yes) {
                std::cout << "Truco was accepted" << std::endl;

                if (trucoAccepted)
                    trucoAccepted(score.getStakes());

                if (packet.requesterId == player->playerId)
                {
                    std::cout << "I am the player now:" << std::endl;
                    if (myTurnStarted)
                        myTurnStarted(false);
                }
            }
            else if(packet.result == TrucoResult::Raise)
            {
                score.increaseStakes();

                if (packet.responseTeamId == player->playerId % 2)
                {
                    if (trucoRequested)
                        trucoRequested(packet.requesterId, score.getStakes());
                }
            }
            else {
                if (trucoRefused)
                    trucoRefused();
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

            if (elevenHandRoundStarted)
                elevenHandRoundStarted(packet.tableCard, packet.handCards, packet.partnerHand);
        }

        void ClientGameManager::OnCardPacketReceived(CardPacket packet)
        {
            if(anotherPlayerPlayed)
                anotherPlayerPlayed(packet.card, packet.playerId, packet.isCovered);
        }

        void ClientGameManager::OnEndTurnPacketReceived(EndTurnPacket packet) {
            if (turnEnded)
                turnEnded(packet.winnerTeamId, packet.winnerPlayerId);
        }
        
        void ClientGameManager::OnEndRoundPacketReceived(EndRoundPacket packet) {
            score.team0GameScore = packet.team0Score;
            score.team1GameScore = packet.team1Score;
            score.resetRound();

            if (roundEnded)
                roundEnded(packet.winnerTeamId, packet.team0Score, packet.team1Score);

            if (score.team0GameScore == POINT_TO_WIN)
            {
                if (player->playerId % 2 == 0) {
                    if (gameWon)
                        gameWon();
                }
                else {
                    if (gameLost)
                        gameLost();
                }
            }
            else if (score.team1GameScore == POINT_TO_WIN)
            {
                if (player->playerId % 2 == 1) {
                    if (gameWon)
                        gameWon();
                }
                else {
                    if (gameLost)
                        gameLost();
                }
            }
        }

        void ClientGameManager::RequestTruco()
        {
            TrucoPacket p(player->playerId, (player->playerId + 1) % 2, TrucoResult::Raise);
            client.Send(&p);
        }
        void ClientGameManager::PlayCard(int index, bool isCovered) 
        {
            CardPacket p = CardPacket(player->playerId, player->popCardByIndex(index), isCovered);
            client.Send(&p);
        }
        void ClientGameManager::RespondTrucoRequest(int trucoResult)
        {
            TrucoPacket packet(lastTrucoRequesterId, !lastTrucoReponseTeamId, (TrucoResult)trucoResult);
            client.Send(&packet);
        }
        void ClientGameManager::RespondElevenHand(bool accepted)
        {
            ElevenHandResponsePacket response(accepted);
            client.Send(&response);
        }
        
    }
}
