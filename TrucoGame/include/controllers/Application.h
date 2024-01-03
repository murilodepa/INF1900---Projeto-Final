#pragma once

// Views
#include "../views/GraphicManager.h"

namespace TrucoGame {

    class Application {
    private:
        static View::GraphicManager* pGraphicManager;

        void initialize();
    public:
        Application();
        ~Application();
        void run();
    };
}