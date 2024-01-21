#pragma once 
#include <SFML/Graphics.hpp>
#include <string>

namespace TrucoGame {

    namespace Models {
        enum Suit { Clubs = 4, Spades = 2, Diamonds = 1, Hearts = 3};

        class Card {
        private:
            int value;
            Suit suit;
        public:
            Card(int value, Suit suit);
            ~Card();
            Suit getSuit();
            int getValue();
        };

        class ClubsCard : public Card {
        public:
            ClubsCard(int value) : Card(value, Suit::Clubs) {}
        };

        class SpadesCard : public Card {
        public:
            SpadesCard(int value) : Card(value, Suit::Spades) {}
        };

        class DiamondsCard : public Card {
        public:
            DiamondsCard(int value) : Card(value, Suit::Diamonds) {}
        };
        class HeartsCard : public Card {
        public:
            HeartsCard(int value) : Card(value, Suit::Hearts) {}
        };
    }
}