#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

namespace TrucoGame {
    namespace View {
        class PlayerView {
        private:
            std::vector<Text> playerNames;
            Font nameFont;
            void initialize();

        public:
            PlayerView();
            ~PlayerView();

            std::vector<Text> getPlayerNames();
            void setPlayerNames(std::vector<Text> playerNames);
            Font getNameFont();
            void setNameFont(const std::string& fontPath);
        };
    }
}
