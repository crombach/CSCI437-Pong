//
// Created by cullen on 9/13/17.
//

#ifndef TEXTUTILS_H
#define TEXTUTILS_H


#include <SFML/Graphics/Text.hpp>

class TextUtils {
public:
    static void centerTextOrigin(sf::Text *text);
    static void centerTwoTexts(sf::Text *top, sf::Text *bottom);
};


#endif //TEXTUTILS_H
