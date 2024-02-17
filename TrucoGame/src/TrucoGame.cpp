// TrucoGame.cpp : Defines the entry point for the application.

#include <SFML/Graphics.hpp>
#include "../include/controllers/Application.h"

#include <thread>
#include "../include/models/server/TcpServer.h"
#include "../include/models/client/TcpClient.h"
#include "../include/models/Card.h"
#include "../include/models/server/ServerGameManager.h"
#include "../include/models/client/ClientGameManager.h"
#include "../include/views/utils/StartInputWindow.h"

void Server(int numberOfHumanPlayers) {
    using namespace TrucoGame::Models;
    ServerGameManager gameManager;

    //std::thread clientThread(Client);
    gameManager.waitForPlayersToConnect(numberOfHumanPlayers);

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




int main()
{
    using namespace TrucoGame::UtilsView;

    StartInputWindow startInput;
    int choice = startInput.GetUserServerClientInput();
    std::string ip = "127.0.0.1";

    if (choice == 1) {
        int numberOfPlayers = startInput.GetNumberOfPlayersInput();
        std::thread tcpThread(Server, numberOfPlayers);
        tcpThread.detach();
    }
    else {
        ip = startInput.GetUserIpInput();
    }

    TrucoGame::Controller::Application applicationObject(ip);
    applicationObject.drawGameScreen();

    return 0;
}
