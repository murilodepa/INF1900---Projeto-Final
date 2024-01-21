#pragma once 
#include "Card.h"

namespace TrucoGame {
	namespace Models {
		struct PlayedCard {
			int playerId;
			Card* card;
		};

		class Table
		{
		public:
			Table();
			Card* turnedCard = nullptr;
			void PlaceCard(Card* card, int playerId);
			int CalculateWinner();
			Card* GetAllCards();
		private:
			PlayedCard playedCards[4];
			int playedCardIndex = 0;
			int GetCardActualValue(Card* card);
		};
	}
}
