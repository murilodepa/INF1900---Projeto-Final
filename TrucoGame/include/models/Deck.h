#pragma once 

#include "Card.h"
#include <vector>

namespace TrucoGame {

    namespace Models {

        class Deck {
        private:
            vector<Card> cardDeck;
        public:
            Deck();
            ~Deck();
            Card DrawCard();
            void returnCard();

        };
    }
}