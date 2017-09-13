//
// Created by cullen on 9/12/17.
//

#include "Paddle.h"
#include "GC.h"

// Build a default paddle.
// Default paddles are white and use 1/32 of the screen's width and 1/6th of its height.
Paddle::Paddle(float x, float y) : Actor(x, y, nullptr) {
    // Build default shape.
    sf::RectangleShape shape;
    sf::Vector2f dimensions = sf::Vector2f(GC::WIDTH / 32.f, GC::HEIGHT / 6.f);
    shape.setSize(dimensions);
    shape.setFillColor(sf::Color::White);
    shape.setOrigin(dimensions / 2.f);
    shape.setPosition(x, y);
    setShape(&shape);
    // Set default speed.
    speed = 10;
}

// Use a custom rectangle shape for the paddle.
Paddle::Paddle(float x, float y, sf::RectangleShape shape) : Actor(x, y, &shape) {
    // Set default speed.
    speed = 10;
}

void Paddle::moveUp(float distance) {
    move(0, -distance);
}

void Paddle::moveDown(float distance) {
    move(0, distance);
}

float Paddle::getSpeed() {
    return speed;
}

void Paddle::setSpeed(float speed) {
    this->speed = speed;
}
