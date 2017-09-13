//
// Created by cullen on 9/12/17.
//

#include <GC.h>
#include <ScoreLabel.h>

ScoreLabel::ScoreLabel(float x, float y, sf::Font *font) {
    // Set initial score to zero.
    score = 0;

    // Set text properties.
    setFont(*font);
    setCharacterSize(GC::HEIGHT / 5.f);
    setColor(sf::Color(40, 40, 40));
    setString(std::to_string(score));

    // Handle size and positioning
    updateOrigin();
    setPosition(x, y);
}

void ScoreLabel::increment() {
    score++;
    setString(std::to_string(score));
    updateOrigin();
}

void ScoreLabel::reset() {
    score = 0;
    setString(std::to_string(score));
    updateOrigin();
}

void ScoreLabel::updateOrigin() {
    sf::FloatRect dimensions = getLocalBounds();
    setOrigin(dimensions.width / 2.f, dimensions.height / 2.f);
}
