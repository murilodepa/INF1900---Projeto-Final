#include "../../include/controllers/Application.h"
#include "../../include/views/trucoGameView/Animator.h"
#include "../../include/views/UtilsView.h"
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
        float initialDeckPosition = (0.1 * windowSize.x);
        return TrucoGameView(windowSize, windowSize.y / 5000, Vector2f(initialDeckPosition, initialDeckPosition));
        }()),
        mainMenuState((pGraphicManager != nullptr) ? std::make_unique<TrucoGame::View::MainMenuState>(pGraphicManager->getWindow()) : nullptr)
    {
        if (pGraphicManager == nullptr || mainMenuState == nullptr) {
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
        
        while (pGraphicManager->checkWindowOpen()) {

            // Check if the user intends to close the window
            pGraphicManager->checkWindowClose();

            //Clear the window
            pGraphicManager->clearWindow();

            //Draw
            trucoGameView.drawElementsOnTheWindow(pGraphicManager, firstTimeFlag);
            mainMenuState->render();

            //Update Mouse
            mainMenuState->update();

            pGraphicManager->showElements();
        }
    }
}