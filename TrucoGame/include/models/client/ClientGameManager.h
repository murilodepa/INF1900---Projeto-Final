#pragma once
#include "TcpClient.h";
#include "../Player.h";
#include "../packets/StartGamePacket.h"
#include "../packets/StartRoundPacket.h"
#include "../packets/PlayerPlayPacket.h"
#include "../packets/CardPacket.h"
#include "../packets/TrucoPacket.h"

namespace TrucoGame {
    namespace Models {
        class ClientGameManager {
        private:
            Player* player;
            TcpClient client;
            void OnStartGamePacketReceived(StartGamePacket packet);
            void OnStartRoundPacketReceived(StartRoundPacket packet);
            void OnPlayPacketReceived(PlayerPlayPacket packet);
        public:
            ClientGameManager();
        };
    }
}