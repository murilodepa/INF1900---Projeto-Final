#pragma once 
#include "Card.h"

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

		class Table
		{
		public:
			Table();
			Card* turnedCard = nullptr;
			void PlaceCard(Card card, int playerId, bool isCovered);
			//Returns: playerId of the winner (0 ~ 3)
			int CalculateWinner();
			Card* GetAllCards();
			std::vector<PlayedCard> playedCards;
		private:
			int playedCardIndex = 0;
			int GetCardActualValue(PlayedCard playedCard);
		};
	}
}
