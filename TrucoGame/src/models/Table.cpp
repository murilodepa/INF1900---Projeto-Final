#include "..\..\include\models\Table.h"

namespace TrucoGame {
	namespace Models {

		std::vector<Card> Table::ShuffleHandCard()
		{
			std::vector<Card> shuffleHand;

			shuffleHand.push_back(deck.pop());
			shuffleHand.push_back(deck.pop());
			shuffleHand.push_back(deck.pop());

			return shuffleHand;
		}

		void Table::PlaceCard(Card card, int playerId)
		{
			PlayedCard playedCard;
			playedCard.card = card;
			playedCard.playerId = playerId;
			playedCards[playedCardIndex] = playedCard;
			playedCardIndex++;
		}


		int Table::CalculateWinner()
		{
			int playerIdWinner = -1;
			Card winningCard;
			for(int i = 0; i < 4; i++)
			{
				if (playedCards[i].card.GetValue() > winningCard.GetValue() || IsManilha(playedCards[i].card)) //TODO: Improve how winner is calculated (maybe improve get value)
				{
					winningCard = playedCards[i];
					playerIdWinner = playedCards[i].playerId;
				}
				if (playedCards[i].card.GetValue() == winningCard.GetValue())
				{
					playerIdWinner = -1;
				}
			}
			return playerIdWinner;
		}

		bool Table::IsManilha(Card card)
		{
			return (card.GetValue() == (turnedCard.GetValue() + 1) % 10);
		}

		void Table::GetTableCards()
		{
			for (int i = 0; i < playedCards; i++)
			{
				deck.push(card);
				PlayedCard[i] = NULL;
			}
		}
	}
}

