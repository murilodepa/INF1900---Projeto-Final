#pragma once
#include "TcpClientPlayer.h"
#include "../Table.h"
#include "../Player.h"

namespace TrucoGame {

    namespace Models {

        class AIPlayer : public TcpClientPlayer {
        public:
            AIPlayer(int id, Table *table) : 
            TcpClientPlayer(id), 
            table(table),
            player(Player(id, "AI"+id))
            {
                
            }

            ErrorCode StartListening() override;
            ErrorCode Send(Packet* packet) override;

            Packet* WaitForPacket() override;

            void Listen() override;
        private:
            const int chanceOfRandomCard = 50;
            const int chanceOfRequestingTruco = 5;

            Player player;
            Table* table;

            Packet* nextPlay;
        };
    }
}
