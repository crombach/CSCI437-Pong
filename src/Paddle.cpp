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
    speed = GC::HEIGHT * (2.f / 3.f);

    // Set AI direction.
    direction = STATIC;
}

// Use a custom rectangle shape for the paddle.
Paddle::Paddle(float x, float y, sf::RectangleShape shape) : RectangleShape(shape) {
    // Set x and y position.
    setPosition(x,y);

    // Set default speed.
    speed = GC::HEIGHT * (2.f / 3.f);

    // Set AI direction.
    direction = STATIC;
}

void Paddle::moveUp(float deltaTime) {
    // Set direction flag.
    direction = UP;
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
    // Set direction flag.
    direction = DOWN;
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

void Paddle::noMove() {
    // Just set direction flag.
    direction = STATIC;
}

float Paddle::getSpeed() {
    return speed;
}

// AI-controlled movement. Takes ball position and tries to move to it.
void Paddle::moveAsAI(float deltaTime, float ballDx, float ballDy, sf::Vector2f ballPosition, bool recalculate) {
    // If recalculate flag is set, need to recalculate direction to move.
    if (recalculate) {
        // If the paddle's center is above the ball, move down.
        if (ballPosition.y > getPosition().y) {
            direction = DOWN;
        }
        // If the paddle's center is below the ball, move up.
        else if (ballPosition.y < getPosition().y) {
            direction = UP;
        }
    }

    // Actually move the paddle.
    if (direction == DOWN) {
        moveDown(deltaTime);
    }
    else if (direction == UP) {
        moveUp(deltaTime);
    }
}

// Reset the paddle to starting position.
void Paddle::reset(bool left) {
    if (left) {
        setPosition(GC::WIDTH / 80.f, GC::HEIGHT / 2.f);
    }
    else {
        setPosition(GC::WIDTH - (GC::WIDTH / 80.f), GC::HEIGHT / 2.f);
    }
}

Direction Paddle::getDirection() {
    return direction;
}
