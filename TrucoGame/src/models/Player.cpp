#include "..\..\include\models\Player.h"

using namespace std;

namespace TrucoGame {

	namespace Models {

		Player::Player(string name, int id) {
			playerName = name;
			playerId = id;
		}

		vector<Card*> &Player::getHand()
		{
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