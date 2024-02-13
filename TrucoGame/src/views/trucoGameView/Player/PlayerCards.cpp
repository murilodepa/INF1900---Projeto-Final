#include "../../../../include/views/trucoGameView/player/PlayerCards.h"

Texture*** initializeTextureMatrix(size_t rows, size_t columns) {
	Texture*** matrix = new Texture * *[rows];
	for (size_t i = 0; i < rows; i++) {
		matrix[i] = new Texture * [columns];

		for (size_t j = 0; j < columns; j++) {
			matrix[i][j] = new Texture();
		}
	}
	return matrix;
}

void deleteTextuteMatrix(Texture*** matrix, size_t rows, size_t columns) 
{
	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < columns; j++) {
			delete matrix[i][j];
		}
		delete[] matrix[i];
	}
	delete[] matrix;
}

TrucoGame::View::PlayerCards::PlayerCards(size_t numPlayer, size_t quantityOfCardsInHands, Vector2f& initialDeckPositionVector2f, const float cardScale)
{
	this->numPlayers = numPlayer;
	this->quantityOfCardsInHands = quantityOfCardsInHands;
	initializePlayerCards(initialDeckPositionVector2f, cardScale);
}

TrucoGame::View::PlayerCards::~PlayerCards()
{
	deleteTextuteMatrix(cardsTexture, numPlayers, quantityOfCardsInHands);
}

Texture* TrucoGame::View::PlayerCards::getCardTexture(size_t player, size_t cardIndex)
{
	return this->cardsTexture[player][cardIndex];
}

void TrucoGame::View::PlayerCards::setCardTexture(CardStruct& cardStruct, Texture* texture)
{
	if (cardStruct.rank == CardRank::Back) {
		*texture = UtilsView::loadTextureBack();
	}
	else {
		// TODO
	}
}

void TrucoGame::View::PlayerCards::initializePlayerCards(Vector2f& initialDeckPositionVector2f, const float cardScale)
{
	cardsInHands = UtilsView::initializeMatrix<CardView>(numPlayers, quantityOfCardsInHands);
	cardsTexture = initializeTextureMatrix(numPlayers, quantityOfCardsInHands);
	CardStruct cardStruct;
	cardStruct.rank = CardRank::Back;

	// Initialize players' cards
	for (size_t playerIndex = 0; playerIndex < numPlayers; playerIndex++) {
		for (size_t cardIndex = 0; cardIndex < quantityOfCardsInHands; cardIndex++) {
			Texture* cardTexture = cardsTexture[playerIndex][cardIndex];
			setCardTexture(cardStruct, cardTexture);
			cardsInHands[playerIndex][cardIndex] = CardView(initialDeckPositionVector2f, *cardTexture, 0.19f);
		}
	}
}
