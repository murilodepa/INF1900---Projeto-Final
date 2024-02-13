#ifndef TABLE_VIEW_H
#define TABLE_VIEW_H

#pragma once
#include <SFML/Graphics.hpp>
#include "../../../include/views/GraphicManager.h"
#include "CardView.h"

using namespace sf;

// Define to represent the number of players
#define NUM_PLAYERS 4

// Define to represent the number of cards in hand
#define CARDS_IN_HAND 3

// Define the total number of cards using the formula (NUM_PLAYERS * CARDS_IN_HAND + 2)
#define TOTAL_CARDS_IN_INITIAL_DECK (NUM_PLAYERS * CARDS_IN_HAND + 2)  // 2 - One cart is to turn face up and another it to represents the deck on the tablhe.

// Define the texture of a back card
#define CARD_BACK_TEXTURE_PATH "../../../../TrucoGame/resources/images/cards/cardBack.png"

// Define the texture of table cloth
#define TABLE_TEXTURE_PATH "../../../../TrucoGame/resources/images/table/tablecloth_texture4.png"

struct CardTurnedFaceUpAndDeck {
    sf::Vector2f cardTurnedFaceUpPosition;
    sf::Vector2f deckPosition;
    float deckRotation;
};

namespace TrucoGame {
    namespace View {
        class TableView {
        private:
            Texture tableTexture;
            Texture backCardTexture;
            Texture turnedFaceUpCardTexture;
            Texture* texture;

            Sprite tableCloth;
            CardTurnedFaceUpAndDeck cardTurnedFaceUpAndDeck;
            CardView* cardTurnedFaceUp;
            CardView* deck;
            Vector2f **cardPositionsInPlayerHands;
            

            void initialize(Vector2f windowSize, Vector2f& initialDeckPositionVector2f, const float cardScale);
            void setDeckPositionOnTheTable(float screenWidth, float screenHeight, float cardWidth);

        public:
            TableView(Vector2f& windowSize, Vector2f& initialDeckPositionVector2f, const float cardScale);
            ~TableView();
            void setTableTexture(const std::string& texturePath);
            void setBackCardTexture(const std::string& texturePath);
            Sprite getTableCloth();
            void setTableClothScale(Vector2f& windowSize, Vector2u& textureSize);
            void drawElementsOnTheTable(GraphicManager* pGraphicManager) const;
            void moveDeckAndTurnUpCard(const float cardScale, float speed, std::string& texturePathToturnedFaceUpCard);
            void setTurnedFaceUpCardTexture(std::string& texturePath);
            void setTextureFromPath(const std::string& texturePath);
        };
    }
}

#endif // TABLE_VIEW_H
