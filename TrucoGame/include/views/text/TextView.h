#ifndef TEXT_VIEW_H
#define TEXT_VIEW_H

#include <SFML/Graphics.hpp>
#include "../utils/UtilsView.h"

// File path for the Arial.ttf font used for names
#define NAME_FONT_PATH "../../../../TrucoGame/resources/fonts/Arial.ttf"

namespace TrucoGame {
    namespace View {
        class TextView : public sf::Text {

        private:
            sf::Font font;
            std::string text;
            float width, height;

            void setFontFromPath(const std::string& fontPath);
            
        public:
            TextView(const std::string& text, float constantToCalculateCharacterSize, float referenceMeasureToCalculateCharacterSize, Color textColor, Uint32 style);
            ~TextView();

            void setText(std::string text);
            float getTextWidth() const;
            float getTextHeight() const;
            float getHalfTextWidth() const;
        };
    }
}
#endif // TEXT_VIEW_H