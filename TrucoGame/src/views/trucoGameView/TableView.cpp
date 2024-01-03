#include "../../../include/views/trucoGameView/TableView.h"


void TrucoGame::View::TableView::initialize()
{
	setTableTexture("../../../../TrucoGame/resources/images/table/tablecloth_texture4.png");
	setTableTextureSize(tableTexture.getSize());
	tableCloth.setTexture(tableTexture);

}

TrucoGame::View::TableView::TableView()
{
	//initialize();
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

Vector2u TrucoGame::View::TableView::getTableTextureSize()
{
	return tableTexture.getSize();
}

void TrucoGame::View::TableView::setTableTextureSize(Vector2u tableTextureSize)
{
	this->tableTextureSize = tableTextureSize;
}

Sprite TrucoGame::View::TableView::getTableCloth()
{
	return tableCloth;
}

void TrucoGame::View::TableView::setTableCloth(Sprite tableCloth)
{
	this->tableCloth = tableCloth;
}
