#pragma once

// Define a constant to calculate the card scale
#define CALCULATE_CARD_SCALE 5000.f;

// Define a constant to calculate the initial deck position
#define CALCULATE_INITIAL_DECK_POSITION 0.1f;

// Views
#include "../views/GraphicManager.h"
#include "../views/trucoGameView/TrucoGameView.h"
#include "../views/mouse/MouseState.h"

#include <thread>
#include "GMController.h"

using namespace TrucoGame::View;
using namespace TrucoGame::Models;

namespace TrucoGame {
    namespace Controller {
        class Application {
        private:
            static View::GraphicManager* pGraphicManager;
            TrucoGame::View::TrucoGameView trucoGameView;
            std::unique_ptr<TrucoGame::View::MouseState> mouseState;
            ClientGameManager clientGameManager;
            GMController gMController;

            //static void commonUpdateLoop(TrucoGame::View::GraphicManager& pGraphicManager, std::shared_ptr<bool>& firstTimeFlag, TrucoGame::View::TrucoGameView& pTrucoGameView, std::unique_ptr<TrucoGame::View::MainMenuState>& pMainMenuState);
            void initialize();
        public:
            Application(std::string ip = "127.0.0.1");
            ~Application();
            void drawGameScreen();
        };
    }
}