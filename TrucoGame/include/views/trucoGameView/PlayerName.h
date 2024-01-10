#ifndef PLAYER_NAME_H
#define PLAYER_NAME_H

#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

namespace TrucoGame {
    namespace View {
        class PlayerName {
        private:
            std::vector<Text> playerNamesText;
            Font font;

        public:
            PlayerName(size_t numPlayers);
            ~PlayerName();

            Font getFont();
            void setFontFromPath(const std::string& fontPath);

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