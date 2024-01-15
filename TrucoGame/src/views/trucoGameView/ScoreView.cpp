#include "../../../include/views/trucoGameView/ScoreView.h"
#include "../../../include/views/UtilsView.h"

void TrucoGame::View::ScoreView::createScoreRectangle(float scoreRectangleXPosition, float scoreRectangleYPosition, Vector2f& scoreRectangleDimensions, std::shared_ptr<float>& rectangleWidthToCircles, std::shared_ptr<float>& rectangleScoreHeight, std::shared_ptr<float>& textsWidth)
{
    scoreRectangle.setSize(sf::Vector2f(scoreRectangleDimensions));
    scoreRectangle.setPosition(scoreRectangleXPosition, scoreRectangleYPosition);
    scoreRectangle.setFillColor(SCORE_RECTANGLE_BACKGROUNG);
    scoreRectangle.setOutlineColor(BORDER_COLOR); 
    scoreRectangle.setOutlineThickness(BORDER_THICKNESS);

    float rectangleScoreWidth = scoreRectangle.getGlobalBounds().width;
    *rectangleScoreHeight = scoreRectangle.getGlobalBounds().height;
    *textsWidth = rectangleScoreWidth / 5;
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

    for (int i = 0; i < numRounds; i++) {
        ourCircles[i].setRadius(CIRCLE_RADIUS);
        theirCircles[i].setRadius(CIRCLE_RADIUS);

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

TrucoGame::View::ScoreView::ScoreView()
{
    float scoreRectangleXPosition = SCORE_RECTANGLE_X_POSITION;
    float scoreRectangleYPosition = SCORE_RECTANGLE_Y_POSITION;
    Vector2f& scoreRectangleDimensions(SCORE_RECTANGLE_DIMENSIONS);
    std::shared_ptr<float> rectangleWidthToCirclesPtr = std::make_shared<float>();
    std::shared_ptr<float> rectangleScoreHeight = std::make_shared<float>();
    std::shared_ptr<float> textsWidth = std::make_shared<float>();

    createScoreRectangle(scoreRectangleXPosition, scoreRectangleYPosition, scoreRectangleDimensions, rectangleWidthToCirclesPtr, rectangleScoreHeight, textsWidth);
    createCirclesInScoreRectangle(*rectangleWidthToCirclesPtr - *textsWidth, *rectangleScoreHeight, scoreRectangleXPosition + *textsWidth, scoreRectangleYPosition);
    initializeTexts();
    setTextsPosition(scoreRectangleXPosition, scoreRectangleYPosition, *rectangleWidthToCirclesPtr, *rectangleScoreHeight, *textsWidth);
}

TrucoGame::View::ScoreView::~ScoreView()
{
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

Text TrucoGame::View::ScoreView::getRoundScoreText()
{
    return this->roundScoreText;
}

Text TrucoGame::View::ScoreView::getWeText()
{
    return this->weText;
}

Text TrucoGame::View::ScoreView::getTheyText()
{
    return this->theyText;
}

void TrucoGame::View::ScoreView::changeRoundScoreText(size_t newRoundScore)
{
    size_t roundScore = std::stoul(getRoundScoreText().getString().toAnsiString());
    if (roundScore != newRoundScore) {
        roundScoreText.setString(std::to_string(newRoundScore));
    }
}

void TrucoGame::View::ScoreView::setTextsFont(const std::string& fontPath)
{
    this->textsFont = UtilsView::loadFont(fontPath);
}

void TrucoGame::View::ScoreView::setTextsColor()
{
    this->roundScoreText.setFillColor(BORDER_COLOR);
    this->weText.setFillColor(BORDER_COLOR);
    this->theyText.setFillColor(BORDER_COLOR);
}


void TrucoGame::View::ScoreView::initializeTexts()
{
    setTextsFont(NAME_FONT_PATH);

    roundScoreText = sf::Text(std::to_string(0), textsFont, SCORE_TEXT_CHARACTER_SIZE);
    weText = sf::Text("Nós", textsFont, WE_AND_THEY_TEXT_CHARACTER_SIZE);
    theyText = sf::Text("Eles", textsFont, WE_AND_THEY_TEXT_CHARACTER_SIZE);

    roundScoreText.setFillColor(BORDER_COLOR);
    weText.setFillColor(BORDER_COLOR);
    theyText.setFillColor(BORDER_COLOR);

    roundScoreTextWidth = roundScoreText.getLocalBounds().width;
    weTextWidth = weText.getGlobalBounds().width;
    theyTextWidth = theyText.getGlobalBounds().width;

    roundScoreTextHeight = roundScoreText.getGlobalBounds().height;
    weTextHeight = weText.getGlobalBounds().height;
    theyTextHeight = theyText.getGlobalBounds().height;
}


void TrucoGame::View::ScoreView::setTextsPosition(float scoreRectangleXPosition, float scoreRectangleYPosition, float rectangleWidthToCircles, float rectangleScoreHeight, float textsWidth)
{
    float spacingScoreTextWidth = (textsWidth - roundScoreTextWidth) / 2;
    float spacingWeTextWidth = (textsWidth - weTextWidth) / 2;
    float spacingTheyTextWidth = (textsWidth - theyTextWidth) / 2;

    float rectangleDivWidthYPosition = rectangleDivWidth.getPosition().y;
    float rectangleToWeAndTheyHeight = (rectangleDivWidthYPosition - scoreRectangleYPosition);

    float spacingScoreTextHeight = (rectangleScoreHeight - roundScoreTextHeight) / 2 - 10;
    float spacingWeTextHeight = (rectangleToWeAndTheyHeight - weTextHeight) / 2 - 6;
    float spacingTheyTextHeight = (rectangleToWeAndTheyHeight - theyTextHeight) / 2 - 6;

    roundScoreText.setPosition(Vector2f(rectangleDivHeight.getPosition().x + spacingScoreTextWidth, scoreRectangleYPosition + spacingScoreTextHeight));
    weText.setPosition(Vector2f(scoreRectangleXPosition + spacingWeTextWidth, scoreRectangleYPosition + spacingWeTextHeight));
    theyText.setPosition(Vector2f(scoreRectangleXPosition + spacingTheyTextWidth, rectangleDivWidthYPosition + spacingTheyTextHeight));
}

