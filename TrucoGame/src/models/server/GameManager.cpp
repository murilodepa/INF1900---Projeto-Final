#include "../../../include/models/server/GameManager.h"
#include <iostream>
#include "../../../include/models/packets/PlayerPlayPacket.h"

#define NUM_OF_PLAYERS 1
#define DEFAULT_PORT 59821

namespace TrucoGame {
    namespace Models {
        void GameManager::waitForPlayersToConnect() {
            std::cout << "[SERVER] Starting Server Thread" << std::endl;
            tcpServer.Open(DEFAULT_PORT);

            clients = tcpServer.AcceptPlayers(NUM_OF_PLAYERS);
        }

        void GameManager::startGame() {
            for (int i = 0; i < clients.size(); i++) {
                StartGamePacket startGamePacket(i, i % 2);
                clients[i]->Send(&startGamePacket);
                //if loading game in clients takes long: consider implementing ReadyPacket
            }
        }

        void GameManager::startRound()
        {
            //Give players hand cards
            table.turnedCard = &deck.pop();
            score.resetRound();

            for each (auto player in clients) {
                std::vector<Card> hand;
                hand.push_back(deck.pop());
                hand.push_back(deck.pop());
                hand.push_back(deck.pop());
                StartRoundPacket startRoundPacket(*table.turnedCard, hand);
                player->Send(&startRoundPacket);
            }
        }

        void GameManager::startTurn() {
            int startingPlayer = 0;
            for (int i = 0; i < clients.size(); i++) {
                int currentPlayer = (i + startingPlayer) % 4;
                startPlay(currentPlayer);
            }
        }

        void GameManager::startPlay(int currentPlayer) {

            PlayerPlayPacket playerPlayPacket(currentPlayer);
            clients[currentPlayer]->Send(&playerPlayPacket);
            clients[currentPlayer]->WaitForPacket();

            //Handle received packet
            Packet* packet = clients[0]->WaitForPacket();
            if (packet->packetType == PacketType::PlayerCard) {
                CardPacket cardPacket(packet->payload);
                table.PlaceCard(&cardPacket.card, currentPlayer, false); //TODO: card packet isCovered property
            }
            else if (packet->packetType == PacketType::Truco) {
                TrucoPacket trucoPacket(packet->payload);
            }
        }

        void GameManager::playCard(int playerId, int cardIndex, bool isCovered)
        {/*
            Card* card = players[playerId].popCardByIndex(cardIndex);
            if (card == nullptr) {
                std::cout << "Can't play the card " << cardIndex << " of " << playerId << std::endl;
                return;
            }
            table.PlaceCard(card, playerId, isCovered);*/
        }

        int GameManager::endTurn() 
        {
            int turnWinner = table.CalculateWinner();
            int roundWinner = score.updateTurnWon(turnWinner % 2);
            //TODO: clear table cards
            return roundWinner;
        }

        int GameManager::endRound(int roundWinner) 
        {
            int gameWinner = score.updateRoundWon(roundWinner);
            //TODO: CleanPlayerCards(); ClearTurnedCard();
            return gameWinner;
        }

        void GameManager::endGame(int gameWinner)
        {
            //end the game based on the winner
        }
    }
}