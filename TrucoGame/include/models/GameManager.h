#pragma once 

#include "Card.h"
#include "Deck.h"
#include "Table.h"
#include "Player.h"
#include <vector>

namespace TrucoGame {

    namespace Models {

        class GameManager {
        private:
            Table table;
            std::vector<Player> players;
        public:
            GameManager();
            ~GameManager();
            void CleanPlayerCards();
            void ShuffleCards();
        };
    }
}