#pragma once 

#include "TcpServer.h"
#include "TcpClientPlayer.h"
#include "../Card.h"
#include "../Deck.h"
#include "../Score.h"
#include "../Table.h"
#include "../Player.h"
#include <vector>

#include "../packets/StartGamePacket.h"
#include "../packets/StartRoundPacket.h"

#define NUM_OF_PLAYERS 1
#define DEFAULT_PORT 59821

namespace TrucoGame {

    namespace Models {

        class GameManager {
        private:
            TcpServer tcpServer;
            Score score;
            Deck deck;
            Table table;
            vector<TcpClientPlayer*> clients;

        public:
            void waitForPlayersToConnect();
            void startGame();
            void startRound();
            void startTurn();
            void startPlay(int currentPlayer);
            void playCard(int playerId, int cardIndex, bool isCovered);
            int endTurn();
            int endRound(int roundWinner);
            void endGame(int gameWinner);
        };
    }
}