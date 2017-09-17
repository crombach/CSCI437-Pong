//
// Created by cullen on 9/12/17.
//

#ifndef BALL_H
#define BALL_H


#include <SFML/Graphics/CircleShape.hpp>
#include <Paddle.h>

class Ball : public sf::CircleShape {
private:
    float dx; // x axis speed
    float dy; // y axis speed
    void randomizeMovement();
public:
    // Constructors.
    Ball(float x, float y);
    Ball(float x, float y, sf::CircleShape shape);
    // Movement methods.
    void bounceX();
    void bounceY();
    void move(float deltaTime, Paddle &leftPaddle, Paddle &rightPaddle);
    void reset();
    void paddleHit(Paddle paddle);
    // Getters/setters
    void setDx(float dx);
    float getDx();
    void setDy(float dy);
    float getDy();
};


#endif //BALL_H
