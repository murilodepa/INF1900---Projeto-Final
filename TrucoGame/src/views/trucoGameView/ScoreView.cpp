#include "../../../include/views/trucoGameView/ScoreView.h"
#include "../../../include/views/utils/UtilsView.h"

void TrucoGame::View::ScoreView::createScoreRectangle(float scoreRectangleXPosition, float scoreRectangleYPosition, Vector2f& scoreRectangleDimensions, std::shared_ptr<float>& rectangleWidthToCircles, std::shared_ptr<float>& rectangleScoreHeight, std::shared_ptr<float>& textsWidth)
{
    scoreRectangle.setSize(sf::Vector2f(scoreRectangleDimensions));
    scoreRectangle.setPosition(scoreRectangleXPosition, scoreRectangleYPosition);
    scoreRectangle.setFillColor(SCORE_RECTANGLE_BACKGROUNG);
    scoreRectangle.setOutlineColor(BORDER_COLOR); 
    scoreRectangle.setOutlineThickness(BORDER_THICKNESS);

    float rectangleScoreWidth = scoreRectangle.getGlobalBounds().width;
    *rectangleScoreHeight = scoreRectangle.getGlobalBounds().height;
    *textsWidth = rectangleScoreWidth / 6;
    *rectangleWidthToCircles = rectangleScoreWidth - *textsWidth;

    rectangleDivWidth.setSize(sf::Vector2f(*rectangleWidthToCircles, BORDER_THICKNESS));
    rectangleDivWidth.setPosition(scoreRectangleXPosition, scoreRectangleYPosition + *rectangleScoreHeight / BORDER_THICKNESS - BORDER_THICKNESS);
    rectangleDivWidth.setFillColor(BORDER_COLOR);

    rectangleDivHeight.setSize(sf::Vector2f(BORDER_THICKNESS, *rectangleScoreHeight - BORDER_THICKNESS));
    rectangleDivHeight.setPosition(scoreRectangleXPosition + *rectangleWidthToCircles, scoreRectangleYPosition);
    rectangleDivHeight.setFillColor(BORDER_COLOR);
}

void TrucoGame::View::ScoreView::createCirclesInScoreRectangle(float rectangleWidthToCircles, float rectangleScoreHeight, float rectangleScoreXPosition, float rectangleScoreYPosition)
{
    ourCircles.resize(numRounds);
    theirCircles.resize(numRounds);

    float circleRadius = rectangleScoreHeight * CALCULATE_CIRCLE_RADIUS;

    for (int i = 0; i < numRounds; i++) {
        ourCircles[i].setRadius(circleRadius);
        theirCircles[i].setRadius(circleRadius);

        ourCircles[i].setFillColor(sf::Color(CIRCLE_COLOR_OF_ROUNDS_NOT_PLAYED));
        theirCircles[i].setFillColor(sf::Color(CIRCLE_COLOR_OF_ROUNDS_NOT_PLAYED));
    }

    float circleDiameter = ourCircles[0].getGlobalBounds().width;

    float circlesSpacingWidth = (rectangleWidthToCircles - 3 * circleDiameter) / 4;
    float circlesSpacingHeight = (rectangleScoreHeight / 2 - circleDiameter) / 2;

    float spacingAndCircleDiameterWidth = circlesSpacingWidth + circleDiameter + circlesSpacingWidth;
    float rectangleScoreYPositionAndSpacing = rectangleScoreYPosition + circlesSpacingHeight;
    float circlesSpacingHeightDouble = circlesSpacingHeight + circlesSpacingHeight;

    ourCircles[0].setPosition(rectangleScoreXPosition + circlesSpacingWidth, rectangleScoreYPositionAndSpacing);
    ourCircles[1].setPosition(rectangleScoreXPosition + spacingAndCircleDiameterWidth, rectangleScoreYPositionAndSpacing);
    ourCircles[2].setPosition(rectangleScoreXPosition + spacingAndCircleDiameterWidth + circleDiameter + circlesSpacingWidth, rectangleScoreYPositionAndSpacing);

    theirCircles[0].setPosition(rectangleScoreXPosition + circlesSpacingWidth, rectangleScoreYPositionAndSpacing + circleDiameter + circlesSpacingHeightDouble);
    theirCircles[1].setPosition(rectangleScoreXPosition + spacingAndCircleDiameterWidth, rectangleScoreYPositionAndSpacing + circleDiameter + circlesSpacingHeightDouble);
    theirCircles[2].setPosition(rectangleScoreXPosition + spacingAndCircleDiameterWidth + circleDiameter + circlesSpacingWidth, rectangleScoreYPositionAndSpacing + circleDiameter + circlesSpacingHeightDouble);
}

TrucoGame::View::ScoreView::ScoreView(const Vector2f& windowSize)
{
    float windowSizeX = windowSize.x;
    float windowSizeY = windowSize.y;
    float scoreRectangleXPosition = CALCULATE_SCORE_RECTANGLE_X_POSITION * windowSizeX;
    float scoreRectangleYPosition = CALCULATE_SCORE_RECTANGLE_Y_POSITION * windowSizeY;
    Vector2f& scoreRectangleDimensions = Vector2f(CALCULATE_SCORE_RECTANGLE_DIMENSIONS_WIDTH * windowSizeX, CALCULATE_SCORE_RECTANGLE_DIMENSIONS_HEIGHT * windowSizeY);
    std::shared_ptr<float> rectangleWidthToCirclesPtr = std::make_shared<float>();
    std::shared_ptr<float> rectangleScoreHeight = std::make_shared<float>();
    std::shared_ptr<float> textsWidth = std::make_shared<float>();

    createScoreRectangle(scoreRectangleXPosition, scoreRectangleYPosition, scoreRectangleDimensions, rectangleWidthToCirclesPtr, rectangleScoreHeight, textsWidth);
    createCirclesInScoreRectangle(*rectangleWidthToCirclesPtr - *textsWidth, *rectangleScoreHeight, scoreRectangleXPosition + *textsWidth, scoreRectangleYPosition);
    initializeTexts(scoreRectangleDimensions.x);
    setTextsPosition(scoreRectangleXPosition, scoreRectangleYPosition, *rectangleWidthToCirclesPtr, *rectangleScoreHeight, *textsWidth);
}

TrucoGame::View::ScoreView::~ScoreView()
{
}

void TrucoGame::View::ScoreView::changeColor(int turn, int vefiryColor)
{
    if (vefiryColor == 0) {
        ourCircles[turn].setFillColor(Color::Yellow);
        theirCircles[turn].setFillColor(Color::Yellow);
    } else if (vefiryColor == 1) {
        ourCircles[turn].setFillColor(Color::Green);
        theirCircles[turn].setFillColor(Color::Red);
    }
    else {
        ourCircles[turn].setFillColor(Color::Red);
        theirCircles[turn].setFillColor(Color::Green);
    }
}
RectangleShape TrucoGame::View::ScoreView::getScoreRectangle()
{
    return scoreRectangle;
}

RectangleShape TrucoGame::View::ScoreView::getRectangleDivWidth()
{
    return rectangleDivWidth;
}

RectangleShape TrucoGame::View::ScoreView::getRectangleDivHeight()
{
    return rectangleDivHeight;
}

CircleShape TrucoGame::View::ScoreView::getOurCircles(size_t index)
{
    return ourCircles[index];
}

CircleShape TrucoGame::View::ScoreView::getTheirCircles(size_t index)
{
    return theirCircles[index];
}

TrucoGame::View::TextView TrucoGame::View::ScoreView::getRoundScoreText()
{
    return *roundScoreText;
}

TrucoGame::View::TextView TrucoGame::View::ScoreView::getWeScoreText()
{
    return *weScoreText;
}

TrucoGame::View::TextView TrucoGame::View::ScoreView::getTheyScoreText()
{
    return *theyScoreText;
}

TrucoGame::View::TextView TrucoGame::View::ScoreView::getWeText()
{
    return *weText;
}

TrucoGame::View::TextView TrucoGame::View::ScoreView::getTheyText()
{
    return *theyText;
}

void TrucoGame::View::ScoreView::changeGameScoreText(int team0Score, int team1Score)
{
    weScoreText->setString(std::to_string(team0Score));
    theyScoreText->setString(std::to_string(team1Score));
}

void TrucoGame::View::ScoreView::changeRoundScoreText(int newRoundScore)
{
    if (newRoundScore == 12) { 
        roundScoreText->setPosition(rectangleDivHeight.getPosition().x + spacingScoreTextWidth / 2, roundScoreTextPosition.y);
    }
    else {
        roundScoreText->setPosition(rectangleDivHeight.getPosition().x + spacingScoreTextWidth, roundScoreTextPosition.y);
    }
    roundScoreText->setString(std::to_string(newRoundScore));
}

void TrucoGame::View::ScoreView::updateScoreColor()
{
    ourCircles[0].setFillColor(Color::Green);
    theirCircles[0].setFillColor(Color::Red);;
}

void TrucoGame::View::ScoreView::setTextsFont(const std::string& fontPath)
{
    this->textsFont = UtilsView::loadFont(fontPath);
}

void TrucoGame::View::ScoreView::initializeTexts(const float scoreRectangleWidth)
{
    roundScoreText = new TextView("1", CALCULATE_SCORE_TEXT_CHARACTER_SIZE, scoreRectangleWidth, BORDER_COLOR, Text::Regular);
    weScoreText = new TextView("0", CALCULATE_WE_AND_THEY_TEXT_CHARACTER_SIZE, scoreRectangleWidth, BORDER_COLOR, Text::Regular);
    theyScoreText = new TextView("0", CALCULATE_WE_AND_THEY_TEXT_CHARACTER_SIZE, scoreRectangleWidth, BORDER_COLOR, Text::Regular);
    weText = new TextView("Nós", CALCULATE_WE_AND_THEY_TEXT_CHARACTER_SIZE, scoreRectangleWidth, BORDER_COLOR, Text::Regular);
    theyText = new TextView("Eles", CALCULATE_WE_AND_THEY_TEXT_CHARACTER_SIZE, scoreRectangleWidth, BORDER_COLOR, Text::Regular);
}


void TrucoGame::View::ScoreView::setTextsPosition(float scoreRectangleXPosition, float scoreRectangleYPosition, float rectangleWidthToCircles, float rectangleScoreHeight, float textsWidth)
{
    spacingScoreTextWidth = (textsWidth - roundScoreText->getTextWidth()) / 2;
    float spacingWeScoreTextWidth = (textsWidth - weScoreText->getTextWidth()) / 2;
    float spacingTheyScoreTextWidth = (textsWidth - theyScoreText->getTextWidth()) / 2;
    float spacingWeTextWidth = (textsWidth - weText->getTextWidth()) / 2;
    float spacingTheyTextWidth = (textsWidth - theyText->getTextWidth()) / 2;

    float rectangleDivWidthYPosition = rectangleDivWidth.getPosition().y;
    float rectangleToWeAndTheyHeight = (rectangleDivWidthYPosition - scoreRectangleYPosition);

    float spacingScoreTextHeight = (rectangleScoreHeight - roundScoreText->getTextHeight()) / 2 - 10;
    float spacingWeScoreTextHeight = (rectangleToWeAndTheyHeight - weScoreText->getTextHeight()) / 2 - 6;
    float spacingTheyScoreTextHeight = (rectangleToWeAndTheyHeight - theyScoreText->getTextHeight()) / 2 - 6;
    float spacingWeTextHeight = (rectangleToWeAndTheyHeight - weText->getTextHeight()) / 2 - 6;
    float spacingTheyTextHeight = (rectangleToWeAndTheyHeight - theyText->getTextHeight()) / 2 - 6;
       
    roundScoreTextPosition = Vector2f(rectangleDivHeight.getPosition().x + spacingScoreTextWidth + spacingScoreTextWidth, scoreRectangleYPosition + spacingScoreTextHeight);
    roundScoreText->setPosition(roundScoreTextPosition);

    weScoreText->setPosition(Vector2f(rectangleDivHeight.getPosition().x + spacingScoreTextWidth, scoreRectangleYPosition + spacingWeScoreTextHeight));
    theyScoreText->setPosition(Vector2f(rectangleDivHeight.getPosition().x + spacingScoreTextWidth, rectangleDivWidthYPosition + spacingTheyScoreTextHeight));

    weText->setPosition(Vector2f(scoreRectangleXPosition + spacingWeTextWidth, scoreRectangleYPosition + spacingWeTextHeight));
    theyText->setPosition(Vector2f(scoreRectangleXPosition + spacingTheyTextWidth, rectangleDivWidthYPosition + spacingTheyTextHeight));
}

