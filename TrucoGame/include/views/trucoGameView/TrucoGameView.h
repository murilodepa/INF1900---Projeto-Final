#ifndef TRUCO_GAME_VIEW_H
#define TRUCO_GAME_VIEW_H

#pragma once
#include <SFML/Graphics.hpp>
#include "../../../include/views/GraphicManager.h"
#include "../../../include/views/utils/UtilsView.h"
#include "TableView.h"
#include "ScoreView.h"
#include "Player/PlayerView.h"
#include "Player/PlayerCards.h"
#include "buttonsTruco/CardButton.h"

// Define a constant to calculate the spacing between cards.
#define CALCULATE_CARDS_SPACING 0.02f

// Define a constant to calculate the spacing between the table and cards
#define CALCULATE_TABLE_AND_CARDS_SPACING 0.073f 

// Define a constant to calculate the spacing between the player name table
#define CALCULATE_TEXT_AND_TABLE_SPACING 0.02f

// Define a constant to calculate the speed to animations
#define CALCULATE_ANIMATION_SPEED 40.f

// Define the color to card hover
#define COLOR_CARD_HOVER Color::Blue

using namespace sf;

namespace TrucoGame {
    namespace View {
        class TrucoGameView {
        private:
            TableView tableView;
            ScoreView scoreView;
            PlayerCards playerCards;
            std::vector<PlayerView*> players;
            std::vector<CardButton*> cardButtons;
            std::vector<Vector2f> positionToDiscardCards;
            float cardScale, animationSpeed;
            Vector2f windowSize;

            void initialize(const std::vector<std::string>& playerNames);

            void setCardPositionsOfThePlayers(float screenWidth, float screenHeight, float cardWidth, float cardHeight, float cardsSpacing, float cardAndTableSpacing);
            void setNamesPositions(float screenWidth, float screenHeight, float textAndTableSpacing);
            void setPositionToDiscardCards();

            void drawScore(GraphicManager* pGraphicManager);
            void drawCardsOnTheTable(GraphicManager* pGraphicManager);
            void drawPlayerNames(GraphicManager* pGraphicManager);
            void checkIftheCardHasBeenDiscardedAndDraw(GraphicManager* pGraphicManager, Vector2f& mousePosView);
            void distributeCardsToPlayers(std::vector<std::string>& texturePathToMainPlayerCards);
            void discardCard(size_t player, size_t card, std::string& cardTexturePath);
            void testDiscartCards();

        public:
            TrucoGameView(const Vector2f windowSize, const float cardScale, Vector2f& initialDeckPosition, const std::vector<std::string>& playerNames);
            ~TrucoGameView();
            void drawElementsOnTheWindow(GraphicManager* pGraphicManager, std::shared_ptr<bool> firstTimeFlag, Vector2f& mousePosView, std::vector<std::string>& texturePathToMainPlayerCards, std::string& cardPathToturnedFaceUp);
        };
    }
}

#endif // TRUCO_GAME_VIEW_H