//
// Created by cullen on 9/12/17.
//

#ifndef BALL_H
#define BALL_H


#include <SFML/Graphics/CircleShape.hpp>
#include <Paddle.h>
#include <memory>
#include <SFML/Audio/Sound.hpp>
using namespace std;

class Ball : public sf::CircleShape {
private:
    // Speed components
    float dx;
    float dy;
    // Sound effects.
    shared_ptr<sf::Sound> leftHit;
    shared_ptr<sf::Sound> rightHit;
    shared_ptr<sf::Sound> wallHit;
    // Helper methods.
    void randomizeMovement();
public:
    // Constructors.
    Ball(float x, float y, shared_ptr<sf::Sound> &leftHit, shared_ptr<sf::Sound> &rightHit, shared_ptr<sf::Sound> &wallHit);
    // Movement methods.
    void bounceX();
    void bounceY();
    void reset();
    void paddleHit(Paddle paddle);
    void move(float deltaTime, Paddle &leftPaddle, Paddle &rightPaddle);
    void moveAsGhostBall(float dTime, Paddle &leftPaddle, Paddle &rightPaddle, Ball &ball, float lastBallDx);
    // Getters/setters
    void setDx(float dx);
    float getDx();
    void setDy(float dy);
    float getDy();
};


#endif //BALL_H
