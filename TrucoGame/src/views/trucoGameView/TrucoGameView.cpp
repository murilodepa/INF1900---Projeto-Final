#include "../../../include/views/trucoGameView/TrucoGameView.h"

void TrucoGame::View::TrucoGameView::initialize()
{
}

TrucoGame::View::TrucoGameView::TrucoGameView() : pGraphicManager(pGraphicManager->getGraphicManager()), tableView(Vector2f(static_cast<float>(pGraphicManager->getWindowSize().x), static_cast<float>(pGraphicManager->getWindowSize().y)))
{
}

TrucoGame::View::TrucoGameView::~TrucoGameView()
{
}

void TrucoGame::View::TrucoGameView::drawTable()
{
	pGraphicManager->drawElement(tableView.getTableCloth());
}
