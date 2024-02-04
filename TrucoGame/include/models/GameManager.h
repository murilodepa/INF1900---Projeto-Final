#pragma once 

#include "Card.h"
#include "Deck.h"
#include "Table.h"
#include "Player.h"
#include <vector>

using namespace std;

namespace TrucoGame {

    namespace Models {

        class GameManager {
        private:
            Table table;
            Deck deck;
        public:
            vector<Player> players;
            GameManager();
            ~GameManager();
            void popAllPlayersCards();
            void cleanTableCards();
            void cleanPlayerCards();
        };
    }
}