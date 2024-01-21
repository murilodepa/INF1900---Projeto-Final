#include "../../include/controllers/Application.h"
#include "../../include/views/trucoGameView/Animator.h"
#include "../../include/views/UtilsView.h"
#include <thread>
#include <iostream>
#include "../../include/models/Deck.h"
#include "../../include/models/Player.h"
#include "../../include/models/Table.h"
#include "../../include/models/Card.h"

using namespace TrucoGame::View;
using namespace TrucoGame::Models;

namespace TrucoGame {

    GraphicManager* Application::pGraphicManager = GraphicManager::getGraphicManager();

    Application::Application() : trucoGameView(pGraphicManager->getWindowSize()) {
        if (pGraphicManager == nullptr) {
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

        while (pGraphicManager->checkWindowOpen()) {

            // Check if the user intends to close the window
            pGraphicManager->checkWindowClose();

            //Clear the window
            pGraphicManager->clearWindow();

            //Draw
            //trucoGameView.drawElementsOnTheWindow(pGraphicManager, firstTimeFlag);

            pGraphicManager->showElements();
        }
    }
}