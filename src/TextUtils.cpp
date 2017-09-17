//
// Created by cullen on 9/13/17.
//

#include <GC.h>
#include <TextUtils.h>

// Calculate a central origin for the given Text object.
void TextUtils::centerTextOrigin(sf::Text &text) {
    sf::FloatRect localBounds = text.getLocalBounds();
    text.setOrigin(localBounds.left + (localBounds.width / 2), localBounds.top + (localBounds.height / 2));
}

// Take two Text objects and center them.
void TextUtils::centerTwoTexts(sf::Text &top, sf::Text &bottom) {
    top.setPosition(GC::WIDTH / 2, (GC::HEIGHT / 2) - top.getLocalBounds().height);
    bottom.setPosition(GC::WIDTH / 2, (GC::HEIGHT / 2) + bottom.getLocalBounds().height);
}