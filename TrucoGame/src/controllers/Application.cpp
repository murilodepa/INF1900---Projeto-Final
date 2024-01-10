#include "../../include/controllers/Application.h"
#include "../../include/views/trucoGameView/Animator.h"
#include "../../include/views/UtilsView.h"
#include <thread>
#include <iostream>

using namespace TrucoGame::View;

namespace TrucoGame {

    GraphicManager* Application::pGraphicManager = GraphicManager::getGraphicManager();

    Application::Application() : trucoGameView(pGraphicManager->getWindowSize()) {
        if (pGraphicManager == nullptr) {
            std::cout << "ERROR::TrucoGame::Application - Failed to create GraphicManager." << std::endl;
            exit(1);
        }
        initialize();
    }

    Application::~Application() {

    }

    void Application::initialize() {
        // TODO Define the initial state of the window
    }

    void Application::run() 
    {
        
        std::shared_ptr<bool> firstTimeFlag = std::make_shared<bool>(true);

        while (pGraphicManager->checkWindowOpen()) {

            // Check if the user intends to close the window
            pGraphicManager->checkWindowClose();

            //Clear the window
            pGraphicManager->clearWindow();

            //Draw
            trucoGameView.drawElementsOnTheWindow(pGraphicManager, firstTimeFlag);


            //pGraphicManager->drawElement(cardDeck.cardsInHands[0][0]);
            //std::thread animationThread1(&TrucoGame::View::Animator::moveSpriteTo, std::ref(cardDeck.cardsInHands[0][0]), Vector2f(200.0f, 200.0f), 15.0f);
            //animationThread1.detach();

            pGraphicManager->showElements();
        }
        

        /*
        sf::Texture mesaTexture = UtilsView::loadTexture("../../../../TrucoGame/resources/images/table/tablecloth_texture4.png");
        sf::Texture cardTexture = UtilsView::loadTexture("../../../../TrucoGame/resources/images/cards/cardBack.png");
        sf::Font arialFont = UtilsView::loadFont("../../../../TrucoGame/resources/fonts/Arial.ttf");
        sf::Texture newTexture = UtilsView::loadTexture("../../../../TrucoGame/resources/images/cards/Clubs/Ace.png");

        sf::Sprite playerHands[4][3];  // Cartas nas mãos dos 4 jogadores

        sf::Sprite cardTurnedFaceUp;
        sf::Sprite deck;
        sf::Sprite initialDeck[14];


        // Obtém as dimensões da textura
        sf::Vector2u textureSize = mesaTexture.getSize();
        
        sf::Sprite pano(mesaTexture);

        cardTurnedFaceUp.setTexture(cardTexture);
        deck.setTexture(cardTexture);


        cardTurnedFaceUp.setScale(0.4f, 0.4f);
        deck.setScale(0.4f, 0.4f);
        deck.setRotation(35.0f);

        int cardCount = 0;


        for (int i = 0; i < 14; i++) {
            initialDeck[i].setTexture(cardTexture);
            initialDeck[i].setScale(0.4f, 0.4f);
            initialDeck[i].setPosition(200, 200);
        }

        // Inicializa as cartas nas mãos dos jogadores
        for (int player = 0; player < 4; ++player) {
            for (int card = 0; card < 3; ++card) {
                playerHands[player][card].setTexture(cardTexture);

                // Define a escala inicial para 0.4 (40% do tamanho original)
                playerHands[player][card].setScale(0.4f, 0.4f);

                // Rotacione as cartas do oponente
                if (player % 2 != 0) {
                    playerHands[player][card].setRotation(90.0f);
                }
            }
        }

        // Define as posições iniciais para as cartas nas mãos dos jogadores
        float cardWidth = playerHands[0][0].getGlobalBounds().width; // 427
        float cardHeight = playerHands[0][0].getGlobalBounds().height; // 600
        
        float screenWidth = pGraphicManager->getWindowSize().x;
        float screenHeight = pGraphicManager->getWindowSize().y;

        float halfScreenWidth = screenWidth / 2;
        float halfScreenHeight = screenHeight / 2;

        float halfCard = cardWidth / 2;
        float cardsSpacing = 15.0f;
        float cardAndTableSpacing = 110.0f;

        float textAndTableSpacing = 40.0f;

       playerHands[0][0].setPosition(halfScreenWidth - halfCard - cardsSpacing - cardWidth, cardAndTableSpacing);
       playerHands[0][1].setPosition(halfScreenWidth - halfCard, cardAndTableSpacing);
       playerHands[0][2].setPosition(halfScreenWidth + halfCard + cardsSpacing, cardAndTableSpacing);

       playerHands[1][0].setPosition(cardHeight + cardAndTableSpacing, halfScreenHeight - halfCard - cardsSpacing - cardWidth);
       playerHands[1][1].setPosition(cardHeight + cardAndTableSpacing, halfScreenHeight - halfCard);
       playerHands[1][2].setPosition(cardHeight + cardAndTableSpacing, halfScreenHeight + halfCard + cardsSpacing);

       playerHands[2][0].setPosition(halfScreenWidth - halfCard - cardsSpacing - cardWidth, screenHeight - cardAndTableSpacing - cardHeight);
       playerHands[2][1].setPosition(halfScreenWidth - halfCard, screenHeight - cardAndTableSpacing - cardHeight);
       playerHands[2][2].setPosition(halfScreenWidth + halfCard + cardsSpacing, screenHeight - cardAndTableSpacing - cardHeight);

       playerHands[3][0].setPosition(screenWidth - cardAndTableSpacing, halfScreenHeight - halfCard - cardsSpacing - cardWidth);
       playerHands[3][1].setPosition(screenWidth - cardAndTableSpacing, halfScreenHeight - halfCard);
       playerHands[3][2].setPosition(screenWidth - cardAndTableSpacing, halfScreenHeight + halfCard + cardsSpacing);

       deck.setPosition(halfScreenWidth + 20, halfScreenHeight - halfCard - 20);
       cardTurnedFaceUp.setPosition(halfScreenWidth - halfCard, halfScreenHeight - halfCard);
      

        pano.setScale(static_cast<float>(pGraphicManager->getWindowSize().x) / textureSize.x,
            static_cast<float>(pGraphicManager->getWindowSize().y) / textureSize.y);

        // Crie um objeto de texto
        sf::Text text[4];

        for (int i = 0; i < 4; i++) {
            text[i].setFont(arialFont); // Defina a fonte para o texto
            text[i].setString("Nome - " + std::to_string(i)); // Defina o texto
            text[i].setCharacterSize(30); // Defina o tamanho do caractere
            text[i].setFillColor(sf::Color::White); // Defina a cor do texto
            text[i].setStyle(sf::Text::Bold); // Defina o estilo para negrito
        }

        float textWidth = text[0].getGlobalBounds().width; 
        float textHeight = text[0].getGlobalBounds().height;

        float halfText = text[0].getGlobalBounds().width / 2;

        text[0].setPosition(halfScreenWidth - halfText, textAndTableSpacing);
        text[1].setRotation(-90.0f);
        text[1].setPosition(textAndTableSpacing, halfScreenHeight + halfText);
        text[2].setPosition(halfScreenWidth - halfText, screenHeight - textAndTableSpacing - textHeight - 5);
        text[3].setRotation(90.0f);
        text[3].setPosition(screenWidth - textAndTableSpacing, halfScreenHeight - halfText);

        bool x = false;

        while (pGraphicManager->checkWindowOpen()) {

            // Check if the user intends to close the window
            pGraphicManager->checkWindowClose();

            //Clear the window
            pGraphicManager->clearWindow();

           // TrucoGa

            // Desenhe a mesa
            //sf::RectangleShape mesa(sf::Vector2f(pGraphicManager->getWindowSize().x, pGraphicManager->getWindowSize().y));
            //mesa.setFillColor(sf::Color(139, 69, 19));  // Cor marrom para representar a madeira da mesa
            pGraphicManager->drawElement(pano);

            // Desenha as cartas nas mãos dos jogadores
            for (int player = 0; player < 4; ++player) {
                for (int card = 0; card < 3; ++card) {
                   // pGraphicManager->drawElement(playerHands[player][card]);
                }
            }

            pGraphicManager->drawElement(cardTurnedFaceUp);
            pGraphicManager->drawElement(deck);

            for (int card = 0; card < 14; ++card) {
                pGraphicManager->drawElement(initialDeck[card]);
            }

            for (int i = 0; i < 4; i++) {
                pGraphicManager->drawElement(text[i]);
            }
            

            if (x == false) {
                x = true;
                std::thread animationThread1(&TrucoGame::View::Animator::moveSpriteTo, std::ref(initialDeck[cardCount]), playerHands[0][0].getPosition(), 15.0f);
                cardCount++;
                std::thread animationThread2(&TrucoGame::View::Animator::moveSpriteTo, std::ref(initialDeck[cardCount]), playerHands[0][1].getPosition(), 15.0f);
                cardCount++;
                std::thread animationThread3(&TrucoGame::View::Animator::moveSpriteTo, std::ref(initialDeck[cardCount]), playerHands[0][2].getPosition(), 15.0f);
                cardCount++;

                std::thread animationThread4(&TrucoGame::View::Animator::moveSpriteTo, std::ref(initialDeck[cardCount]), playerHands[2][0].getPosition(), 15.0f);
                cardCount++;
                std::thread animationThread5(&TrucoGame::View::Animator::moveSpriteTo, std::ref(initialDeck[cardCount]), playerHands[2][1].getPosition(), 15.0f);
                cardCount++;
                std::thread animationThread6(&TrucoGame::View::Animator::moveSpriteTo, std::ref(initialDeck[cardCount]), playerHands[2][2].getPosition(), 15.0f);
                cardCount++;

                std::thread animationThread7(&TrucoGame::View::Animator::moveAndRotateSpriteTo, std::ref(initialDeck[cardCount]), playerHands[1][0].getPosition(), 90.0f, 15.0f);
                cardCount++;
                std::thread animationThread8(&TrucoGame::View::Animator::moveAndRotateSpriteTo, std::ref(initialDeck[cardCount]), playerHands[1][1].getPosition(), 90.0f, 15.0f);
                cardCount++;
                std::thread animationThread9(&TrucoGame::View::Animator::moveAndRotateSpriteTo, std::ref(initialDeck[cardCount]), playerHands[1][2].getPosition(), 90.0f, 15.0f);
                cardCount++;
                
                std::thread animationThread10(&TrucoGame::View::Animator::moveAndRotateSpriteTo, std::ref(initialDeck[cardCount]), playerHands[3][0].getPosition(), 90.0f, 15.0f);
                cardCount++;
                std::thread animationThread11(&TrucoGame::View::Animator::moveAndRotateSpriteTo, std::ref(initialDeck[cardCount]), playerHands[3][1].getPosition(), 90.0f, 15.0f);
                cardCount++;
                std::thread animationThread12(&TrucoGame::View::Animator::moveAndRotateSpriteTo, std::ref(initialDeck[cardCount]), playerHands[3][2].getPosition(), 90.0f, 15.0f);
                cardCount++;

                Texture newTexture = UtilsView::loadTexture("../../../../TrucoGame/resources/images/cards/Clubs/Ace.png");

                std::thread animationThread13(&TrucoGame::View::Animator::animationWithCardTurnedFaceUpAndInitialDeck, std::ref(initialDeck[cardCount]), newTexture, std::ref(initialDeck[cardCount+1]), sf::Vector2f(cardTurnedFaceUp.getPosition().x+cardWidth, cardTurnedFaceUp.getPosition().y), deck.getPosition(), 35.0f, 15.0f);
                cardCount++;
                cardCount++;
                

                //std::thread animationThread(&TrucoGame::View::Animator::moveAndRotateSpriteTo, std::ref(initialDeck), cardTurnedFaceUp.getPosition(), 90.0f, 15.0f);
                animationThread1.detach();
                animationThread2.detach();
                animationThread3.detach();
                animationThread4.detach();
                animationThread5.detach();
                animationThread6.detach();
                animationThread7.detach();
                animationThread8.detach();
                animationThread9.detach();
                animationThread10.detach();
                animationThread11.detach();
                animationThread12.detach();
                animationThread13.detach();

                //Animator::moveSpriteTo(std::ref(initialDeck[cardCount]), cardTurnedFaceUp.getPosition(), 15.0f);
                //Animator::flipCard(std::ref(initialDeck[cardCount]), 1.5f);
                //cardCount++;
                //animationThread13.join();

                //std::thread animationThread13(&TrucoGame::View::Animator::moveSpriteTo, std::ref(initialDeck[cardCount]), cardTurnedFaceUp.getPosition(), 15.0f);
                //std::thread animationThread14(&Animator::flipCard, std::ref(playerHands[0][0]), 1.5f);
                //animationThread14.join();
                // 
                //std::thread animationThread(animate, std::ref(initialDeck), cardTurnedFaceUp.getPosition(), 15.0f);
                //animationThread.detach();
                //std::thread animationThread2(&Animator::flipCard, std::ref(playerHands[0][0]), 1.5f);
                //animationThread2.detach();

            }
            
            pGraphicManager->showElements();
        }*/
    }
}