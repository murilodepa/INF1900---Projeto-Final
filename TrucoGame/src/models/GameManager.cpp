#include "../../include/models/GameManager.h"
#include <iostream>

using namespace std;

namespace TrucoGame {
    namespace Models {

        GameManager::GameManager()
        {
        }

        GameManager::~GameManager()
        {
        }

        void GameManager::cleanTableCards()
        {
            for (Card card : table.getPlayedCards())
            {
                deck.push(card);
            }
            //table.cleanPlayedCards();
        }

        void GameManager::cleanPlayerCards() 
        {
            for (Player& player : players)
            {
                for (Card* card : player.getHand())
                {
                    deck.push(*card);
                }
                player.cleanHand();
            }
        }

        void GameManager::popAllPlayersCards()
        {
            for (Player& player : players) 
            { 
                player.getHand().push_back(deck.pop());
                player.getHand().push_back(deck.pop());
                player.getHand().push_back(deck.pop());
            }
        }
    }
}