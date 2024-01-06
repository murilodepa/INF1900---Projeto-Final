#pragma once
#include <SFML/Graphics.hpp>
#include "../../../include/views/GraphicManager.h"
#include "CardView.h"
#include "PlayerView.h"

using namespace sf;

// Define to represent the number of players
#define NUM_PLAYERS 4

// Define to represent the number of cards in hand
#define CARDS_IN_HAND 3

// Macro para facilitar a criação de uma posição inicial para o deck como sf::Vector2u
#define InitialDeckPositionVector2u(x, y) sf::Vector2u(x, y)

// Define the spacing between cards.
#define CARDS_SPACING 16.0f

// Define the spacing between the table and cards.
#define TABLE_AND_CARDS_SPACING 20.0f


namespace TrucoGame {
    namespace View {
        class TableView {
        private:
            View::GraphicManager* pGraphicManager;
            Texture tableTexture;
            sf::Sprite tableCloth;

            CardView cardView;

            void initialize(Vector2f windowSize);
            void setCardPositionsInPlayerHandsOnTable(float screenWidth, float screenHeight, float cardWidth, float cardHeight, float cardsSpacing, float cardAndTableSpacing);

        public:
            TableView(Vector2f windowSize);
            ~TableView();
            Texture getTableTexture();
            void setTableTexture(const std::string& texturePath);
            Sprite getTableCloth();
            void setTableCloth(Sprite tableCloth);
            void setTableClothScale(Vector2f windowSize, Vector2u textureSize);

            void drawElementsOnTheTable();
            void distributeCardsAndFlip();
        };
    }
}
