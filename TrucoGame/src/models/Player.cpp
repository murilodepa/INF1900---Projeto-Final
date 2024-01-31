#include "../../include/models/Player.h"

namespace TrucoGame {
	namespace Models {
		Card Player::popCardByIndex(int index) 
		{
			Card card = hand[index];
			hand.erase(hand.begin() + index);
			return card;
		}
	}
}