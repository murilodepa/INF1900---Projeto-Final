#include "../../../include/views/trucoGameView/TableView.h"
#include "../../../include/views/UtilsView.h"
#include <thread>
#include "../../../include/views/trucoGameView/Animator.h"

#define TABLE_TEXTURE_PATH "../../../../TrucoGame/resources/images/table/tablecloth_texture4.png"


void TrucoGame::View::TableView::initialize(Vector2f windowSize)
{
	setTableTexture(TABLE_TEXTURE_PATH);
	tableCloth.setTexture(tableTexture);
	setTableClothScale(windowSize, tableTexture.getSize());
	if (cardDeck.cardsInHands != nullptr) {
		setCardPositionsOnTheTable(windowSize.x, windowSize.y, cardDeck.cardsInHands[0][0].getCardWidth(), cardDeck.cardsInHands[0][0].getCardHeight(), CARDS_SPACING, TABLE_AND_CARDS_SPACING);
	}
}

void TrucoGame::View::TableView::setCardPositionsOnTheTable(float screenWidth, float screenHeight, float cardWidth, float cardHeight, float cardsSpacing, float cardAndTableSpacing) {

	cardPositionsInPlayerHands = UtilsView::initializeMatrix<Vector2f>(NUM_PLAYERS, CARDS_IN_HAND);

	float halfScreenWidth = screenWidth / 2;
	float halfScreenHeight = screenHeight / 2;
	float halfCardWidth = cardWidth / 2;

	cardPositionsInPlayerHands[0][0] = Vector2f(halfScreenWidth - halfCardWidth - cardsSpacing - cardWidth, cardAndTableSpacing);
	cardPositionsInPlayerHands[0][1] = Vector2f(halfScreenWidth - halfCardWidth, cardAndTableSpacing);
	cardPositionsInPlayerHands[0][2] = Vector2f(halfScreenWidth + halfCardWidth + cardsSpacing, cardAndTableSpacing);

	cardPositionsInPlayerHands[1][0] = Vector2f(cardHeight + cardAndTableSpacing, halfScreenHeight - halfCardWidth - cardsSpacing - cardWidth);
	cardPositionsInPlayerHands[1][1] = Vector2f(cardHeight + cardAndTableSpacing, halfScreenHeight - halfCardWidth);
	cardPositionsInPlayerHands[1][2] = Vector2f(cardHeight + cardAndTableSpacing, halfScreenHeight + halfCardWidth + cardsSpacing);

	cardPositionsInPlayerHands[2][0] = Vector2f(halfScreenWidth - halfCardWidth - cardsSpacing - cardWidth, screenHeight - cardAndTableSpacing - cardHeight);
	cardPositionsInPlayerHands[2][1] = Vector2f(halfScreenWidth - halfCardWidth, screenHeight - cardAndTableSpacing - cardHeight);
	cardPositionsInPlayerHands[2][2] = Vector2f(halfScreenWidth + halfCardWidth + cardsSpacing, screenHeight - cardAndTableSpacing - cardHeight);

	cardPositionsInPlayerHands[3][0] = Vector2f(screenWidth - cardAndTableSpacing, halfScreenHeight - halfCardWidth - cardsSpacing - cardWidth);
	cardPositionsInPlayerHands[3][1] = Vector2f(screenWidth - cardAndTableSpacing, halfScreenHeight - halfCardWidth);
	cardPositionsInPlayerHands[3][2] = Vector2f(screenWidth - cardAndTableSpacing, halfScreenHeight + halfCardWidth + cardsSpacing);

	//std::ref(initialDeck[cardCount+1]), sf::Vector2f(cardTurnedFaceUp.getPosition().x+cardWidth, cardTurnedFaceUp.getPosition().y), deck.getPosition(), 35.0f, 15.0f);

	cardTurnedFaceUpAndDeck.cardTurnedFaceUpPosition = Vector2f(halfScreenWidth - halfCardWidth + cardWidth, halfScreenHeight - halfCardWidth);
	cardTurnedFaceUpAndDeck.deckPosition = Vector2f(halfScreenWidth + 20, halfScreenHeight - halfCardWidth - 20);
	cardTurnedFaceUpAndDeck.deckRotation = 35.0f;
}

TrucoGame::View::TableView::TableView(Vector2f windowSize) :
	pGraphicManager(pGraphicManager->getGraphicManager()),
	cardDeck(NUM_PLAYERS, CARDS_IN_HAND, InitialDeckPositionVector2f(200.0f, 200.0f))
{
	initialize(windowSize);
}

TrucoGame::View::TableView::~TableView()
{
	//UtilsView::freeMatrix(cardPositionsInPlayerHands, NUM_PLAYERS);
}

void TrucoGame::View::TableView::setTableTexture(const std::string& texturePath)
{
	this->tableTexture = UtilsView::loadTexture(texturePath);
}

Sprite TrucoGame::View::TableView::getTableCloth()
{
	return this->tableCloth;
}

void TrucoGame::View::TableView::setTableClothScale(Vector2f windowSize, Vector2u textureSize)
{
	this->tableCloth.setScale(windowSize.x / textureSize.x, windowSize.y / textureSize.y);
}

void TrucoGame::View::TableView::drawElementsOnTheTable()
{
	for (size_t player = 0; player < NUM_PLAYERS; player++) {
		for (size_t card = 0; card < CARDS_IN_HAND; card++) {
			pGraphicManager->drawElement(cardDeck.cardsInHands[player][card]);
		}
	}
	pGraphicManager->drawElement(*cardDeck.getCardTurnedFaceUp());
	pGraphicManager->drawElement(*cardDeck.getDeck());
}

void TrucoGame::View::TableView::distributeCardsAndFlip()
{
	size_t quantityOfCards = cardDeck.getQuantityOfCards() - 1;
	float speed = 15.0f;
	std::vector<std::thread*> animationThreads;

	for (size_t player = 0; player < NUM_PLAYERS; player++) {
		for (size_t card = 0; card < CARDS_IN_HAND; card++) {
			if (player % 2 == 0) {
				animationThreads.push_back(new std::thread(&TrucoGame::View::Animator::moveSpriteTo, std::ref(cardDeck.cardsInHands[player][card]), cardPositionsInPlayerHands[player][card], speed));
			}
			else {
				animationThreads.push_back(new std::thread(&TrucoGame::View::Animator::moveAndRotateSpriteTo, std::ref(cardDeck.cardsInHands[player][card]), cardPositionsInPlayerHands[player][card], 90.0f, speed));
			}
		}
	}

	animationThreads.push_back(new std::thread(&TrucoGame::View::Animator::animationWithCardTurnedFaceUpAndInitialDeck, 
		std::ref(*cardDeck.getCardTurnedFaceUp()), std::ref(*cardDeck.getDeck()), cardTurnedFaceUpAndDeck.cardTurnedFaceUpPosition, cardTurnedFaceUpAndDeck.deckPosition, cardTurnedFaceUpAndDeck.deckRotation, speed));

		//threads[threadCount] = std::thread(&TrucoGame::View::Animator::animationWithCardTurnedFaceUpAndInitialDeck, std::ref(initialDeck[cardCount]), std::ref(initialDeck[cardCount + 1]), sf::Vector2f(cardTurnedFaceUp.getPosition().x + cardWidth, cardTurnedFaceUp.getPosition().y), deck.getPosition(), 35.0f, 15.0f);
		//cardCount += 2;

	//	threads[threadCount] = std::thread(&TrucoGame::View::Animator::animationWithCardTurnedFaceUpAndInitialDeck, cardDeck.getCardTurnedFaceUp(), cardDeck.getDeck(), nds[player][card], 90.0f, 15.0f);

		//threads[threadCount] = std::thread(&TrucoGame::View::Animator::animationWithCardTurnedFaceUpAndInitialDeck, std::ref(initialDeck[cardCount]), std::ref(initialDeck[cardCount + 1]), sf::Vector2f(cardTurnedFaceUp.getPosition().x + cardWidth, cardTurnedFaceUp.getPosition().y), deck.getPosition(), 35.0f, 15.0f);
		//cardCount += 2;

		for (std::thread* t : animationThreads) {
			t->detach();
			delete t;  // Libera a memória alocada para a thread
		}
}







// std::thread animationThread1(&TrucoGame::View::Animator::moveSpriteTo, std::ref(cardDeck.cardsInHands[0][0]), Vector2f(500.0f, 500.0f), 15.0f);
// animationThread1.detach();
