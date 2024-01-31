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
            int endTurn();
            int endRound(int roundWinner);
            void endGame(int gameWinner);
        };
    }
}