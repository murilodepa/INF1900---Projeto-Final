#include "../../../include/models/server/ServerGameManager.h"
#include <iostream>
#include "../../../include/models/packets/PlayerPlayPacket.h"
#include "../../../include/models/server/AIPlayer.h"

#define NUM_OF_PLAYERS 4
#define NUM_OF_HUMANS 1
#define DEFAULT_PORT 59821

namespace TrucoGame {
    namespace Models {
        void ServerGameManager::waitForPlayersToConnect() {
            std::cout << "[SERVER] Starting Server Thread" << std::endl;
            tcpServer.Open(DEFAULT_PORT);

            clients = tcpServer.AcceptPlayers(NUM_OF_HUMANS);   

            for (int i = NUM_OF_HUMANS; i < NUM_OF_PLAYERS; i++) {
                clients.push_back(new AIPlayer(i, &table));
            }
        }

        void ServerGameManager::startGame() {
            for (int i = 0; i < clients.size(); i++) {
                StartGamePacket startGamePacket(i, i % 2);
                clients[i]->Send(&startGamePacket);
                //if loading game in clients takes long: consider implementing ReadyPacket
            }
        }

        void ServerGameManager::startRound()
        {
            //Give players hand cards
            deck.reset();
            Card tableCard = deck.pop();
            table.SetTableCard(tableCard);
            score.resetRound();

            for each (auto player in clients) {
                std::vector<Card> hand;
                hand.push_back(deck.pop());
                hand.push_back(deck.pop());
                hand.push_back(deck.pop());
                StartRoundPacket startRoundPacket(tableCard, hand);
                player->Send(&startRoundPacket);
            }
        }

        void ServerGameManager::startTurn() {
            int startingPlayer = 0;
            for (int i = 0; i < clients.size(); i++) {
                int currentPlayer = (i + startingPlayer) % 4;
                startPlay(currentPlayer);
            }
            std::cout << std::endl;
        }

        void ServerGameManager::startPlay(int currentPlayer) {
            PlayerPlayPacket playerPlayPacket(currentPlayer);
            clients[currentPlayer]->Send(&playerPlayPacket);

        waitForPlayerPacket:
            Packet* packet = clients[currentPlayer]->WaitForPacket();
            if (packet->packetType == PacketType::PlayerCard) {
                CardPacket cardPacket(packet->payload);
                std::cout << cardPacket.playerId << ": " << "[" << cardPacket.card.getValue() << " " << cardPacket.card.getSuit() << "] | ";

                table.PlaceCard(cardPacket.card, cardPacket.playerId, false); 
            }
            else if (packet->packetType == PacketType::Truco) {
                TrucoPacket trucoPacket(packet->payload);
                TrucoResult result = TrucoResult::Raise;

                while (score.getStakes() < score.maxStakes && result == TrucoResult::Raise) {
                    tcpServer.SendToClients(clients, &trucoPacket);

                    int teamId = trucoPacket.responseTeamId;
                    TcpClientPlayer* players[] = { clients[teamId], clients[teamId + 2] };
                    auto [playerAResponse, playerBResponse] = tcpServer.WaitForTeamPacket(players);
                    TrucoPacket a(playerAResponse->payload);
                    TrucoPacket b(playerBResponse->payload);

                    result = calculateTrucoResult(a.result, b.result);

                    if (result != TrucoResult::No) {
                        score.increaseStakes();
                    }

                    trucoPacket = TrucoPacket(trucoPacket.requesterId, a.responseTeamId, result);

                    delete playerAResponse;
                    delete playerBResponse;
                }

                tcpServer.SendToClients(clients, &trucoPacket);

                if (result == TrucoResult::No) {
                    endRound(!trucoPacket.responseTeamId);
                    return;
                }

                goto waitForPlayerPacket; //After truco, wait for requester player card
            }
        }

        TrucoResult ServerGameManager::calculateTrucoResult(TrucoResult a, TrucoResult b)
        {
            if (a == TrucoResult::No || b == TrucoResult::No)
                return TrucoResult::No;
            if (a == TrucoResult::Raise || b == TrucoResult::Raise)
                return TrucoResult::Raise;

            return TrucoResult::Yes;
        }

        int ServerGameManager::endTurn()
        {
            int turnWinner = table.CalculateWinner();
            int roundWinner = score.updateTurnWon(turnWinner % 2);
            table.playedCards.clear();
            //TODO: clear table cards
            std::cout << "===== TURN ENDED ===== ";
            std::cout << score.getTeam0TurnsWon() << " - " << score.getTeam1TurnsWon() << std::endl;
            return roundWinner;
        }

        int ServerGameManager::endRound(int roundWinner)
        {
            int gameWinner = score.updateRoundWon(roundWinner);
            //TODO: CleanPlayerCards(); ClearTurnedCard();

            std::cout << "========== ROUND ENDED ========== ";
            std::cout << score.getTeam0GameScore() << " x " << score.getTeam1GameScore() << std::endl;
            return gameWinner;
        }

        void ServerGameManager::endGame(int gameWinner)
        {
            std::cout << "=============== GAME ENDED ================" << std::endl;
            std::cout << "WINNER: " << gameWinner << std::endl;
            std::cout << "===========================================" << std::endl;
            //end the game based on the winner
        }
    }
}