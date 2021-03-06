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

// Take two Text objects and center them together.
void TextUtils::centerTwoTexts(sf::Text &top, sf::Text &bottom) {
    float topHeight = top.getLocalBounds().height;
    float bottomHeight = bottom.getLocalBounds().height;
    top.setPosition(GC::WIDTH / 2, (GC::HEIGHT / 2) - ((bottomHeight / 2.f) + 10.f));
    bottom.setPosition(GC::WIDTH / 2, (GC::HEIGHT / 2) + ((topHeight / 2.f) + 10.f));
}