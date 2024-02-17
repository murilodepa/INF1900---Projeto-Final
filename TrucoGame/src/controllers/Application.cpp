#include "../../include/controllers/Application.h"
#include "../../include/views/trucoGameView/Animator.h"
#include "../../include/views/utils/UtilsView.h"
#include <thread>
#include <iostream>
#include "../../include/models/Deck.h"
#include "../../include/models/Player.h"
#include "../../include/models/Table.h"
#include "../../include/models/Card.h"
#include "../../include/models/Score.h"

using namespace TrucoGame::View;
using namespace TrucoGame::Models;

namespace TrucoGame {

    GraphicManager* TrucoGame::Controller::Application::pGraphicManager = GraphicManager::getGraphicManager();

    TrucoGame::Controller::Application::Application(std::string ip) :
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

        return TrucoGameView(windowSize, cardScale, Vector2f(initialDeckPosition, initialDeckPosition), { "Jogador 1", "Jogador 2", "Jogador 3", "Jogador 4" });
        }()),
        mouseState((pGraphicManager != nullptr) ? std::make_unique<TrucoGame::View::MouseState>(pGraphicManager->getWindow()) : nullptr),
        gMController(&trucoGameView, &clientGameManager)
    {
        if (pGraphicManager == nullptr || mouseState == nullptr) {
            std::cout << "ERROR::TrucoGame::Application - Failed to create GraphicManager." << std::endl;
            exit(1);
        }
        clientGameManager.Start(ip);
    }

    TrucoGame::Controller::Application::~Application() {

    }

    void TrucoGame::Controller::Application::drawGameScreen()
    {
        /*
        std::shared_ptr<bool> firstTimeFlag = std::make_shared<bool>(true);
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

        trucoGameView.setTexturePathToMainPlayerCards(texturePathToMainPlayerCards);


        cardStruct.rank = CardRank::Ace;
        cardStruct.suit = CardSuit::Clubs;
        std::string texturePathToturnedFaceUpCard = UtilsView::findTexturePathByNumberAndSuit(cardStruct);
        trucoGameView.setTexturePathToturnedFaceUpCard(texturePathToturnedFaceUpCard);
        
        */
        while (pGraphicManager->checkWindowOpen()) {

            // Check if the user intends to close the window
            pGraphicManager->checkWindowClose();

            //Clear the window
            pGraphicManager->clearWindow();

            //Draw
            trucoGameView.drawElementsOnTheWindow(pGraphicManager, mouseState->getMousePosView());
            //mainMenuState->render();

            //Update Mouse
            mouseState->updateMousePosition();


            pGraphicManager->showElements();
        }
    }
}