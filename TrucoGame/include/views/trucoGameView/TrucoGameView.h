#pragma once
#include <SFML/Graphics.hpp>
#include "../../../include/views/GraphicManager.h"
#include "../../../include/views/UtilsView.h"
#include "TableView.h"

using namespace sf;


namespace TrucoGame {
    namespace View {
        class TrucoGameView {
        private:
            View::GraphicManager* pGraphicManager;
            TableView tableView;

            void initialize();

        public:
            TrucoGameView();
            ~TrucoGameView();
            void drawElementsOnTheWindow(bool firstTimeFlag);
        };
    }
}
