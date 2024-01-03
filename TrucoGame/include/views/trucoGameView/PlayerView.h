#pragma once
#include <SFML/Graphics.hpp>
#include "../UtilsView.h"

using namespace sf;

namespace TrucoGame {
    namespace View {
        class PlayerView {
        private:
            std::vector<Text> playerNames;
            Font nameFont;
            UtilsView* utilsView;
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
