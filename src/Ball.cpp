//
// Created by cullen on 9/12/17.
//

#include <Ball.h>
#include <GC.h>

// Build a default ball.
// Default balls are white and have a radius of 1/60th the screen's width.
Ball::Ball(float x, float y) {
    // Build default shape.
    setRadius(GC::WIDTH / 60.f);
    setFillColor(sf::Color::White);
    setOrigin(getRadius()/2.f, getRadius()/2.f);
    setPosition(x, y);

    // Set speeds to zero for now.
    setDx(0);
    setDy(0);
}

// Use a custom circle shape for the ball..
Ball::Ball(float x, float y, sf::CircleShape shape) : CircleShape(shape) {
    // Set position.
    setPosition(x, y);

    // Set speeds to zero for now.
    setDx(0);
    setDy(0);
}

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
    sf::CircleShape::move(dx, dy);
}