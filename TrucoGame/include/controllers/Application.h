#pragma once

//Controllers
#include "../views/Camera.h"
#include "../views/GraphicManager.h"

namespace TrucoGame {

    class Application {
    private:
        static Controller::GraphicManager* pGraphicManager;

        void inicialize();
    public:
        Application();
        ~Application();
        void run();
    };
}