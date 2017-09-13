//
// Created by cullen on 9/12/17.
//

#ifndef BALL_H
#define BALL_H


#include <SFML/Graphics/CircleShape.hpp>
#include "Paddle.h"

class Ball : public sf::CircleShape {
    float dx; // x axis speed
    float dy; // y axis speed
private:
    void randomizeMovement();
public:
    // Constructors.
    Ball(float x, float y);
    Ball(float x, float y, sf::CircleShape shape);
    // Movement methods.
    void setDx(float dx);
    void setDy(float dy);
    void bounceX();
    void bounceY();
    void move(float deltaTime, Paddle *leftPaddle, Paddle *rightPaddle);
    void reset();
};


#endif //BALL_H
