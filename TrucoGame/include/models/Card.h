#pragma once 

namespace TrucoGame {

    namespace Models {

        class Card {
        private:
            int value;
            string suit;
            //image image;
        public:
            Card(int value, string suit);
            ~Card();
            string getSuit();
            int getValor();
        };
    }
}