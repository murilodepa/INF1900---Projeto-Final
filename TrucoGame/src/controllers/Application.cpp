#include "../../include/controllers/Application.h"
#include "../../include/views/trucoGameView/Animator.h"
#include "../../include/views/UtilsView.h"
#include <thread>
#include <iostream>
#include "../../include/models/Deck.h"
#include "../../include/models/Player.h"
#include "../../include/models/Table.h"
#include "../../include/models/Card.h"
#include "../../include/views/Button.h"

using namespace TrucoGame::View;
using namespace TrucoGame::Models;

namespace TrucoGame {

    GraphicManager* Application::pGraphicManager = GraphicManager::getGraphicManager();

    Application::Application() : 
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
        return TrucoGameView(windowSize, cardScale, Vector2f(initialDeckPosition, initialDeckPosition));
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
        std::vector<Player> players;
        players.push_back(Player(0, "Laert"));
        players.push_back(Player(1, "Caique"));
        players.push_back(Player(2, "Vitor"));
        players.push_back(Player(3, "Murilo"));

        Table table;
        Deck deck;        
        Models::Card* cards[4];
        table.turnedCard = deck.pop();

        // get 4 cards and place them at the table, (player 2 covers)
        for (int i = 0; i < 4; i++) {
            cards[i] = deck.pop();
            bool isCovered = false;
            if (i == 2) isCovered = true;
            table.PlaceCard(cards[i], i, isCovered);
        }
        int winner = table.CalculateWinner(); //calculate winner and does nothing

        Button *button = new Button(100, 100, 150, 50, Color::Green, Color::Blue, Color::Yellow);

        while (pGraphicManager->checkWindowOpen()) {

            // Check if the user intends to close the window
            pGraphicManager->checkWindowClose();

            //Clear the window
            pGraphicManager->clearWindow();

            //Draw
            trucoGameView.drawElementsOnTheWindow(pGraphicManager, firstTimeFlag, mouseState->getMousePosView());
            //mainMenuState->render();

            //Update Mouse
            mouseState->updateMousePosition();

            button->update(mouseState->getMousePosView());

            pGraphicManager->drawElement(*button);

            pGraphicManager->showElements();
        }
    }
}