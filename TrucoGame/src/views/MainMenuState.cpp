/*
#include "../../include/views/MainMenuState.h"
#include <iostream>

TrucoGame::View::MainMenuState::MainMenuState(RenderWindow* window) : State(window)
{
	button = new Button(100, 100, 150, 50, Color::Green, Color::Blue, Color::Yellow);
}

TrucoGame::View::MainMenuState::~MainMenuState()
{
	delete this->button;
}

void TrucoGame::View::MainMenuState::endState()
{
	// TODO - Quit Game
	std::cout << "Ending State - Truco Game" << std::endl;
}

void TrucoGame::View::MainMenuState::update(/*const float& dt*/ /*)
{
	//TODO - Update game state
	this->updateMousePosition();

	this->button->update(this->mousePosView);

	//system("cls");
	//std::cout << this->mousePosView.x << " " << this->mousePosView.y  << std::endl;
}

void TrucoGame::View::MainMenuState::render(RenderTarget* target) {
	if (!target)
		target = this->window;

	this->button->render(target);
}
*/