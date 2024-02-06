#include "..\..\include\models\Table.h"
#include "..\..\include\models\Card.h"
#include <iostream>

namespace TrucoGame {
	namespace Models {

		Table::Table() {
			playedCardIndex = 0;
		}

		void Table::PlaceCard(Card card, int playerId, bool isCovered)
		{
			if (playedCardIndex >= 4) return;

			PlayedCard playedCard(playerId, card, isCovered);
			playedCards.push_back(playedCard);
			playedCardIndex++;
		}

		void Table::SetTableCard(Card card) {
			manilhaValue = (card.getValue() + 1) % 10;
		}

		int Table::CalculateWinner()
		{
			PlayedCard winningCard = playedCards[0];
			for(int i = 1; i < playedCards.size(); i++)
			{
				int newCardValue = GetCardActualValue(playedCards[i]);
				int oldCardValue = GetCardActualValue(winningCard);
				if (newCardValue > oldCardValue)
				{
					winningCard = playedCards[i];
				}
				else if (newCardValue == oldCardValue)
				{
					winningCard.playerId = -1;
				}
			}

			std::cout << "Winner: " << winningCard.playerId << ": " << winningCard.card.getValue() << " " << winningCard.card.getSuit() << std::endl;
			
			playedCardIndex = 0;

			return winningCard.playerId;
		}

		int Table::GetCardActualValue(PlayedCard playedCard)
		{
			int baseValue = playedCard.card.getValue();

			if (manilhaValue == -1)
				return baseValue;

			if (playedCard.isCovered)
				return -1;

			int actualValue;
			//is manilha
			if (baseValue == manilhaValue)
				actualValue = baseValue + (10 * playedCard.card.getSuit());
			else
				actualValue = baseValue;

			return actualValue;
		}

	}
}
