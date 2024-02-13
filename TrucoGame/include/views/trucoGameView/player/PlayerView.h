#ifndef PLAYER_VIEW_H
#define PLAYER_VIEW_H

// File path for the Arial.ttf font used for names
#define NAME_FONT_PATH "../../../../TrucoGame/resources/fonts/Arial.ttf"

// Character size for the player name display
#define CONSTANT_TO_CALCULATE_PLAYER_NAME_CHARACTER_SIZE 0.03

// Define name color 
#define NAME_COLOR sf::Color::White

#pragma once
#include <SFML/Graphics.hpp>
#include "../CardView.h"

using namespace sf;

namespace TrucoGame {
    namespace View {
        class PlayerView {
        private:
            Text playerName;
            std::vector<CardView> playerCards;
            Font font;
            float width, height;

            void setFontFromPath(const std::string& fontPath);

        public:
            PlayerView(size_t numCardsInHands, const float windowHeight, const std::string& name);
            ~PlayerView();

            void setPlayerName(std::string name);
            void setCardPositions(std::vector<Vector2f> cardPositions);
            void setNamePosition(Vector2f namePosition);
            void setNameRotation(float nameRotation);

            Text getPlayerName() const;
            float getTextWidth(size_t playerIndex) const;
            float getTextHeight(size_t playerIndex) const;
            float getHalfTextWidth(size_t playerIndex) const;
            Vector2f getCardPosition(size_t cardIndex) const;
        };
    }
}

#endif // PLAYER_VIEW_H