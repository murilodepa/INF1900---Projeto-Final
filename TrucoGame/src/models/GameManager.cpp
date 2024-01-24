#include "../../include/models/GameManager.h"

namespace TrucoGame {
    namespace Models {
        void GameManager::playCard(int playerId, int cardIndex, bool isCovered)
        {
            Card* card = players[playerId].hand[cardIndex];
            table.PlaceCard(card, playerId, isCovered);
        }
    }
}