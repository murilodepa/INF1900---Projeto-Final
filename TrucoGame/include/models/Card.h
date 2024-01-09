#pragma once 
#include <SFML/Graphics.hpp>
#include <string>

namespace TrucoGame {

    namespace Models {
        enum Suit { Clubs, Spades, Diamonds, Hearts };

        class Card {
        private:
            int value;
            Suit suit;
            sf::Sprite sprite;
            sf::Texture texture;
        public:
            Card(int value, Suit suit);
            ~Card();
            Suit getSuit();
            int getValue();
            sf::Sprite* getSprite();
            std::string getSpritePath();
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