#include "../../../include/views/trucoGameView/CardButton.h"
#include <thread>
#include "../../../include/views/trucoGameView/Animator.h"

void CardButton::onPress() {
    if (areCardsInTheHandsOfThePlayer) {
        areCardsInTheHandsOfThePlayer = false;
        std::thread* animationThread;
        
        animationThread = new std::thread(&TrucoGame::View::Animator::moveAndRotateSpriteTo,
            std::ref(*card),
            discardOnTheTablePosition,
            35.0f,
            animationSpeed);

        animationThread->detach();

        delete animationThread;
    }
}

void CardButton::onHover() {
    this->setOutlineThickness(4);
}

void CardButton::onIdle() {
    this->setOutlineThickness(0);
}

CardButton::CardButton(float x, float y, float width, float height, Color hoverColor, Sprite* card, Vector2f& windowSize, float animationSpeed) :
    ButtonBase(x, y, width, height, hoverColor)
{
    this->setFillColor(Color::Transparent);
    this->setOutlineColor(Color::Transparent);
    this->setOutlineColor(hoverColor);

    areCardsInTheHandsOfThePlayer = false;
    this->card = card;
    discardOnTheTablePosition = Vector2f(0.70f * windowSize.x, 0.63f * windowSize.y);
    this->animationSpeed = animationSpeed;
}

CardButton::~CardButton()
{
}

bool CardButton::getAreCardsInTheHandsOfThePlayer() {
    return areCardsInTheHandsOfThePlayer;
}

void CardButton::setAreCardsInTheHandsOfThePlayer(bool areCardsInTheHandsOfThePlayer) {
    this->areCardsInTheHandsOfThePlayer = areCardsInTheHandsOfThePlayer;
}