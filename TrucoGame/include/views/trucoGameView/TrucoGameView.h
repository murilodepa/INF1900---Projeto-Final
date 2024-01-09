#ifndef TRUCO_GAME_VIEW_H
#define TRUCO_GAME_VIEW_H

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
            TableView tableView;

            void initialize();

        public:
            TrucoGameView(Vector2f windowSize);
            ~TrucoGameView();
            void drawElementsOnTheWindow(GraphicManager* pGraphicManager, std::shared_ptr<bool> firstTimeFlag);
        };
    }
}

#endif // TRUCO_GAME_VIEW_H