#ifndef CARD_BUTTON_H
#define CARD_BUTTON_H

#include "../../../include/views/ButtonBase.h"

class CardButton : public ButtonBase {

private:
    Sprite* card;
    bool areCardsInTheHandsOfThePlayer;
    Vector2f discardOnTheTablePosition;
    float animationSpeed;

protected:
    void onHover();
    void onPress();
    void onIdle();

public:
    CardButton(float x, float y, float width, float height, Color hoverColor, Sprite* card, Vector2f& windowSize, float animationSpeed);
    ~CardButton();

    bool getAreCardsInTheHandsOfThePlayer();
    void setAreCardsInTheHandsOfThePlayer(bool areCardsInTheHandsOfThePlayer);
};

#endif // CARD_BUTTON_H
