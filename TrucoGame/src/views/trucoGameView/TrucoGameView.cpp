#include "../../../include/views/trucoGameView/TrucoGameView.h"
#include <thread>
#include "../../../include/views/trucoGameView/Animator.h"

void TrucoGame::View::TrucoGameView::initialize()
{
}

TrucoGame::View::TrucoGameView::TrucoGameView() :
	pGraphicManager(pGraphicManager->getGraphicManager()),
	tableView(Vector2f(static_cast<float>(pGraphicManager->getWindowSize().x), static_cast<float>(pGraphicManager->getWindowSize().y)))
{

}


TrucoGame::View::TrucoGameView::~TrucoGameView()
{
}

void TrucoGame::View::TrucoGameView::drawElementsOnTheWindow(bool firstTimeFlag)
{
	pGraphicManager->drawElement(tableView.getTableCloth());
	tableView.drawElementsOnTheTable();
    
    if (firstTimeFlag == true) {
        tableView.distributeCardsAndFlip();
    }
}
