//
// Created by cullen on 9/12/17.
//

#include <Paddle.h>
#include <GC.h>

// Build a default paddle.
// Default paddles are white and use 1/32 of the screen's width and 1/6th of its height.
Paddle::Paddle(float x, float y) {
    // Build default shape.
    sf::Vector2f dimensions = sf::Vector2f(GC::WIDTH / 40.f, GC::HEIGHT / 6.f);
    setSize(dimensions);
    setFillColor(sf::Color::White);
    setOrigin(dimensions / 2.f);
    setPosition(x, y);

    // Set default speed.
    speed = 300;
}

// Use a custom rectangle shape for the paddle.
Paddle::Paddle(float x, float y, sf::RectangleShape shape) : RectangleShape(shape) {
    // Set x and y position.
    setPosition(x,y);

    // Set default speed.
    speed = 300;
}

void Paddle::moveUp(float deltaTime) {
    // Calculate movement distance.
    float distance = deltaTime * speed;
    // Don't let the paddle move off-screen.
    sf::FloatRect bounds = getGlobalBounds();
    float top = bounds.top;
    if (top - distance <= 0) {
        move(0, -top);
    } else {
        move(0, -distance);
    }
}

void Paddle::moveDown(float deltaTime) {
    // Calculate movement distance.
    float distance = deltaTime * speed;
    // Don't let the paddle move off-screen.
    sf::FloatRect bounds = getGlobalBounds();
    float bottom = bounds.top + bounds.height;
    if (bottom + distance >= GC::HEIGHT) {
        move(0, GC::HEIGHT - bottom);
    } else {
        move(0, distance);
    }
}

float Paddle::getSpeed() {
    return speed;
}

void Paddle::setSpeed(float speed) {
    this->speed = speed;
}

// AI-controlled movement. Takes ball position and tries to move to it.
void Paddle::moveAsAI(sf::Vector2f ballPosition, float deltaTime) {
    // If the paddle's center is above the ball, move down.
    if (ballPosition.y > getPosition().y) {
        moveDown(deltaTime);
    }
    // If the paddle's center is below the ball, move up.
    else if (ballPosition.y < getPosition().y) {
        moveUp(deltaTime);
    }
}

// Reset the paddle to starting position.
void Paddle::reset(bool player) {
    if (player) {
        setPosition(GC::WIDTH / 40.f, GC::HEIGHT / 2.f);
    }
    else {
        setPosition(GC::WIDTH - (GC::WIDTH / 40.f), GC::HEIGHT / 2.f);
    }
}
