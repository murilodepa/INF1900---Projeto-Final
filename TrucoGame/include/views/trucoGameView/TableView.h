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
            sf::Sprite tableCloth;
            CardView cardView;
            UtilsView *utilsView;

            void initialize(Vector2f windowSize);

        public:
            TableView(Vector2f windowSize);
            ~TableView();

            Texture getTableTexture();
            void setTableTexture(const std::string& texturePath);

            Sprite getTableCloth();
            void setTableCloth(Sprite tableCloth);

            void setTableClothScale(Vector2f windowSize, Vector2u textureSize);
        };
    }
}
