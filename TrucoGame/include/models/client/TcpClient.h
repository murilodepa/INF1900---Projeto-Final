#pragma once
#include <winsock2.h>
#include <thread>
#include <iostream>

#include "../ErrorCode.h"
#include "../packets/Packet.h"
#include "../packets/StartGamePacket.h"
#include "../packets/StartRoundPacket.h"
#include "../packets/EndRoundPacket.h"
#include "../packets/EndTurnPacket.h"
#include "../packets/PlayerPlayPacket.h"
#include "../packets/CardPacket.h"
#include "../packets/TrucoPacket.h"
#include "../packets/ElevenHandPacket.h"
#include <nlohmann/json.hpp>

#pragma comment(lib,"WS2_32")
#pragma warning(disable:4996)

namespace TrucoGame {
	namespace Models {

		typedef std::function<void(StartGamePacket)> StartGamePacketEventHandler;
		typedef std::function<void(PlayerPlayPacket)> PlayerPlayPacketEventHandler;
		typedef std::function<void(StartRoundPacket)> StartRoundPacketEventHandler;
		typedef std::function<void(TrucoPacket)> TrucoPacketEventHandler;
		typedef std::function<void(ElevenHandPacket)> ElevenHandPacketEventHandler;

		class TcpClient {
		private:
			SOCKET clientSocket;
			sockaddr_in serverAddr;

			ErrorCode InitializeWinSock();
			ErrorCode CreateSocket(SOCKET& newSocket);
			std::thread mListenThread;

		public:
			ErrorCode Connect(const char* ipAddress, u_short port);
			ErrorCode Send(const char* message);
			ErrorCode Send(const Packet* packet);

			ErrorCode StartListening();
			void Listen();

			PlayerPlayPacketEventHandler playerPlayPacketReceived;
			StartGamePacketEventHandler startGamePacketReceived;
			StartRoundPacketEventHandler startRoundPacketReceived;
			TrucoPacketEventHandler trucoPacketReceived;
			ElevenHandPacketEventHandler elevenHandPacketReceived;
		};
	}
}