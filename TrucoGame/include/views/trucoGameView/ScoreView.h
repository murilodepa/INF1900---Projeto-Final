#ifndef SCORE_VIEW_H
#define SCORE_VIEW_H

// Define for the x-axis position of the score rectangle
#define CALCULATE_SCORE_RECTANGLE_X_POSITION 0.09f

// Define for the y-axis position of the score rectangle
#define CALCULATE_SCORE_RECTANGLE_Y_POSITION 0.007f

// Character size for the "We" and "They" labels
#define WE_AND_THEY_CHARACTER_SIZE 25

// Character size for the round score display
#define ROUND_SCORE_CHARACTER_SIZE 30

// Define to create dimensions to the score rectangle width
#define CALCULATE_SCORE_RECTANGLE_DIMENSIONS_WIDTH 0.18f

// Macro to create dimensions to the score rectangle height
#define CALCULATE_SCORE_RECTANGLE_DIMENSIONS_HEIGHT 0.12f

// Border color of the score rectangle 
#define BORDER_COLOR sf::Color::White

// Background color of the score rectangle 
#define SCORE_RECTANGLE_BACKGROUNG sf::Color(89, 89, 89, 255)

// Border thickness of the score rectangle
#define BORDER_THICKNESS 2.f

// Circles Color to represent rounds not played yet 
#define CIRCLE_COLOR_OF_ROUNDS_NOT_PLAYED sf::Color(126, 126, 126)

// Define radius of the circles that represent the rounds 
#define CALCULATE_CIRCLE_RADIUS 0.166f

// Defines the sizes of the texts: we and they
#define CALCULATE_WE_AND_THEY_TEXT_CHARACTER_SIZE 0.0675f

// Defines the sizes of the texts: score
#define CALCULATE_SCORE_TEXT_CHARACTER_SIZE 0.0925f

#pragma once
#include <SFML/Graphics.hpp>
#include "../text/TextView.h"

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

			TextView *roundScoreText, *weText, *theyText;
			Font textsFont;
			size_t numRounds = 3;

			void createScoreRectangle(float rectangleScoreXPosition, float rectangleScoreYPosition, 
				Vector2f& scoreRectangleDimensions, std::shared_ptr<float>& rectangleScoreWidth, 
				std::shared_ptr<float>& rectangleScoreHeight, std::shared_ptr<float>& textsWidth);
			void createCirclesInScoreRectangle(float rectangleWidthToCircles, float rectangleScoreHeight, float rectangleScoreXPosition, float rectangleScoreYPosition);
			void initializeTexts(const float scoreRectangleWidth);

			void setTextsFont(const std::string& fontPath);
			void setTextsColor();
			void TrucoGame::View::ScoreView::setTextsPosition(float scoreRectangleXPosition, float scoreRectangleYPosition, float rectangleWidthToCirclesPtr, float rectangleScoreHeight, float textsWidth);
		public:
			ScoreView(const Vector2f& windowSize);
			~ScoreView();

			RectangleShape getScoreRectangle();
			RectangleShape getRectangleDivWidth();
			RectangleShape getRectangleDivHeight();

			CircleShape getOurCircles(size_t index);
			CircleShape getTheirCircles(size_t index);

			TextView getRoundScoreText();
			TextView getWeText();
			TextView getTheyText();

			void changeRoundScoreText(size_t newRoundScore); // TODO Enum 1 - 2 -3
		};
	}
}

#endif // SCORE_VIEW_H