#ifndef PLAYER_VIEW_H
#define PLAYER_VIEW_H

// File path for the Arial.ttf font used for names
#define NAME_FONT_PATH "../../../../TrucoGame/resources/fonts/Arial.ttf"

// Character size for the player name display
#define PLAYER_NAME_CHARACTER_SIZE 50

// Define name color 
#define NAME_COLOR sf::Color::White

#pragma once
#include <SFML/Graphics.hpp>
#include "CardView.h"

using namespace sf;

namespace TrucoGame {
    namespace View {
        class PlayerView {
        private:
            Text playerName;
            std::vector<CardView> playerCards;
            Font font;

            void setFontFromPath(const std::string& fontPath);

        public:
            PlayerView(size_t numCardsInHands);
            ~PlayerView();

            void setPlayerName(std::string name);
            void setCardPositions(std::vector<Vector2f> cardPositions);
            void setNamePosition(Vector2f namePosition);
            void setNameRotation(float nameRotation);

            Text getPlayerName() const;
            float getTextWidth(size_t playerIndex) const;
            float getTextHeight(size_t playerIndex) const;
            float getHalfTextWidth(size_t playerIndex) const;
        };
    }
}

#endif // PLAYER_VIEW_H