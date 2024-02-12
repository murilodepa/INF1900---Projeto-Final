#pragma once 

#include "TcpServer.h"
#include "AIPlayer.h"
#include "TcpClientPlayer.h"
#include "../Card.h"
#include "../Deck.h"
#include "../Score.h"
#include "../Table.h"
#include "../Player.h"
#include <vector>

#include "../packets/StartGamePacket.h"
#include "../packets/StartRoundPacket.h"
#include "../packets/ElevenHandPacket.h"
#include "../packets/PlayerPlayPacket.h"
#include "../packets/ElevenHandResponsePacket.h"

namespace TrucoGame {

    namespace Models {

        class ServerGameManager {
        private:
            TcpServer tcpServer;
            Score score;
            Deck deck;
            Table table;
            vector<TcpClientPlayer*> clients;

            TrucoResult calculateTrucoResult(TrucoResult a, TrucoResult b);
            int teamRefusedTruco = -1;
        public:
            void waitForPlayersToConnect();
            void startGame();
            int startRound();
            void startTurn();
            void startPlay(int currentPlayer);
            int endTurn();
            int endRound(int roundWinner);
            void endGame(int gameWinner);
        };
    }
}