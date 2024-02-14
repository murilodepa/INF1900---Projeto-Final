﻿// TrucoGame.cpp : Defines the entry point for the application.

#include <SFML/Graphics.hpp>
#include "../include/controllers/Application.h"

#include <thread>
#include "../include/models/server/TcpServer.h"
#include "../include/models/client/TcpClient.h"
#include "../include/models/Card.h"
#include "../include/models/server/ServerGameManager.h"
#include "../include/models/client/ClientGameManager.h"

void Client() {
    using namespace TrucoGame::Models;
    ClientGameManager clientGameManager;
    clientGameManager.Start("127.0.0.1");

    while (true) {}
}

void Server() {
    using namespace TrucoGame::Models;
    ServerGameManager gameManager;

    std::thread clientThread(Client);
    gameManager.waitForPlayersToConnect();

    int gameWinner = -1;
    int roundWinner = -1;
    int turnsPlayed = 0;

    gameManager.startGame();
    int currentRound = 0;
    while (gameWinner == -1)
    {
        
        roundWinner = gameManager.startRound();

        turnsPlayed = 0;
        while (roundWinner == -1 && turnsPlayed < 3)
        {
            gameManager.startTurn();
            roundWinner = gameManager.endTurn();
            turnsPlayed++;
        }
        currentRound++;
        gameWinner = gameManager.endRound(roundWinner);
    }
    gameManager.endGame(gameWinner);

    while (true) {}
}

void TestTcp() {
    int choice;
    std::cout << "1 - SERVER \n2 - CLIENT\n";
    std::cin >> choice;
    if (choice == 1) {
        std::thread tcpThread(Server);
        tcpThread.join();
    }
    else {
        std::thread tcpThread(Client);
        tcpThread.join();
    }
}

int main()
{
    std::vector<std::string> names;
    names = { "Caique", "Laert", "Murilo", "Vitor" };

    TrucoGame::Application applicationObject(names);
    applicationObject.run();
    TestTcp();
    return 0;
}