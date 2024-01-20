#include "..\..\include\models\Player.h"

namespace TrucoGame {

	namespace Models {

		Player::Player(string name, int id) {
			playerName = name;
			playerId = id;
		}

		Player::~Player()
		{
		}

		std::vector<Card> Player::GetHand()
		{
			return hand;
		}

		void Player::SetHand(std::vector<Card> shuffleCards)
		{
			hand = shuffleCards;
		}
		
		void Player::CleanHand()
		{
			GetHand().clear();
		}
	}
}