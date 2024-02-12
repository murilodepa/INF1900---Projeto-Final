#include "../../../include/views/trucoGameView/CardButton.h"
#include <thread>
#include "../../../include/views/trucoGameView/Animator.h"

void CardButton::onPressLeft() {
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

void CardButton::onPressRight() {
    std::thread* animationThread;

    //void Animator::flipCard(Sprite & card, float duration, Texture * texture, const std::string & newTexturePath, const float cardScale, bool flipHorizontally)
    //flipCard(sprite, 1.5f, texture, newTexturePath, cardScale, true);

    animationThread = new std::thread(&TrucoGame::View::Animator::flipCard,
        std::ref(*card),
        15.f,
        cardTexture,
        CARD_BACK_TEXTURE_PATH,
        card->getScale().x,
        true);

    animationThread->detach();

    delete animationThread;
}

void CardButton::onHover() {
    this->setOutlineThickness(4);
}

void CardButton::onIdle() {
    this->setOutlineThickness(0);
}

CardButton::CardButton(float x, float y, float width, float height, Color hoverColor, Sprite* card, Vector2f& windowSize, float animationSpeed, Vector2f& discardOnTheTablePosition, Texture* cardTexture) :
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

CardButton::~CardButton()
{
}

bool CardButton::getAreCardsInTheHandsOfThePlayer() {
    return areCardsInTheHandsOfThePlayer;
}

void CardButton::setAreCardsInTheHandsOfThePlayer(bool areCardsInTheHandsOfThePlayer) {
    this->areCardsInTheHandsOfThePlayer = areCardsInTheHandsOfThePlayer;
}