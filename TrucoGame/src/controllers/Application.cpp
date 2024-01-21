#include "../../include/controllers/Application.h"
#include "../../include/views/trucoGameView/Animator.h"
#include "../../include/views/UtilsView.h"
#include <thread>
#include <iostream>
#include "../../include/models/Score.h"

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

        Score score;
        score.increaseStakes();
        int x = score.updateTurnWon(1);
        x = score.updateTurnWon(0);
        x = score.updateTurnWon(0);
        x = score.getStakes();
        x = score.updateRoundWon(1);
        score.resetRound();

        while (pGraphicManager->checkWindowOpen()) {

            // Check if the user intends to close the window
            pGraphicManager->checkWindowClose();

            //Clear the window
            pGraphicManager->clearWindow();

            //Draw
            trucoGameView.drawElementsOnTheWindow(pGraphicManager, firstTimeFlag);

            pGraphicManager->showElements();
        }
    }
}