#include "../../../include/views/trucoGameView/CardView.h"


#define CARD_SCALE 0.4

TrucoGame::View::CardView::CardView(Vector2f& cardPositionOnTable, Texture& texture)
{
	this->setScale(CARD_SCALE, CARD_SCALE);
	this->setPosition(cardPositionOnTable);
	this->setTexture(texture);
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