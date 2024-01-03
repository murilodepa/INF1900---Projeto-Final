#include "../../../include/views/trucoGameView/CardView.h"

Sprite** initializeMatrix(int rows, int columns) {
	Sprite** matrix = new Sprite * [rows];
	for (int i = 0; i < rows; i++) {
		matrix[i] = new Sprite[columns];
		for (int j = 0; j < columns; j++) {
			// Assuming Sprite has a default constructor
			matrix[i][j] = Sprite();
		}
	}
	return matrix;
}

void freeMatrix(Sprite** matrix, int rows) {
	for (int i = 0; i < rows; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}

void TrucoGame::View::CardView::initialize()
{
	setCardBackTexture("../../../../TrucoGame/resources/images/cards/cardBack.png");
	cardTurnedFaceUp.setTexture(cardBackTexture);
	deck.setTexture(cardBackTexture);

	setCardScale(0.4f);
	setDeckRotation(35.0f);

	cardTurnedFaceUp.setScale(cardScale, cardScale);
	deck.setScale(cardScale, cardScale);
	deck.setRotation(deckRotation);

	setInitialDeckQuantity(14);
	setInitialDeckPosition(Vector2u(200, 200));

	initializeInitialDeck();
	initializePlayerHandsCards();
}

void TrucoGame::View::CardView::initializeInitialDeck()
{
	for (int i = 0; i < initialDeckQuantity; i++) {
		initialDeck[i].setTexture(cardBackTexture);
		initialDeck[i].setScale(cardScale, cardScale);
		initialDeck[i].setPosition(initialDeckPosition.x, initialDeckPosition.y);
	}
}

void TrucoGame::View::CardView::initializePlayerHandsCards()
{
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
}

TrucoGame::View::CardView::CardView(int numPlayers, int cardsInHand)
{
	setNumPlayers(numPlayers);
	playerHandsCards = initializeMatrix(numPlayers, cardsInHand);
	initialize();
}

TrucoGame::View::CardView::~CardView()
{
	freeMatrix(playerHandsCards, numPlayers);
}

Texture TrucoGame::View::CardView::getCardBackTexture()
{
	return cardBackTexture;
}

void TrucoGame::View::CardView::setCardBackTexture(const std::string& texturePath)
{
	this->cardBackTexture = utilsView->loadTexture(texturePath);
}


Texture TrucoGame::View::CardView::getCardFrontTexture()
{
	return cardFrontTexture;
}

void TrucoGame::View::CardView::setCardFrontTexture(const std::string& texturePath)
{
	this->cardFrontTexture = utilsView->loadTexture(texturePath);
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

void TrucoGame::View::CardView::setInitialDeck(std::vector<Sprite> initialDeck)
{
	this->initialDeck = initialDeck;
}

Vector2u TrucoGame::View::CardView::getInitialDeckPosition()
{
	return initialDeckPosition;
}

void TrucoGame::View::CardView::setInitialDeckPosition(Vector2u position)
{
	this->initialDeckPosition = position;
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

void TrucoGame::View::CardView::setNumPlayers(int numPlayers)
{
	this->numPlayers = numPlayers;
}

void TrucoGame::View::CardView::setCardsInHand(int cardsInHand)
{
	this->cardsInHand = cardsInHand;
}

float TrucoGame::View::CardView::getCardWidth()
{
	return playerHandsCards[0][0].getGlobalBounds().width;
}

float TrucoGame::View::CardView::getCardHeight()
{
	return playerHandsCards[0][0].getGlobalBounds().height;
}

float TrucoGame::View::CardView::getHalfCard()
{
	return getCardWidth() / 2;
}
