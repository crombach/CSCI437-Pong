//
// Created by cullen on 9/12/17.
//

#include "Ball.h"
#include "GC.h"

// Build a default ball.
// Default balls are white and have a radius of 1/60th the screen's width.
Ball::Ball(float x, float y) : Actor(x, y, nullptr) {
    sf::CircleShape shape;
    shape.setRadius(GC::WIDTH / 60.f);
    shape.setFillColor(sf::Color::White);
    shape.setOrigin(shape.getRadius()/2.f, shape.getRadius()/2.f);
    shape.setPosition(x, y);
    setShape(&shape);
}

// Use a custom circle shape for the ball..
Ball::Ball(float x, float y, sf::CircleShape shape) : Actor(x, y, &shape) {}

void Ball::setDx(float dx) {
    this->dx = dx;
};

void Ball::setDy(float dy) {
    this->dy = dy;
};

void Ball::bounceX() {
    dx = -dx;
}

void Ball::bounceY() {
    dy = -dy;
}

void Ball::move() {
    Actor::move(dx, dy);
}