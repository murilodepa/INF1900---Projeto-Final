#include "../../include/models/GameManager.h"

namespace TrucoGame {

    namespace Models {

        GameManager::GameManager()
        {
        }

        GameManager::~GameManager()
        {
            cards.clear();
        }

        void GameManager::CleanPlayerCards() 
        {
            for each (Player player in players)
            {
                for each (Card card in player.GetHand())
                {
                    table.deck.push(card);
                }
                player.CleanHand();
            }
        }

        void GameManager::ShuffleCards() 
        {
            for each (Player player in players)
            {
                player.setHand(table.ShuffleHandCard());
            }
        }
    }
}