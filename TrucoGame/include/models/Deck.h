#pragma once 

#include "Card.h"
#include <vector>

namespace TrucoGame {

    namespace Models {

        class Deck {
        private:
            std::vector<Card> cards;
        public:
            Deck();
            ~Deck();
            Card pop();
            void push(Card card);
            void reset();

        };
    }
}