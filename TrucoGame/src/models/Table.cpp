#include "..\..\include\models\Table.h"
#include "..\..\include\models\Card.h"

namespace TrucoGame {
	namespace Models {

		Table::Table() {
			playedCardIndex = 0;
		}

		std::vector<Card> Table::ShuffleHandCard()
		{
			std::vector<Card> shuffleHand;

			shuffleHand.push_back(deck.pop());
			shuffleHand.push_back(deck.pop());
			shuffleHand.push_back(deck.pop());

			return shuffleHand;
		}

		void Table::PlaceCard(Card* card, int playerId, bool isCovered)
		{
			if (playedCardIndex >= 4) return;

			PlayedCard playedCard;
			playedCard.card = card;
			playedCard.playerId = playerId;
			playedCard.isCovered = isCovered;
			playedCards[playedCardIndex] = playedCard;
			playedCardIndex++;
		}

		int Table::CalculateWinner()
		{
			PlayedCard winningCard;
			winningCard = playedCards[0];
			for(int i = 1; i < 4; i++)
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
			return winningCard.playerId;
		}

		int Table::GetCardActualValue(PlayedCard playedCard)
		{
			int baseValue = playedCard.card->getValue();

			if (turnedCard == nullptr)
				return baseValue;

			if (playedCard.isCovered)
				return -1;

			//is manilha
			if (baseValue == (turnedCard->getValue() + 1) % 10)
				return baseValue + (10 * playedCard.card->getSuit());
			else
				return baseValue;
		}
	}
}

