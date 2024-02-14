#include "../../include/controllers/Application.h"
#include "../../include/views/trucoGameView/Animator.h"
#include "../../include/views/utils/UtilsView.h"
#include <thread>
#include <iostream>
#include "../../include/models/Deck.h"
#include "../../include/models/Player.h"
#include "../../include/models/Table.h"
#include "../../include/models/Card.h"
#include "../../include/models/GameManager.h"

using namespace TrucoGame::View;
using namespace TrucoGame::Models;

namespace TrucoGame {

    GraphicManager* Application::pGraphicManager = GraphicManager::getGraphicManager();

    Application::Application(const std::vector<std::string>& playerNames) :
        trucoGameView([&]() {
        Vector2f windowSize;
        if ((pGraphicManager != nullptr)) {
            windowSize = pGraphicManager->getWindowSize();
        }
        else {
            windowSize = Vector2f(SCREEN_X / 2, SCREEN_Y / 2);
        }
        float initialDeckPosition = windowSize.x * CALCULATE_INITIAL_DECK_POSITION;
        float cardScale = windowSize.y / CALCULATE_CARD_SCALE;

        std::vector<std::string> names = playerNames.empty() ? std::vector<std::string>{ "Jogador 1", "Jogador 2", "Jogador 3", "Jogador 4" } : playerNames;

        return TrucoGameView(windowSize, cardScale, Vector2f(initialDeckPosition, initialDeckPosition), names);
        }()),
        mouseState((pGraphicManager != nullptr) ? std::make_unique<TrucoGame::View::MouseState>(pGraphicManager->getWindow()) : nullptr)
    {
        if (pGraphicManager == nullptr || mouseState == nullptr) {
            std::cout << "ERROR::TrucoGame::Application - Failed to create GraphicManager." << std::endl;
            exit(1);
        }
        initialize();
    }

    Application::~Application() {

    }

    void Application::initialize() {
        // TODO Define the initial state of the window
    }

    void Application::run()
    {

        std::shared_ptr<bool> firstTimeFlag = std::make_shared<bool>(true);
        // TEST CODE FOR THE MODELS, WILL BE REMOVED LATER
        //std::vector<Player> players;
        //players.push_back(Player("Laert",  0));
        //players.push_back(Player("Caique", 1));
        //players.push_back(Player("Vitor",  2));
        //players.push_back(Player("Murilo", 3));

        std::vector<std::string> texturePathToMainPlayerCards;
        CardStruct cardStruct;

        cardStruct.rank = CardRank::Ace;
        cardStruct.suit = CardSuit::Spades;
        texturePathToMainPlayerCards.emplace_back(UtilsView::findTexturePathByNumberAndSuit(cardStruct));
        
        cardStruct.rank = CardRank::Five;
        cardStruct.suit = CardSuit::Hearts;
        texturePathToMainPlayerCards.emplace_back(UtilsView::findTexturePathByNumberAndSuit(cardStruct));
        
        cardStruct.rank = CardRank::Queen;
        cardStruct.suit = CardSuit::Diamonds;
        texturePathToMainPlayerCards.emplace_back(UtilsView::findTexturePathByNumberAndSuit(cardStruct));

        cardStruct.rank = CardRank::Ace;
        cardStruct.suit = CardSuit::Clubs;
        std::string texturePathToturnedFaceUpCard = UtilsView::findTexturePathByNumberAndSuit(cardStruct);

        Table table;
        Deck deck;        
        Models::Card* cards[4];
        table.turnedCard = deck.pop();

      /*  GameManager gameManager;
        gameManager.players = players;
        gameManager.popAllPlayersCards();
        gameManager.cleanPlayerCards();*/

        // get 4 cards and place them at the table, (player 2 covers)
        for (int i = 0; i < 4; i++) {
            cards[i] = deck.pop();
            bool isCovered = false;
            if (i == 2) isCovered = true;
            table.placeCard(cards[i], i, isCovered);
        }
        int winner = table.calculateWinner(); //calculate winner and does nothing

        while (pGraphicManager->checkWindowOpen()) {

            // Check if the user intends to close the window
            pGraphicManager->checkWindowClose();

            //Clear the window
            pGraphicManager->clearWindow();

            //Draw
            trucoGameView.drawElementsOnTheWindow(pGraphicManager, firstTimeFlag, mouseState->getMousePosView(), texturePathToMainPlayerCards, texturePathToturnedFaceUpCard);
            //mainMenuState->render();

            //Update Mouse
            mouseState->updateMousePosition();


            pGraphicManager->showElements();
        }
    }
}