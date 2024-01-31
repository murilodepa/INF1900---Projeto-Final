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

			std::cout << "Calculated Winner:" << std::endl;
			std::cout << "Card:" << winningCard.card.getValue() << " " << winningCard.card.getSuit() << std::endl;
			std::cout << "Played by:" << winningCard.playerId << std::endl;
			return winningCard.playerId;
		}

		int Table::GetCardActualValue(PlayedCard playedCard)
		{
			int baseValue = playedCard.card.getValue();

			if (turnedCard == nullptr)
				return baseValue;

			if (playedCard.isCovered)
				return -1;

			//is manilha
			if (baseValue == (turnedCard->getValue() + 1) % 10)
				return baseValue + (10 * playedCard.card.getSuit());
			else
				return baseValue;
		}

	}
}
