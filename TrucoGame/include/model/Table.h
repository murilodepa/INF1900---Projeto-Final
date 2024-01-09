#pragma once 
#include "Card.h"

namespace TrucoGame {
	namespace Model {
		struct PlayedCard {
			int playerId;
			Card card;
		};

		class Table
		{
		public:
			Card turnedCard;
			void PlaceCard(Card card, int playerId);
			int CalculateWinner();
			Card* GetAllCards();
		private:
			PlayedCard playedCards[4];
			int playedCardIndex = 0;
			bool IsManilha(Card card);
		};
	}
}
