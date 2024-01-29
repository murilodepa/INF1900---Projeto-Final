#pragma once 
#include "Card.h"
#include <string>
#include <vector>

using namespace std;

namespace TrucoGame {
	namespace Models {

		class Player
		{
		public:
			Player(int id, string name) : playerName(name), playerId(id) {};
			vector<Card*> hand;
			std::vector<Card> GetHand();
			void SetHand(std::vector<Card> shuffleCards);
			void CleanHand();
		private:
			string playerName;
			int playerId;
			std::vector<Card> hand;
		};
	}
}
