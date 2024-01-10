#include "../../../include/views/trucoGameView/TrucoGameView.h"
#include <thread>
#include "../../../include/views/trucoGameView/Animator.h"

void TrucoGame::View::TrucoGameView::initialize()
{
}

TrucoGame::View::TrucoGameView::TrucoGameView(Vector2f windowSize) :
	tableView(Vector2f(static_cast<float>(windowSize.x), static_cast<float>(windowSize.y)))
{

}


TrucoGame::View::TrucoGameView::~TrucoGameView()
{
}

void TrucoGame::View::TrucoGameView::drawElementsOnTheWindow(GraphicManager* pGraphicManager, std::shared_ptr<bool> firstTimeFlag)
{
    if (pGraphicManager) {
        pGraphicManager->drawElement(tableView.getTableCloth());
        tableView.drawElementsOnTheTable();

        if (*firstTimeFlag == true) {
            *firstTimeFlag = false;
             tableView.distributeCardsAndFlip();
        }


    }

}
