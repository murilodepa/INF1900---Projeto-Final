#include "..\..\include\models\Player.h"

using namespace std;

namespace TrucoGame {

	namespace Models {
		Card Player::popCardByIndex(int index) 
		{
			Card card = hand[index];
			hand.erase(hand.begin() + index);
			return card;
			return hand;
		}

		void Player::setHand(vector<Card*> shuffleCards)
		{
			hand = shuffleCards;
		}
		
		void Player::cleanHand()
		{
			 getHand().clear();
		}
	}
}