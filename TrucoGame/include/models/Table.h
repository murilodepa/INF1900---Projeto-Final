#pragma once 
#include "Card.h"
#include "Deck.h"

using namespace std;

namespace TrucoGame {
	namespace Models {
		class PlayedCard {
		public:
			int playerId;
			Card card;
			bool isCovered;
			PlayedCard(int playerId, Card card, bool isCovered) :
				playerId(playerId),
				card(card),
				isCovered(isCovered){}
		};

		class Table {
		public:
			Table();
			void PlaceCard(Card card, int playerId, bool isCovered);
			//Returns: playerId of the winner (0 ~ 3)
			int CalculateWinner();
			Card* GetAllCards();
			void SetTableCard(Card card);
			std::vector<PlayedCard> playedCards;
		private:
			int manilhaValue = -1;
			int playedCardIndex = 0;
			int getCardActualValue(PlayedCard playedCard);
		};
	}
}
