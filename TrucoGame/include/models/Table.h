#pragma once 
#include "Card.h"
#include "Deck.h"

using namespace std;

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
			void placeCard(Card* card, int playerId, bool isCovered);
			vector<Card> getPlayedCards();
			int calculateWinner();
			void cleanPlayedCards();
		private:
			PlayedCard playedCards[4];
			int playedCardIndex = 0;
			int getCardActualValue(PlayedCard playedCard);
		};
	}
}
