#include "../../../include/views/trucoGameView/TableView.h"

#define TABLE_TEXTURE_PATH "../../../../TrucoGame/resources/images/table/tablecloth_texture4.png"


void TrucoGame::View::TableView::initialize(Vector2f windowSize)
{
	setTableTexture(TABLE_TEXTURE_PATH);
	tableCloth.setTexture(tableTexture);
	setTableClothScale(windowSize, tableTexture.getSize());
}

TrucoGame::View::TableView::TableView(Vector2f windowSize) : cardView(NUM_PLAYERS, CARDS_IN_HAND)
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
	this->tableTexture = utilsView->loadTexture(texturePath);
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
