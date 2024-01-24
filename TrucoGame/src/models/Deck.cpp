#include "../../include/models/Deck.h"
#include <random>
#include <iostream>

namespace TrucoGame {

    namespace Models {
        

        Deck::Deck()
        {
            for (int i = 0; i <= 9; i++) {
                cards.push_back(ClubsCard(i));
                cards.push_back(SpadesCard(i));
                cards.push_back(DiamondsCard(i));
                cards.push_back(HeartsCard(i));
            }
        }

        Deck::~Deck() 
        {
            cards.clear();
        }

        Card* Deck::pop() {
            if (cards.empty()) {
                std::cout << "Attempted to draw card on an empty deck." << std::endl;
            }

            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distrib(0, cards.size() - 1);
            int randomIndex = distrib(gen);

            Card* selectedCard = &cards[randomIndex];
            cards.erase(cards.begin() + randomIndex);

            return selectedCard;
        }

        void Deck::push(Card card) {
            cards.push_back(card);
        }
    }
}