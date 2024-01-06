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
    setCardPositionsInPlayerHandsOnTable(windowSize.x, windowSize.y, cardView.getCardWidth(), cardView.getCardHeight(), CARDS_SPACING, TABLE_AND_CARDS_SPACING);
}

void TrucoGame::View::TableView::setCardPositionsInPlayerHandsOnTable(float screenWidth, float screenHeight, float cardWidth, float cardHeight, float cardsSpacing, float cardAndTableSpacing){
    /*Vector2f** cardPositionsInPlayerHands = UtilsView::initializeMatrix<Vector2f>(NUM_PLAYERS, CARDS_IN_HAND);

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

    cardView.setCardPositionsInPlayerHands(cardPositionsInPlayerHands);
    */
    //UtilsView::freeMatrix(cardPositionsInPlayerHands, NUM_PLAYERS);
}

TrucoGame::View::TableView::TableView(Vector2f windowSize) : 
    pGraphicManager(pGraphicManager->getGraphicManager()), 
    cardView(NUM_PLAYERS, CARDS_IN_HAND, InitialDeckPositionVector2u(200, 200))
{
	initialize(windowSize);
}

TrucoGame::View::TableView::~TableView()
{
}

Texture TrucoGame::View::TableView::getTableTexture()
{
	return tableTexture;
}

void TrucoGame::View::TableView::setTableTexture(const std::string& texturePath)
{
	this->tableTexture = UtilsView::loadTexture(texturePath);
}

Sprite TrucoGame::View::TableView::getTableCloth()
{
	return this->tableCloth;
}

void TrucoGame::View::TableView::setTableCloth(Sprite tableCloth)
{
	this->tableCloth = tableCloth;
}

void TrucoGame::View::TableView::setTableClothScale(Vector2f windowSize, Vector2u textureSize)
{
	this->tableCloth.setScale(windowSize.x / textureSize.x, windowSize.y / textureSize.y);
}

void TrucoGame::View::TableView::drawElementsOnTheTable()
{   
    for (int card = 0; card < cardView.getInitialDeckQuantity(); card++) {
        pGraphicManager->drawElement(cardView.getInitialDeck()[card]);
    }
}

void TrucoGame::View::TableView::distributeCardsAndFlip() 
{
    /*
    std::vector<std::thread> animationThreads;
    size_t cardCount = 0;;

    auto createThread = [&](auto&& function, auto&&... args) {
        animationThreads.emplace_back(function, std::forward<decltype(args)>(args)...);
        cardCount++;
    };

    std::vector<Sprite> initialDeck = cardView.getInitialDeck();

    
    for (int i = 0; i < 3; i++) {
        createThread(&TrucoGame::View::Animator::moveSpriteTo, std::ref(initialDeck[cardCount]), cardView.getCardPositionInHand(0, i), 15.0f);
        createThread(&TrucoGame::View::Animator::moveSpriteTo, std::ref(initialDeck[cardCount]), cardView.getCardPositionInHand(2, i), 15.0f);
        createThread(&TrucoGame::View::Animator::moveAndRotateSpriteTo, std::ref(initialDeck[cardCount]), cardView.getCardPositionInHand(1, i), 90.0f, 15.0f);
        createThread(&TrucoGame::View::Animator::moveAndRotateSpriteTo, std::ref(initialDeck[cardCount]), cardView.getCardPositionInHand(3, i), 90.0f, 15.0f);
    }

    createThread(&TrucoGame::View::Animator::animationWithCardTurnedFaceUpAndInitialDeck, std::ref(initialDeck[cardCount]), std::ref(initialDeck[cardCount + 1]), sf::Vector2f(cardView.getCardTurnedFaceUp().getPosition().x +cardView.getCardWidth(), cardView.getCardTurnedFaceUp().getPosition().y), cardView.getDeck().getPosition(), 35.0f, 15.0f);
    cardCount++;
    cardCount++;
    
    // Usar .detach() para liberar as threads para execução independente
    for (auto& thread : animationThreads) {
        thread.detach();
    }
    */
}
