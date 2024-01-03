#pragma once
#include <SFML/Graphics.hpp>
#include "../../../include/views/UtilsView.h"
#include "CardView.h"
#include "PlayerView.h"

using namespace sf;

// Define to represent the number of players
#define NUM_PLAYERS 4

// Define to represent the number of cards in hand
#define CARDS_IN_HAND 3

namespace TrucoGame {
    namespace View {
        class TableView {
        private:
            Texture tableTexture;
            Vector2u tableTextureSize;
            Sprite tableCloth;

            UtilsView *utilsView;

            void initialize();

        public:
            TableView();
            ~TableView();

            Texture getTableTexture();
            void setTableTexture(const std::string& texturePath);

            Vector2u getTableTextureSize();
            void setTableTextureSize(Vector2u tableTextureSize);

            Sprite getTableCloth();
            void setTableCloth(Sprite tableCloth);
        };
    }
}
