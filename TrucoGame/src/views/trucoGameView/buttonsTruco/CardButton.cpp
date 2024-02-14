#include "../../../../include/views/trucoGameView/buttonsTruco/CardButton.h"
#include "../../../../include/views/trucoGameView/Animator.h"
#include "../../../../include/views/utils/MutexView.h"

#include <thread>

void TrucoGame::View::CardButton::discardCardOnTheTable()
{
	if (areCardsInTheHandsOfThePlayer) {
		areCardsInTheHandsOfThePlayer = false;
		std::thread* animationThread;

		animationThread = new std::thread(&TrucoGame::View::Animator::moveAndRotateSpriteTo,
			std::ref(*card),
			discardOnTheTablePosition,
			90.0f,
			animationSpeed);

		animationThread->detach();

		delete animationThread;
	}
}


void TrucoGame::View::CardButton::onPressLeft() 
{
	discardCardOnTheTable();
}

void TrucoGame::View::CardButton::onPressRight()
{
	uIThreadMutex.lock();
	*cardTexture = UtilsView::loadTextureBack();
	uIThreadMutex.unlock();
	discardCardOnTheTable();
}

void TrucoGame::View::CardButton::onHover() {
	this->setOutlineThickness(4);
}

void TrucoGame::View::CardButton::onIdle() {
	this->setOutlineThickness(0);
}

TrucoGame::View::CardButton::CardButton(float x, float y, float width, float height, Color hoverColor, Sprite* card, Vector2f& windowSize, float animationSpeed, Vector2f& discardOnTheTablePosition, Texture* cardTexture) :
	ButtonBase(x, y, width, height, hoverColor)
{
	this->setFillColor(Color::Transparent);
	this->setOutlineColor(Color::Transparent);
	this->setOutlineColor(hoverColor);

	areCardsInTheHandsOfThePlayer = false;
	this->card = card;
	this->discardOnTheTablePosition = discardOnTheTablePosition;
	this->animationSpeed = animationSpeed;
	this->cardTexture = cardTexture;
}

TrucoGame::View::CardButton::~CardButton()
{
	delete cardTexture;
}

bool TrucoGame::View::CardButton::getAreCardsInTheHandsOfThePlayer() {
	return areCardsInTheHandsOfThePlayer;
}

void TrucoGame::View::CardButton::setAreCardsInTheHandsOfThePlayer(bool areCardsInTheHandsOfThePlayer) {
	this->areCardsInTheHandsOfThePlayer = areCardsInTheHandsOfThePlayer;
}