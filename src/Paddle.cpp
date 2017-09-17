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
    speed = GC::HEIGHT;

    // Set AI variables.
    direction = STATIC;
    secondsSinceAIRecalculation = 0.f;
}

// Use a custom rectangle shape for the paddle.
Paddle::Paddle(float x, float y, sf::RectangleShape shape) : RectangleShape(shape) {
    // Set x and y position.
    setPosition(x,y);

    // Set default speed.
    speed = GC::HEIGHT;

    // Set AI variables.
    direction = STATIC;
    secondsSinceAIRecalculation = 0.f;
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
void Paddle::moveAsAI(float deltaTime, float ballDy, sf::Vector2f ballPosition) {
    // Only recalculate the AI if it has been more than 0.15 seconds.
    if (secondsSinceAIRecalculation < 0.15) {
        secondsSinceAIRecalculation += deltaTime;
        return;
    } else {
        // If the ball is above the paddle, move up.
        if (ballPosition.y < (getPosition().y - (getLocalBounds().height / 2.f))) {
            direction = UP;
        }
        // If the ball is below the paddle, move down.
        else if (ballPosition.y > (getPosition().y + (getLocalBounds().height / 2.f))) {
            direction = DOWN;
        }
        // If the ball is across from the paddle...
        else {
            // If the ball is moving up at at least 2/3 the paddle's speed, move up.
            if (ballDy < 0 && (ballDy < -(speed / 1.5f))) {
                direction = UP;
            }
            // If the ball is moving down at at least 2/3 the paddle's speed, move down.
            else if (ballDy > 0 && (ballDy > (speed / 1.5f))) {
                direction = DOWN;
            }
            // Otherwise, don't move.
            else {
                direction = STATIC;
            }
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
