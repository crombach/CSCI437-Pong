//
// Created by cullen on 9/12/17.
//

#include <GC.h>
#include <ScoreLabel.h>
#include <TextUtils.h>

ScoreLabel::ScoreLabel(float x, float y, sf::Font *font) {
    // Set initial score to zero.
    score = 0;

    // Set text properties.
    setFont(*font);
    setCharacterSize(GC::HEIGHT / 5);
    setColor(sf::Color(80, 80, 80));
    setString(std::to_string(score));

    // Handle size and positioning
    TextUtils::centerTextOrigin(this);
    setPosition(x, y);
}

void ScoreLabel::increment() {
    score++;
    setString(std::to_string(score));
    TextUtils::centerTextOrigin(this);
}

void ScoreLabel::reset() {
    score = 0;
    setString(std::to_string(score));
    TextUtils::centerTextOrigin(this);
}

uint ScoreLabel::getScore() {
    return score;
}
