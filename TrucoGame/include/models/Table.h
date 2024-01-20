#pragma once 
#include "Card.h"
#include "Deck.h"

namespace TrucoGame {
	namespace Models {
		struct PlayedCard {
			int playerId;
			Card card;
		};

		class Table {
		public:
			Deck deck;
			Card turnedCard;
			std::vector<Card> ShuffleHandCard();
			void PlaceCard(Card card, int playerId);
			int CalculateWinner();
		private:
			PlayedCard playedCards[4];
			int playedCardIndex = 0;
			bool IsManilha(Card card);
			void GetTableCards();
		};
	}
}
