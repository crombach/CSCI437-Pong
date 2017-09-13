//
// Created by cullen on 9/12/17.
//

#ifndef BALL_H
#define BALL_H


#include <SFML/Graphics/CircleShape.hpp>
#include "Actor.h"

class Ball : public Actor {
    float dx; // x axis speed
    float dy; // y axis speed
public:
    // Constructors.
    Ball(float x, float y);
    Ball(float x, float y, sf::CircleShape shape);
    // Movement methods.
    void setDx(float dx);
    void setDy(float dy);
    void bounceX();
    void bounceY();
    void move();
};


#endif //BALL_H
