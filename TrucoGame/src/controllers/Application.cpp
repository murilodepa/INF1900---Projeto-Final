#include "../../include/controllers/Application.h"
#include "../../include/views/trucoGameView/Animator.h"
#include "../../include/views/UtilsView.h"
#include <thread>
#include <iostream>

using namespace TrucoGame::View;

namespace TrucoGame {

    GraphicManager* Application::pGraphicManager = GraphicManager::getGraphicManager();

    Application::Application() : 
        trucoGameView((pGraphicManager != nullptr) ? pGraphicManager->getWindowSize() : Vector2f(SCREEN_X, SCREEN_Y)),
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