#pragma once

// Views
#include "../views/GraphicManager.h"
#include "../views/trucoGameView/TrucoGameView.h"
#include "../views/MainMenuState.h"
#include <thread>
using namespace TrucoGame::View;

namespace TrucoGame {

    class Application {
    private:
        static View::GraphicManager* pGraphicManager;
        TrucoGame::View::TrucoGameView trucoGameView;
        std::unique_ptr<TrucoGame::View::MainMenuState> mainMenuState;

        std::thread updateThread;
        std::thread drawThread;

        void updateThreadFunction();
        void drawThreadFunction();
        
        //static void commonUpdateLoop(TrucoGame::View::GraphicManager& pGraphicManager, std::shared_ptr<bool>& firstTimeFlag, TrucoGame::View::TrucoGameView& pTrucoGameView, std::unique_ptr<TrucoGame::View::MainMenuState>& pMainMenuState);
        void initialize();
    public:
        Application();
        ~Application();
        void commonUpdateLoop(GraphicManager& graphicManager, std::shared_ptr<bool>& firstTimeFlag, TrucoGameView& trucoGameView, MainMenuState* mainMenuState);
        void run();
    };
}