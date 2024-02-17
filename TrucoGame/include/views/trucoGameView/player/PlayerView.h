#ifndef PLAYER_VIEW_H
#define PLAYER_VIEW_H

// Character size for the player name display
#define CONSTANT_TO_CALCULATE_PLAYER_NAME_CHARACTER_SIZE 0.03f

// Define name color 
#define NAME_COLOR sf::Color::White

#pragma once
#include <SFML/Graphics.hpp>
#include "../CardView.h"
#include "../../text/TextView.h"

using namespace sf;

namespace TrucoGame {
    namespace View {
        class PlayerView {
        private:
            std::vector<CardView> playerCards;
            Font font;
            float width, height;

            void setFontFromPath(const std::string& fontPath);

        public:
            TextView* playerName;

            PlayerView(size_t numCardsInHands, const float windowHeight, const std::string& name);
            ~PlayerView();

            void setCardPositions(std::vector<Vector2f> cardPositions);
            void setNamePosition(Vector2f namePosition);
            void setNameRotation(float nameRotation);

            TextView getPlayerName() const;
            Vector2f getCardPosition(size_t cardIndex) const;
        };
    }
}

#endif // PLAYER_VIEW_H