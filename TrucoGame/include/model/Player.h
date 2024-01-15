#pragma once 
#include "Card.h"
#include <string>

namespace TrucoGame {
	namespace Model {

		class Player
		{
		private:
			std::string playerName;
			int playerId;
			Card hand[3];
		};
	}
}
