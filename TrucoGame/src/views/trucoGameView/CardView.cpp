#include "../../../include/views/trucoGameView/CardView.h"


//#define CARD_SCALE 0.4

TrucoGame::View::CardView::CardView(Vector2f& cardPositionOnTable, Texture& texture, const float cardScale)
{
	this->setScale(cardScale, cardScale);
	this->setPosition(cardPositionOnTable);
	this->setTexture(texture);
	this->isCardBeingDiscarded = false;
}

TrucoGame::View::CardView::~CardView()
{

}

float TrucoGame::View::CardView::getCardWidth() const
{
	return this->getGlobalBounds().width;
}

float TrucoGame::View::CardView::getCardHeight() const
{
	return this->getGlobalBounds().height;
}

float TrucoGame::View::CardView::getHalfCardWidth() const
{
	return this->getGlobalBounds().width / 2;
}

bool TrucoGame::View::CardView::getIsCardBeingDiscarded()
{
	return isCardBeingDiscarded;
}

void TrucoGame::View::CardView::setIsCardBeingDiscarded(bool isCardBeingDiscarded)
{
	this->isCardBeingDiscarded = isCardBeingDiscarded;
}
