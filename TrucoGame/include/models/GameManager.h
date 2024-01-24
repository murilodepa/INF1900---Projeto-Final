#pragma once 

#include "Card.h"
#include "Deck.h"
#include "Score.h"
#include "Table.h"
#include "Player.h"
#include <vector>

namespace TrucoGame {

    namespace Models {

        class GameManager {
        private:
            Score score;
            Deck deck;
            Table table;
            vector<Player> players;

        public:
            void playCard(int playerId, int cardIndex, bool isCovered);
            void endTurn();
            void endRound(int roundWinner);
            void endGame(int gameWinner);
        };
    }
}