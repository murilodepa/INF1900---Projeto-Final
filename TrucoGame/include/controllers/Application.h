#pragma once

// Views
#include "../views/GraphicManager.h"
#include "../views/trucoGameView/TrucoGameView.h"

namespace TrucoGame {

    class Application {
    private:
        static View::GraphicManager* pGraphicManager;
        TrucoGame::View::TrucoGameView trucoGameView;

        void initialize();
    public:
        Application();
        ~Application();
        void run();
    };
}