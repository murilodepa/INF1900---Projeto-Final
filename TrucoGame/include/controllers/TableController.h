#pragma once

// Views
#include "../views/GraphicManager.h"

using namespace TrucoGame::View;

namespace TrucoGame {

    class TableController {
    private:
        static View::GraphicManager* pGraphicManager;
        //CardView cardView;
        //PlayerView playerView;

    public:
        TableController();
        ~TableController();
    };
}