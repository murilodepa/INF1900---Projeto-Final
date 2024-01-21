#include "..\..\include\models\Table.h"
#include "..\..\include\models\Card.h"

namespace TrucoGame {
	namespace Models {

		Table::Table() {
			playedCardIndex = 0;
		}

		void Table::PlaceCard(Card* card, int playerId)
		{
			if (playedCardIndex >= 4) return;

			PlayedCard playedCard;
			playedCard.card = card;
			playedCard.playerId = playerId;
			playedCards[playedCardIndex] = playedCard;
			playedCardIndex++;
		}

		int Table::CalculateWinner()
		{
			PlayedCard winningCard;
			winningCard = playedCards[0];
			for(int i = 1; i < 4; i++)
			{
				int newCardValue = GetCardActualValue(playedCards[i].card);
				int oldCardValue = GetCardActualValue(winningCard.card);
				if (newCardValue > oldCardValue)
				{
					winningCard = playedCards[i];
				}
				else if (newCardValue == oldCardValue)
				{
					winningCard.playerId = -1;
				}
			}
			return winningCard.playerId;
		}

		int Table::GetCardActualValue(Card* card)
		{
			int baseValue = card->getValue();
			if (turnedCard == nullptr)
				return baseValue;

			//is manilha
			if (card->getValue() == (turnedCard->getValue() + 1) % 10)
				return baseValue + (10 * card->getSuit());
			else
				return baseValue;
		}

	}
}
