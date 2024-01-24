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

			Card* popCardByIndex(int index);
		private:
			string playerName;
			int playerId;
		};
	}
}
