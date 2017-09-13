//
// Created by cullen on 9/12/17.
//

#include <Ball.h>
#include <GC.h>
#include <CollisionUtils.h>

// Build a default ball.
// Default balls are white and have a radius of 1/60th the screen's width.
Ball::Ball(float x, float y) {
    // Build default shape.
    setRadius(GC::WIDTH / 80.f);
    setFillColor(sf::Color::White);
    setOrigin(getRadius(), getRadius());
    setPosition(x, y);

    // Generate a random starting speed vector.
    randomizeMovement();
}

// Use a custom circle shape for the ball..
Ball::Ball(float x, float y, sf::CircleShape shape) : CircleShape(shape) {
    // Set position.
    setPosition(x, y);

    // Generate a random starting speed vector.
    randomizeMovement();
}

void Ball::setDx(float dx) {
    this->dx = dx;
};

void Ball::setDy(float dy) {
    this->dy = dy;
};

void Ball::bounceX() {
    // Set up a random number generator and distributions.
    std::default_random_engine randomEngine(std::random_device{}());
    std::uniform_real_distribution<float> perturbationDistribution(-20, 20);
    float deltaDx = perturbationDistribution(randomEngine);

    // Add a small random perturbation.
    dx = -(dx + deltaDx);
}

void Ball::bounceY() {
    // Set up a random number generator and distributions.
    std::default_random_engine randomEngine(std::random_device{}());
    std::uniform_real_distribution<float> perturbationDistribution(-20, 20);
    float deltaDy = perturbationDistribution(randomEngine);

    // Add a small random perturbation.
    dy = -(dy + deltaDy);
}

void Ball::move(float deltaTime, Paddle *leftPaddle, Paddle *rightPaddle) {
    // Calculate movement distance.
    float xDistance = deltaTime * dx;
    float yDistance = deltaTime * dy;

    // Move.
    sf::CircleShape::move(xDistance, yDistance);

    // Check for paddle hits.
    // Left paddle.
    switch (CollisionUtils::check(this, leftPaddle)) {
        case RIGHT : {
            bounceX();
            float newX = leftPaddle->getGlobalBounds().left + leftPaddle->getGlobalBounds().width + getRadius() + .1f;
            setPosition(newX, getPosition().y);
            break;
        }
        case TOP : {
            bounceY();
            float newY = leftPaddle->getGlobalBounds().top - getRadius() - .1f;
            setPosition(getPosition().x, newY);
            break;
        }
        case TOP_RIGHT : {
            bounceX();
            break;
        }
        case BOTTOM : {
            bounceY();
            float newY = leftPaddle->getGlobalBounds().top + leftPaddle->getGlobalBounds().height + getRadius() + .1f;
            setPosition(getPosition().x, newY);
            break;
        }
        case BOTTOM_RIGHT : {
            bounceX();
            break;
        }
        default : break;
    }
    // Right paddle.
    switch (CollisionUtils::check(this, rightPaddle)) {
        case LEFT : {
            bounceX();
            float newX = rightPaddle->getGlobalBounds().left - getRadius() - .1f;
            setPosition(newX, getPosition().y);
            break;
        }
        case TOP : {
            bounceY();
            float newY = rightPaddle->getGlobalBounds().top - getRadius() - .1f;
            setPosition(getPosition().x, newY);
            break;
        }
        case TOP_LEFT : {
            bounceX();
            break;
        }
        case BOTTOM : {
            bounceY();
            float newY = rightPaddle->getGlobalBounds().top + rightPaddle->getGlobalBounds().height + getRadius() + .1f;
            setPosition(getPosition().x, newY);
            break;
        }
        case BOTTOM_LEFT : {
            bounceX();
            break;
        }
        default : break;
    }

    // Don't let the ball move off-screen on the top or bottom.
    if ((getPosition().y - getRadius()) <= 0) {
        // Collide with top.
        setPosition(getPosition().x, getRadius() + .1f);
        bounceY();
    } else if (getPosition().y + getRadius() >= GC::HEIGHT) {
        // Collide with bottom.
        setPosition(getPosition().x, GC::HEIGHT - getRadius() - .1f);
        bounceY();
    }
}

// Randomize ball movement. Helper method for constructors.
void Ball::randomizeMovement() {
    // Set up a random number generator and distributions.
    std::default_random_engine randomEngine(std::random_device{}());
    std::uniform_real_distribution<float> speedDistribution(360, 400);
    std::uniform_int_distribution<int> directionDistribution(0, 3);

    // Generate x and y speeds
    float dx = speedDistribution(randomEngine);
    float dy = speedDistribution(randomEngine);

    // Randomize direction (4 possibilities).
    int direction = directionDistribution(randomEngine);
    switch(direction) {
        case 0 :
            dx = -dx;
            break;
        case 1:
            dy = -dy;
            break;
        case 2:
            dx = -dx;
            dy = -dy;
            break;
        default: break; // Do nothing. Both stay positive.
    }

    // Set speeds to generated numbers.
    setDx(dx);
    setDy(dy);
}

// Reset ball position to the origin and generate new directions.
void Ball::reset() {
    setPosition(GC::WIDTH / 2.f, GC::HEIGHT / 2.f);
    randomizeMovement();
}
