#ifndef CARD_BUTTON_H
#define CARD_BUTTON_H

#include "../../../include/views/ButtonBase.h"
#define CARD_BACK_TEXTURE_PATH "../../../../TrucoGame/resources/images/cards/cardBack.png"

class CardButton : public ButtonBase {

private:
    Sprite* card;
    bool areCardsInTheHandsOfThePlayer;
    Vector2f discardOnTheTablePosition;
    float animationSpeed;
    Texture* cardTexture;

protected:
    void onHover();
    void onPressLeft();
    void onPressRight();
    void onIdle();

public:
    CardButton(float x, float y, float width, float height, Color hoverColor, Sprite* card, Vector2f& windowSize, float animationSpeed, Vector2f& discardOnTheTablePosition, Texture* cardTexture);
    ~CardButton();

    bool getAreCardsInTheHandsOfThePlayer();
    void setAreCardsInTheHandsOfThePlayer(bool areCardsInTheHandsOfThePlayer);
};

#endif // CARD_BUTTON_H
