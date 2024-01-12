#ifndef PLAYER_NAME_H
#define PLAYER_NAME_H

// File path for the Arial.ttf font used for names
#define NAME_FONT_PATH "../../../../TrucoGame/resources/fonts/Arial.ttf"

// Character size for the player name display
#define PLAYER_NAME_CHARACTER_SIZE 50

#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

namespace TrucoGame {
    namespace View {
        class PlayerName {
        private:
            std::vector<Text> playerNamesText;
            Font font;

            void setFontFromPath(const std::string& fontPath);

        public:
            PlayerName(size_t numPlayers);
            ~PlayerName();

            Text getPlayerName(size_t playerIndex);
            void setPlayerNames(std::vector<std::string> names);

            float getTextWidth(size_t playerIndex) const;
            float getTextHeight(size_t playerIndex) const;
            float getHalfTextWidth(size_t playerIndex) const;

            void setPositionOfPlayerName(size_t playerIndex, Vector2f namePosition);
            void setRotationOfPlayerName(size_t playerIndex, float nameRotation);
        };
    }
}

#endif // PLAYER_NAME_H