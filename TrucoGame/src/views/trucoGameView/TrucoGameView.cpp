#include "../../../include/views/trucoGameView/TrucoGameView.h"
#include <thread>
#include "../../../include/views/trucoGameView/Animator.h"

void TrucoGame::View::TrucoGameView::initialize()
{
}

TrucoGame::View::TrucoGameView::TrucoGameView(Vector2f windowSize) :
	tableView(Vector2f(static_cast<float>(windowSize.x), static_cast<float>(windowSize.y)))
{
	players.resize(NUM_PLAYERS);

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
        drawScore(pGraphicManager);
    }
}

void TrucoGame::View::TrucoGameView::drawScore(GraphicManager* pGraphicManager)
{
    pGraphicManager->drawElement(scoreView.getScoreRectangle());
    pGraphicManager->drawElement(scoreView.getRectangleDivWidth());
    pGraphicManager->drawElement(scoreView.getRectangleDivHeight());

    for (int i = 0; i < 3; i++) {
       pGraphicManager->drawElement(scoreView.getOurCircles(i));
       pGraphicManager->drawElement(scoreView.getTheirCircles(i));
    }

    pGraphicManager->drawElement(scoreView.getRoundScoreText());
    pGraphicManager->drawElement(scoreView.getWeText());
    pGraphicManager->drawElement(scoreView.getTheyText());
}

void TrucoGame::View::TrucoGameView::setCardPositionsOfThePlayers(float screenWidth, float screenHeight, float cardWidth, float cardHeight, float cardsSpacing, float cardAndTableSpacing) {

	float halfScreenWidth = screenWidth / 2;
	float halfScreenHeight = screenHeight / 2;
	float halfCardWidth = cardWidth / 2;

	std::vector<Vector2f> cardsPositions;

	cardsPositions.push_back(Vector2f(halfScreenWidth - halfCardWidth - cardsSpacing - cardWidth, cardAndTableSpacing));
	cardsPositions.push_back(Vector2f(halfScreenWidth - halfCardWidth, cardAndTableSpacing));
	cardsPositions.push_back(Vector2f(halfScreenWidth + halfCardWidth + cardsSpacing, cardAndTableSpacing));
	players[0].setCardPositions(cardsPositions);

	cardsPositions.clear();

	cardsPositions.push_back(Vector2f(cardHeight + cardAndTableSpacing, halfScreenHeight - halfCardWidth - cardsSpacing - cardWidth));
	cardsPositions.push_back(Vector2f(cardHeight + cardAndTableSpacing, halfScreenHeight - halfCardWidth));
	cardsPositions.push_back(Vector2f(cardHeight + cardAndTableSpacing, halfScreenHeight + halfCardWidth + cardsSpacing));
	players[1].setCardPositions(cardsPositions);

	cardsPositions.clear();

	cardsPositions.push_back(Vector2f(halfScreenWidth - halfCardWidth - cardsSpacing - cardWidth, screenHeight - cardAndTableSpacing - cardHeight));
	cardsPositions.push_back(Vector2f(halfScreenWidth - halfCardWidth, screenHeight - cardAndTableSpacing - cardHeight));
	cardsPositions.push_back(Vector2f(halfScreenWidth + halfCardWidth + cardsSpacing, screenHeight - cardAndTableSpacing - cardHeight));
	players[2].setCardPositions(cardsPositions);

	cardsPositions.clear();

	cardsPositions.push_back(Vector2f(screenWidth - cardAndTableSpacing, halfScreenHeight - halfCardWidth - cardsSpacing - cardWidth));
	cardsPositions.push_back(Vector2f(screenWidth - cardAndTableSpacing, halfScreenHeight - halfCardWidth));
	cardsPositions.push_back(Vector2f(screenWidth - cardAndTableSpacing, halfScreenHeight + halfCardWidth + cardsSpacing));
	players[3].setCardPositions(cardsPositions);
}