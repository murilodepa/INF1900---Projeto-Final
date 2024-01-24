#pragma once 
#include "Card.h"

namespace TrucoGame {
	namespace Models {
		struct PlayedCard {
			int playerId;
			Card* card;
			bool isCovered;
		};

		class Table
		{
		public:
			Table();
			Card* turnedCard = nullptr;
			void PlaceCard(Card* card, int playerId, bool isCovered);
			//Returns: playerId of the winner (0 ~ 3)
			int CalculateWinner();
			Card* GetAllCards();
		private:
			PlayedCard playedCards[4];
			int playedCardIndex = 0;
			int GetCardActualValue(PlayedCard playedCard);
		};
	}
}
