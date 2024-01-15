#pragma once
#include <winsock2.h>
#include <thread>
#include <iostream>

#include "../ErrorCode.h"
#include "../Packet.h"
#include <nlohmann/json.hpp>

#pragma comment(lib,"WS2_32")
#pragma warning(disable:4996)

namespace TrucoGame {
	namespace Models {

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
			ErrorCode Send(const Packet& packet);

			ErrorCode StartListening();
			void Listen();
		};
	}
}