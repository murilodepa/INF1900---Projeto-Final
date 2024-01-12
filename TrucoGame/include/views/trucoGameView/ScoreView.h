#ifndef SCORE_VIEW_H
#define SCORE_VIEW_H

// File path for the Arial.ttf font used "We" and "They" labels and round score
#define NAME_FONT_PATH "../../../../TrucoGame/resources/fonts/Arial.ttf"

// Define for the x-axis position of the score rectangle
#define SCORE_RECTANGLE_X_POSITION 200.0f

// Define for the y-axis position of the score rectangle
#define SCORE_RECTANGLE_Y_POSITION 10.0f

// Character size for the "We" and "They" labels
#define WE_AND_THEY_CHARACTER_SIZE 25

// Character size for the round score display
#define ROUND_SCORE_CHARACTER_SIZE 30

// Macro to create dimensions to the score rectangle like sf::Vector2f
#define SCORE_RECTANGLE_DIMENSIONS sf::Vector2f(400.f, 180.f)

// Border color of the score rectangle 
#define BORDER_COLOR sf::Color::White

// Background color of the score rectangle 
#define SCORE_RECTANGLE_BACKGROUNG sf::Color(89, 89, 89, 255)

// Border thickness of the score rectangle
#define BORDER_THICKNESS 2.f

// Circles Color to represent rounds not played yet 
#define CIRCLE_COLOR_OF_ROUNDS_NOT_PLAYED sf::Color(126, 126, 126)

// Define radius of the circles that represent the rounds 
#define CIRCLE_RADIUS 30.f

// Defines the sizes of the texts: we and they
#define WE_AND_THEY_TEXT_CHARACTER_SIZE 27

// Defines the sizes of the texts: score
#define SCORE_TEXT_CHARACTER_SIZE 37

#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

namespace TrucoGame {
	namespace View {
		class ScoreView {
		private:
			RectangleShape scoreRectangle;
			RectangleShape rectangleDivWidth;
			RectangleShape rectangleDivHeight;

			std::vector<sf::CircleShape> ourCircles;
			std::vector<sf::CircleShape> theirCircles;

			Text roundScoreText;
			Text weText;
			Text theyText;
			Font textsFont;
			size_t numRounds = 3;

			float roundScoreTextWidth;
			float weTextWidth;
			float theyTextWidth;

			float roundScoreTextHeight;
			float weTextHeight;
			float theyTextHeight;

			void createScoreRectangle(float rectangleScoreXPosition, float rectangleScoreYPosition, 
				Vector2f& scoreRectangleDimensions, std::shared_ptr<float>& rectangleScoreWidth, 
				std::shared_ptr<float>& rectangleScoreHeight, std::shared_ptr<float>& textsWidth);
			void createCirclesInScoreRectangle(float rectangleWidthToCircles, float rectangleScoreHeight, float rectangleScoreXPosition, float rectangleScoreYPosition);
			void initializeTexts();

			void setTextsFont(const std::string& fontPath);
			void setTextsColor();
			void TrucoGame::View::ScoreView::setTextsPosition(float scoreRectangleXPosition, float scoreRectangleYPosition, float rectangleWidthToCirclesPtr, float rectangleScoreHeight, float textsWidth);
		public:
			ScoreView();
			~ScoreView();

			RectangleShape getScoreRectangle();
			RectangleShape getRectangleDivWidth();
			RectangleShape getRectangleDivHeight();

			CircleShape getOurCircles(size_t index);
			CircleShape getTheirCircles(size_t index);

			Text getRoundScoreText();
			Text getWeText();
			Text getTheyText();

			void changeRoundScoreText(size_t newRoundScore); // TODO Enum 1 - 2 -3
		};
	}
}

#endif // SCORE_VIEW_H