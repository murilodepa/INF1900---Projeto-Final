#include "../../../../include/views/trucoGameView/Player/PlayerView.h"

void TrucoGame::View::PlayerView::setFontFromPath(const std::string& fontPath)
{
	this->font = UtilsView::loadFont(fontPath);
}

TrucoGame::View::PlayerView::PlayerView(size_t numCardsInHands, const float windowHeight, const std::string& name)
{
	playerName = new TextView(name, CONSTANT_TO_CALCULATE_PLAYER_NAME_CHARACTER_SIZE, windowHeight, NAME_COLOR, sf::Text::Bold);
	playerCards.resize(numCardsInHands);

	float playerNameCharacterSize = windowHeight * CONSTANT_TO_CALCULATE_PLAYER_NAME_CHARACTER_SIZE;
}

TrucoGame::View::PlayerView::~PlayerView()
{
}

void TrucoGame::View::PlayerView::setCardPositions(std::vector<Vector2f> cardPositions)
{
	for (size_t i = 0; i < cardPositions.size(); i++) {
		playerCards[i].setPosition(cardPositions[i]);
	}
}

void TrucoGame::View::PlayerView::setNamePosition(Vector2f namePosition)
{
	playerName->setPosition(namePosition);
}

void TrucoGame::View::PlayerView::setNameRotation(float nameRotation)
{
	playerName->setRotation(nameRotation);
}

TrucoGame::View::TextView TrucoGame::View::PlayerView::getPlayerName() const
{
	return *playerName;
}

Vector2f TrucoGame::View::PlayerView::getCardPosition(size_t cardIndex) const
{
	return playerCards[cardIndex].getPosition();
}