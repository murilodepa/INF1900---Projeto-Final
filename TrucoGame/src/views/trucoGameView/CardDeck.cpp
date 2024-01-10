#include "../../../include/views/trucoGameView/CardDeck.h"

TrucoGame::View::CardDeck::CardDeck(size_t numPlayer, size_t quantityOfCardsInHands, Vector2f& initialDeckPositionVector2f)
{
    initializeCardDeck(numPlayer, quantityOfCardsInHands, initialDeckPositionVector2f);
}

TrucoGame::View::CardDeck::~CardDeck()
{

}

Texture TrucoGame::View::CardDeck::getCardTexture()
{
    return this->cardTexture;
}

void TrucoGame::View::CardDeck::setCardTexture(Card& card)
{
    if (card.rank == CardRank::Back) {
        this->cardTexture = UtilsView::loadTexture(CARD_BACK_TEXTURE_PATH);
    }
    else {
        // TODO
    }
}

TrucoGame::View::CardView* TrucoGame::View::CardDeck::getCardTurnedFaceUp()
{
    return cardTurnedFaceUp;
}

TrucoGame::View::CardView* TrucoGame::View::CardDeck::getDeck()
{
    return deck;
}

size_t TrucoGame::View::CardDeck::getQuantityOfCards()
{
    return quantityOfCards;
}

void TrucoGame::View::CardDeck::initializeCardDeck(size_t numPlayer, size_t quantityOfCardsInHands, Vector2f& initialDeckPositionVector2f)
{
    cardsInHands = UtilsView::initializeMatrix<CardView>(numPlayer, quantityOfCardsInHands);
    Card card;
    card.rank = CardRank::Back;
    setCardTexture(card);

    quantityOfCards = 0;

    // Initialize players' cards
    for (size_t player = 0; player < numPlayer; player++) {
        for (size_t card = 0; card < quantityOfCardsInHands; card++) {
            cardsInHands[player][card] = CardView(initialDeckPositionVector2f);
            cardsInHands[player][card].setTexture(cardTexture);
            quantityOfCards++;
        }
    }

    cardTurnedFaceUp = new CardView(initialDeckPositionVector2f); 
    cardTurnedFaceUp->setTexture(cardTexture);
    quantityOfCards++;

    deck = new CardView(initialDeckPositionVector2f);
    deck->setTexture(cardTexture);
    quantityOfCards++;
}
