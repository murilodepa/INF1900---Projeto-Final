#include "../../../include/views/trucoGameView/TableView.h"
#include "../../../include/views/UtilsView.h"
#include <thread>
#include "../../../include/views/trucoGameView/Animator.h"



void TrucoGame::View::TableView::initialize(Vector2f windowSize, Vector2f& initialDeckPositionVector2f, const float cardScale)
{
	setTableTexture(TABLE_TEXTURE_PATH);
	tableCloth.setTexture(tableTexture);
	setTableClothScale(windowSize, tableTexture.getSize());

	setBackCardTexture(CARD_BACK_TEXTURE_PATH);

	setTextureFromPath(CARD_BACK_TEXTURE_PATH);
	
	cardTurnedFaceUp = new CardView(initialDeckPositionVector2f, *texture, cardScale);
	deck = new CardView(initialDeckPositionVector2f, backCardTexture, cardScale);

	deck->setTexture(backCardTexture);
	if (deck != nullptr)
		setDeckPositionOnTheTable(windowSize.x, windowSize.y, deck->getCardWidth());
}

void TrucoGame::View::TableView::setDeckPositionOnTheTable(float screenWidth, float screenHeight, float cardWidth) {

	cardPositionsInPlayerHands = UtilsView::initializeMatrix<Vector2f>(NUM_PLAYERS, CARDS_IN_HAND);

	float halfScreenWidth = screenWidth / 2;
	float halfScreenHeight = screenHeight / 2;
	float halfCardWidth = cardWidth / 2;

	cardTurnedFaceUpAndDeck.cardTurnedFaceUpPosition = Vector2f(halfScreenWidth - halfCardWidth + cardWidth, halfScreenHeight - halfCardWidth);
	cardTurnedFaceUpAndDeck.deckPosition = Vector2f(halfScreenWidth + 20, halfScreenHeight - halfCardWidth - 20);
	cardTurnedFaceUpAndDeck.deckRotation = 35.0f;
}

TrucoGame::View::TableView::TableView(Vector2f& windowSize, Vector2f& initialDeckPositionVector2f, const float cardScale)
{
	initialize(windowSize, initialDeckPositionVector2f, cardScale);
}

TrucoGame::View::TableView::~TableView()
{

}

void TrucoGame::View::TableView::setTableTexture(const std::string& texturePath)
{
	this->tableTexture = UtilsView::loadTexture(texturePath);
}

void TrucoGame::View::TableView::setBackCardTexture(const std::string& texturePath)
{
	this->backCardTexture = UtilsView::loadTexture(texturePath);
}

Sprite TrucoGame::View::TableView::getTableCloth()
{
	return this->tableCloth;
}

void TrucoGame::View::TableView::setTableClothScale(Vector2f& windowSize, Vector2u& textureSize)
{
	this->tableCloth.setScale(windowSize.x / textureSize.x, windowSize.y / textureSize.y);
}

void TrucoGame::View::TableView::drawElementsOnTheTable(GraphicManager* pGraphicManager) const
{
	pGraphicManager->drawElement(*cardTurnedFaceUp);
	pGraphicManager->drawElement(*deck);
}

void TrucoGame::View::TableView::moveDeckAndTurnUpCard(const float cardScale, float speed)
{
	std::string turnedFaceUpPath = "../../../../TrucoGame/resources/images/cards/Clubs/Ace.png";
	//*texture = UtilsView::loadTexture(turnedFaceUpPath);
	std::thread* animationThread = new std::thread(&TrucoGame::View::Animator::animationWithCardTurnedFaceUpAndInitialDeck,
		std::ref(*cardTurnedFaceUp), texture, turnedFaceUpPath, std::ref(*deck), cardTurnedFaceUpAndDeck.cardTurnedFaceUpPosition, cardTurnedFaceUpAndDeck.deckPosition, cardTurnedFaceUpAndDeck.deckRotation, speed, cardScale);
	
	animationThread->detach();
	delete animationThread;
}

void TrucoGame::View::TableView::setTurnedFaceUpCardTexture(std::string& texturePath)
{
	this->turnedFaceUpCardTexture = UtilsView::loadTexture(texturePath);
}

void TrucoGame::View::TableView::setTextureFromPath(const std::string& texturePath)
{
	this->texture = new Texture(UtilsView::loadTexture(texturePath));
}


