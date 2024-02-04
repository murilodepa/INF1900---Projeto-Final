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
			Player(string name, int id);
			vector<Card*> &getHand();
			void setHand(vector<Card*> shuffleCards);
			void cleanHand();
		private:
			string playerName;
			int playerId;
			vector<Card*> hand;
		};
	}
}
