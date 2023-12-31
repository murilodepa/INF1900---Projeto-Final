#include "../../include/controllers/Application.h"

namespace TrucoGame {

    Controller::GraphicManager* Application::pGraphicManager = Controller::GraphicManager::getGraphicManager();

    Application::Application() {
        if (pGraphicManager == nullptr) {
            std::cout << "ERROR::TrucoGame::Application - Failed to create GraphicManager." << std::endl;
            exit(1);
        }
        inicialize();
    }

    Application::~Application() {

    }

    void Application::inicialize() {
        // TODO Define the inicial state of the window
    }

    void Application::run() {

        while (pGraphicManager->checkWindowOpen()) {

            // Check if the user intends to close the window
            pGraphicManager->checkWindowClose();

            //Clear the window
            pGraphicManager->clearWindow();

            // Show everything on the screen
            pGraphicManager->showElements();
        }
    }
}