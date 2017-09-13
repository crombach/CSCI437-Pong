//
// Created by cullen on 9/12/17.
//

#include <GC.h>
#include "ScoreLabel.h"

ScoreLabel::ScoreLabel(float x, float y, sf::Font font) {
    // Set initial score to zero.
    score = 0;

    // Set text properties.
    setFont(font);
    setCharacterSize(GC::HEIGHT / 20.f);
    setColor(sf::Color(80, 80, 80));
    setString(score);

    // Handle size and positioning
    setPosition(x, y);
    updateOrigin();
}

void ScoreLabel::increment() {
    score++;
    setString(score);
    updateOrigin();
}

void ScoreLabel::reset() {
    score = 0;
    setString(score);
    updateOrigin();
}

void ScoreLabel::updateOrigin() {
    sf::FloatRect dimensions = getLocalBounds();
    setOrigin(dimensions.width / 2.f, dimensions.height / 2.f);
}
