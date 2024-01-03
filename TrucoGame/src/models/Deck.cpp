#include "../../include/models/Deck.h"

namespace TrucoGame {

    namespace Models {
        

        Deck::Deck()
        {
            cardDeck = new List<Card>;
            //popula lista de cartas
            //deckupdate(cardDeck);
        }

        Deck::~Deck() 
        {
            delete(cardDeck);
        }

        Card DrawCard() {
        
            //return Card;
        }

        void returnCard(Card card) {

        }
    }
}