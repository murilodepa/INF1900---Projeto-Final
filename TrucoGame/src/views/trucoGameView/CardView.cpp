#include "../../../include/views/trucoGameView/CardView.h"
#include "../../../include/views/UtilsView.h"

#define CARD_BACK_TEXTURE_PATH "../../../../TrucoGame/resources/images/cards/cardBack.png"
#define INITIAL_DECK_QUANTITY 14

Sprite** initializeMatrix(int rows, int columns) {
	Sprite** matrix = new Sprite * [rows];
	for (int i = 0; i < rows; i++) {
		matrix[i] = new Sprite[columns];
		for (int j = 0; j < columns; j++) {
			matrix[i][j] = Sprite();
		}
	}
	return matrix;
}

void TrucoGame::View::CardView::initialize(Vector2u initialDeckPosition)
{
	setCardBackTexture(CARD_BACK_TEXTURE_PATH);
	cardTurnedFaceUp.setTexture(cardBackTexture);
	deck.setTexture(cardBackTexture); 

	setCardScale(0.4f);
	setDeckRotation(35.0f);

	cardTurnedFaceUp.setScale(cardScale, cardScale);
	deck.setScale(cardScale, cardScale);
	deck.setRotation(deckRotation);

	setInitialDeckQuantity(INITIAL_DECK_QUANTITY);

	initializeInitialDeck(initialDeckPosition);
	initializePlayerHandsCards();
}

void TrucoGame::View::CardView::initializeInitialDeck(Vector2u initialDeckPosition)
{
	initialDeck.resize(initialDeckQuantity);
	for (size_t i = 0; i < initialDeck.size(); ++i) {
		initialDeck[i].setTexture(cardBackTexture);
		initialDeck[i].setScale(cardScale, cardScale);
		initialDeck[i].setPosition(initialDeckPosition.x, initialDeckPosition.y);
	}
}

void TrucoGame::View::CardView::initializePlayerHandsCards()
{
/*	playerHandsCards = UtilsView::initializeMatrix<Sprite>(numPlayers, cardsInHand);

	for (int player = 0; player < numPlayers; player++) {
		for (int card = 0; card < cardsInHand; card++) {
			playerHandsCards[player][card].setTexture(cardBackTexture);

			// Define a escala inicial para 0.4 (40% do tamanho original)
			playerHandsCards[player][card].setScale(cardScale, cardScale);

			// Rotacione as cartas do oponente
			if (player % 2 != 0) {
				playerHandsCards[player][card].setRotation(90.0f);
			}
		}
	}
	*/
}

TrucoGame::View::CardView::CardView(int numPlayers, int cardsInHand, Vector2u initialDeckPosition)
{
	setNumPlayers(numPlayers);
	playerHandsCards = UtilsView::initializeMatrix<Sprite>(numPlayers, cardsInHand);
	initialize(initialDeckPosition);
 }

TrucoGame::View::CardView::~CardView()
{
	//UtilsView::freeMatrix(playerHandsCards, numPlayers);
}

Texture TrucoGame::View::CardView::getCardBackTexture()
{
	return cardBackTexture;
}

void TrucoGame::View::CardView::setCardBackTexture(const std::string& texturePath)
{
	this->cardBackTexture = UtilsView::loadTexture(texturePath);
}


Texture TrucoGame::View::CardView::getCardFrontTexture()
{
	return cardFrontTexture;
}

void TrucoGame::View::CardView::setCardFrontTexture(const std::string& texturePath)
{
	this->cardFrontTexture =  UtilsView::loadTexture(texturePath);
}

Sprite TrucoGame::View::CardView::getCardTurnedFaceUp()
{
	return cardTurnedFaceUp;
}

void TrucoGame::View::CardView::setCardTurnedFaceUp(Sprite cardTurnedFaceUp)
{
	this->cardTurnedFaceUp = cardTurnedFaceUp;
}

Sprite TrucoGame::View::CardView::getDeck()
{
	return deck;
}

void TrucoGame::View::CardView::setDeck(Sprite deck)
{
	this->deck = deck;
}

std::vector<Sprite> TrucoGame::View::CardView::getInitialDeck()
{
	return initialDeck;
}

float TrucoGame::View::CardView::getCardScale()
{
	return cardScale;
}

void TrucoGame::View::CardView::setCardScale(float cardScale)
{
	this->cardScale = cardScale;
}

float TrucoGame::View::CardView::getDeckRotation()
{
	return deckRotation;
}

void TrucoGame::View::CardView::setDeckRotation(float deckRotation)
{
	this->deckRotation = deckRotation;
}

int TrucoGame::View::CardView::getInitialDeckQuantity()
{
	return initialDeckQuantity;
}

void TrucoGame::View::CardView::setInitialDeckQuantity(int initialDeckQuantity)
{
	this->initialDeckQuantity = initialDeckQuantity;
}

Vector2f TrucoGame::View::CardView::getCardPositionInHand(size_t player, size_t card)
{
	return playerHandsCards[player][card].getPosition();
}

void TrucoGame::View::CardView::setNumPlayers(int numPlayers)
{
	this->numPlayers = numPlayers;
}

void TrucoGame::View::CardView::setCardsInHand(int cardsInHand)
{
	this->cardsInHand = cardsInHand;
}

void TrucoGame::View::CardView::setCardPositionsInPlayerHands(Vector2f** cardPositionsOnTable)
{
	for (int player = 0; player < numPlayers; player++) {
		for (int card = 0; card < cardsInHand; card++) {
			playerHandsCards[player][card].setPosition(cardPositionsOnTable[player][card]);
		}
	}
}

float TrucoGame::View::CardView::getCardWidth()
{
	if (!initialDeck.empty()) {
		return initialDeck[0].getGlobalBounds().width;
	}
}

float TrucoGame::View::CardView::getCardHeight()
{
	if (!initialDeck.empty()) {
		return initialDeck[0].getGlobalBounds().height;
	}
}

float TrucoGame::View::CardView::getHalfCardWidth()
{
	return getCardWidth() / 2;
}
