#pragma once 
#include <SFML/Graphics.hpp>
#include <string>
#include <nlohmann/json.hpp>

namespace TrucoGame {

    namespace Models {
        enum Suit { Clubs = 4, Spades = 2, Diamonds = 1, Hearts = 3};

        class Card {
        private:
            int value;
            Suit suit;
        public:
            Card(int value, Suit suit);
            Card(const nlohmann::json& j);
            ~Card();
            Suit getSuit();
            int getValue();
            void ToJson(nlohmann::json& j) const;
            static Card FromJson(const nlohmann::json& j);
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