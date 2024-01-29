#pragma once 
#include "Card.h"
#include "Deck.h"

namespace TrucoGame {
	namespace Models {
		struct PlayedCard {
			int playerId;
			Card* card;
			bool isCovered;
		};

		class Table {
		public:
			Table();
			Card* turnedCard = nullptr;
			void PlaceCard(Card* card, int playerId, bool isCovered);
			std::vector<Card> ShuffleHandCard();
			int CalculateWinner();
		private:
			PlayedCard playedCards[4];
			int playedCardIndex = 0;
			int GetCardActualValue(PlayedCard playedCard);
			void CleanTableCards();
		};
	}
}
