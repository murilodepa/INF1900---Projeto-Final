#include "..\..\include\models\Table.h"
#include "..\..\include\models\Card.h"

using namespace std;

namespace TrucoGame {
	namespace Models {

		Table::Table() {
			playedCardIndex = 0;
		}
		
		void Table::placeCard(Card* card, int playerId, bool isCovered)
		{
			if (playedCardIndex >= 4) return;

			PlayedCard playedCard;
			playedCard.card = card;
			playedCard.playerId = playerId;
			playedCard.isCovered = isCovered;
			playedCards[playedCardIndex] = playedCard;
			playedCardIndex++;
		}

		vector<Card> Table::getPlayedCards()
		{
			vector<Card> tableCards;
		
			for (int i = 0; i < 4; i++)
			{
				tableCards.push_back(*playedCards[i].card);
			}
			
			return tableCards;
		}

		int Table::calculateWinner()
		{
			PlayedCard winningCard;
			winningCard = playedCards[0];
			for(int i = 1; i < 4; i++)
			{
				int newCardValue = getCardActualValue(playedCards[i]);
				int oldCardValue = getCardActualValue(winningCard);
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

		int Table::getCardActualValue(PlayedCard playedCard)
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

