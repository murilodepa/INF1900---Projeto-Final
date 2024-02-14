#pragma once
#include <functional>
#include "TcpClient.h"
#include "../Score.h"
#include "../Player.h"
#include "../packets/StartGamePacket.h"
#include "../packets/StartRoundPacket.h"
#include "../packets/PlayerPlayPacket.h"
#include "../packets/CardPacket.h"
#include "../packets/TrucoPacket.h"
#include "../packets/ElevenHandPacket.h"
#include "../packets/ElevenHandResponsePacket.h"

namespace TrucoGame {
    namespace Models {
        typedef std::function<void(bool)> MyTurnStartedEventHandler;
        typedef std::function<void(Card, int, bool)> AnotherPlayerPlayedEventHandler;
        typedef std::function<void(Card, std::vector<Card>)> RoundStartedEventHandler;
        typedef std::function<void(Card, std::vector<Card>, std::vector<Card>)> ElevenHandRoundStartEventHandler;
        typedef std::function<void(Card)> IronHandRoundStartedEventHandler;
        typedef std::function<void(int, int, int)> RoundEndedEventHandler;
        typedef std::function<void(int, int)> TurnEndedEventHandler;
        typedef std::function<void(int)> TrucoAcceptedEventHandler;
        typedef std::function<void()> TrucoRefusedEventHandler;
        typedef std::function<void(int, int)> TrucoResquestedEventHandler;
        typedef std::function<void()> GameWonEventHandler;
        typedef std::function<void()> GameLostEventHandler;


        class ClientGameManager {
        private:
            TcpClient client;
            Score score;

            void GetPlayerInputAndSend();
            void OnStartGamePacketReceived(StartGamePacket packet);
            void OnStartRoundPacketReceived(StartRoundPacket packet);
            void OnPlayPacketReceived(PlayerPlayPacket packet);
            void OnTrucoPacketReceived(TrucoPacket packet);
            void OnElevenHandPacketReceived(ElevenHandPacket packet);
            void OnCardPacketReceived(CardPacket packet);
            void OnEndTurnPacketReceived(EndTurnPacket packet);
            void OnEndRoundPacketReceived(EndRoundPacket packet);
        public:
            Player* player;
            ClientGameManager();
            void Start(std::string ip);

             //EVENTS 
            MyTurnStartedEventHandler myTurnStarted;
            AnotherPlayerPlayedEventHandler anotherPlayerPlayed;
            RoundStartedEventHandler roundStarted;
            ElevenHandRoundStartEventHandler elevenHandRoundStarted;
            IronHandRoundStartedEventHandler ironHandRoundStarted;
            RoundEndedEventHandler roundEnded;
            TurnEndedEventHandler turnEnded;
            TrucoAcceptedEventHandler trucoAccepted;
            TrucoRefusedEventHandler trucoRefused;
            TrucoResquestedEventHandler trucoRequested;
            GameWonEventHandler gameWon;
            GameLostEventHandler gameLost;
        };
    }
}