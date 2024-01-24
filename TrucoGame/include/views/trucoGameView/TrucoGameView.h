#ifndef TRUCO_GAME_VIEW_H
#define TRUCO_GAME_VIEW_H

#pragma once
#include <SFML/Graphics.hpp>
#include "../../../include/views/GraphicManager.h"
#include "../../../include/views/UtilsView.h"
#include "TableView.h"
#include "ScoreView.h"
#include "Player/PlayerView.h"
#include "Player/PlayerCards.h"

// Macro to create a initial position to the deck like sf::Vector2f
#define InitialDeckPositionVector2f(x, y) sf::Vector2f(x, y)

// Define the spacing between cards.
#define CARDS_SPACING 16.0f

// Define the spacing between the table and cards
#define TABLE_AND_CARDS_SPACING 110.0f

// Define the spacing between the player name table
#define TEXT_AND_TABLE_SPACING 40.0f

using namespace sf;

namespace TrucoGame {
    namespace View {
        class TrucoGameView {
        private:
            TableView tableView;
            ScoreView scoreView;
            PlayerCards playerCards;
            std::vector<PlayerView*> players;
            std::vector<std::string> names;

            void initialize(Vector2f& windowSize);

            void setCardPositionsOfThePlayers(float screenWidth, float screenHeight, float cardWidth, float cardHeight, float cardsSpacing, float cardAndTableSpacing);
            void setNamesPositions(float screenWidth, float screenHeight, float textAndTableSpacing, std::vector<std::string>& names);

            void drawScore(GraphicManager* pGraphicManager);
            void drawCardsOnTheTable(GraphicManager* pGraphicManager);
            void drawPlayerNames(GraphicManager* pGraphicManager);
            void distributeCardsToPlayers();

        public:
            TrucoGameView(Vector2f windowSize);
            ~TrucoGameView();
            void drawElementsOnTheWindow(GraphicManager* pGraphicManager, std::shared_ptr<bool> firstTimeFlag);
            void setPlayerNames(std::vector<std::string> names);
        };
    }
}

#endif // TRUCO_GAME_VIEW_H