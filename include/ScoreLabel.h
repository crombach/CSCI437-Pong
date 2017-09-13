//
// Created by cullen on 9/12/17.
//

#ifndef TEXTLABEL_H
#define TEXTLABEL_H


#include <SFML/Graphics/Text.hpp>

class ScoreLabel : public sf::Text {
    uint score;
private:
    // Helper methods.
    void updateOrigin();
public:
    // Constructor
    ScoreLabel(float x, float y, sf::Font *font);
    // Scoring methods.
    uint getScore();
    void increment();
    void reset();
};


#endif //TEXTLABEL_H
