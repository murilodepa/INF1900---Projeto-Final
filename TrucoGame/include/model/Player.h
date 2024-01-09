#pragma once 
#include "Card.h"

namespace TrucoGame {
	namespace Model {

		class Player
		{
		private:
			int playerId;
			Card hand[3];
		};
	}
}
