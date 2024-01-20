#pragma once 
#include "Card.h"
#include <vector>
#include <string>

namespace TrucoGame {
	namespace Models {

		class Player {
		private:
			std::string playerName;
			int playerId;
			std::vector<Card> hand;
		public:
			Player(std::string name, int id);
			~Player();
			std::vector<Card> GetHand();
			void SetHand(std::vector<Card> shuffleCards);
			void CleanHand();
		};
	}
}
