#include "../../../include/models/server/ServerGameManager.h"
#include <iostream>


#define NUM_OF_PLAYERS 4
#define NUM_OF_HUMANS 2
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

        int ServerGameManager::startRound()
        {
            //Give players hand cards
            deck.reset();
            Card tableCard = deck.pop();
            table.SetTableCard(tableCard);
            score.resetRound();

            std::vector<Card> playerHands[4];

            for each (auto player in clients) {
                playerHands[player->id].push_back(deck.pop());
                playerHands[player->id].push_back(deck.pop());
                playerHands[player->id].push_back(deck.pop());
            }

            if (score.getTeam0GameScore() != score.getTeam1GameScore()) {
                if (score.getTeam0GameScore() + 1 == POINT_TO_WIN) {
                    std::cout << "Team 0 in eleven hand." << std::endl;
                    ElevenHandPacket elevenHandPacket(tableCard, playerHands[0], playerHands[2]);
                    clients[0]->Send(&elevenHandPacket);
                    ElevenHandPacket elevenHandPacket2(tableCard, playerHands[2], playerHands[0]);
                    clients[2]->Send(&elevenHandPacket2);

                    StartRoundPacket startRoundPacket(tableCard, playerHands[1]);
                    clients[1]->Send(&startRoundPacket);
                    StartRoundPacket startRoundPacket2(tableCard, playerHands[3]);
                    clients[3]->Send(&startRoundPacket2);

                    TcpClientPlayer* players[] = { clients[0], clients[2] };
                    auto [playerAResponse, playerBResponse] = tcpServer.WaitForTeamPacket(players);

                    ElevenHandResponsePacket a(playerAResponse->payload);
                    ElevenHandResponsePacket b(playerBResponse->payload);
                    std::cout << "ElevenHandResponse: " << a.response << "+" << b.response << std::endl;
                    if (a.response == 0 || b.response == 0) {
                        return 1;
                    }
                    else {
                        score.increaseStakes();
                    }
                    return -1; // no winner yet, play round normally
                }
                else if (score.getTeam1GameScore() + 1 == POINT_TO_WIN) {
                    std::cout << "Team 1 in eleven hand." << std::endl;
                    ElevenHandPacket elevenHandPacket(tableCard, playerHands[1], playerHands[3]);
                    clients[1]->Send(&elevenHandPacket);
                    ElevenHandPacket elevenHandPacket2(tableCard, playerHands[3], playerHands[1]);
                    clients[3]->Send(&elevenHandPacket2);

                    StartRoundPacket startRoundPacket(tableCard, playerHands[0]);
                    clients[0]->Send(&startRoundPacket);
                    StartRoundPacket startRoundPacket2(tableCard, playerHands[2]);
                    clients[2]->Send(&startRoundPacket2);

                    TcpClientPlayer* players[] = { clients[1], clients[3] };
                    auto [playerAResponse, playerBResponse] = tcpServer.WaitForTeamPacket(players);

                    ElevenHandResponsePacket a(playerAResponse->payload);
                    ElevenHandResponsePacket b(playerBResponse->payload);

                    std::cout << "ElevenHandResponse: " << a.response << "+" << b.response << std::endl;
                    if (a.response == 0 || b.response == 0) {
                        return 0;
                    }
                    else {
                        score.increaseStakes();
                    }
                    return -1; // no winner yet, play round normally
                }
            }
            

            for each (auto player in clients) {
                StartRoundPacket startRoundPacket(tableCard, playerHands[player->id]);
                player->Send(&startRoundPacket);
            }

            return -1; // no winner yet, play round normally
        }

        void ServerGameManager::startTurn() {
            int startingPlayer = 0;
            for (int i = 0; i < clients.size(); i++) {
                int currentPlayer = (i + startingPlayer) % 4;
                if(teamRefusedTruco == -1)
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
                    teamRefusedTruco = !trucoPacket.responseTeamId;
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
            int roundWinner;
            if (teamRefusedTruco != -1) {
                roundWinner = !teamRefusedTruco;
                teamRefusedTruco = -1;
                return roundWinner;
            }
            int turnWinner = table.CalculateWinner();
            roundWinner = score.updateTurnWon(turnWinner % 2);
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