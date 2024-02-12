#include "..\..\include\models\Table.h"
#include "..\..\include\models\Card.h"
#include <iostream>

using namespace std;

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

		vector<Card> Table::getPlayedCards()
		{
			vector<Card> tableCards;
		
			for (int i = 0; i < 4; i++)
			{
				tableCards.push_back(*playedCards[i].card);
			}
			
			return tableCards;
		}

		
		void Table::SetTableCard(Card card) {
			manilhaValue = (card.getValue() + 1) % 10;
		}

		int Table::CalculateWinner()
		{
			PlayedCard winningCard = playedCards[0];
			for(int i = 1; i < playedCards.size(); i++)
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

			std::cout << "Winner: " << winningCard.playerId << ": " << winningCard.card.getValue() << " " << winningCard.card.getSuit() << std::endl;
			
			playedCardIndex = 0;

			return winningCard.playerId;
		}

		int Table::getCardActualValue(PlayedCard playedCard)
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

