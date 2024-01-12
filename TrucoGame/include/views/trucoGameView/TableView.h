#ifndef TABLE_VIEW_H
#define TABLE_VIEW_H

#pragma once
#include <SFML/Graphics.hpp>
#include "../../../include/views/GraphicManager.h"
#include "CardView.h"

#include "CardDeck.h"
#include "PlayerName.h"

using namespace sf;

// Define to represent the number of players
#define NUM_PLAYERS 4

// Define to represent the number of cards in hand
#define CARDS_IN_HAND 3

// Define the total number of cards using the formula (NUM_PLAYERS * CARDS_IN_HAND + 2)
#define TOTAL_CARDS_IN_INITIAL_DECK (NUM_PLAYERS * CARDS_IN_HAND + 2)  // 2 - One cart is to turn face up and another it to represents the deck on the tablhe.

// Macro to create a initial position to the deck like sf::Vector2f
#define InitialDeckPositionVector2f(x, y) sf::Vector2f(x, y)

// Define the spacing between cards.
#define CARDS_SPACING 16.0f

// Define the spacing between the table and cards
#define TABLE_AND_CARDS_SPACING 110.0f

// Define the spacing between the player name table
#define TEXT_AND_TABLE_SPACING 40.0f

struct CardTurnedFaceUpAndDeck {
    sf::Vector2f cardTurnedFaceUpPosition;
    sf::Vector2f deckPosition;
    float deckRotation;
};

namespace TrucoGame {
    namespace View {
        class TableView {
        private:
            View::GraphicManager* pGraphicManager;
            Texture tableTexture;
            Sprite tableCloth;
            CardDeck cardDeck;
            PlayerName playerName;
            Vector2f **cardPositionsInPlayerHands;
            CardTurnedFaceUpAndDeck cardTurnedFaceUpAndDeck;

            void initialize(Vector2f windowSize);
            void setCardPositionsOnTheTable(float screenWidth, float screenHeight, float cardWidth, float cardHeight, float cardsSpacing, float cardAndTableSpacing);

        public:
            TableView(Vector2f& windowSize);
            ~TableView();
            void setTableTexture(const std::string& texturePath);
            Sprite getTableCloth();
            void setTableClothScale(Vector2f& windowSize, Vector2u& textureSize);
            void drawElementsOnTheTable();
            void distributeCardsAndFlip();
            void setNamesPositionsOnTheTable(float screenWidth, float screenHeight, float textAndTableSpacing);
        };
    }
}

#endif // TABLE_VIEW_H
