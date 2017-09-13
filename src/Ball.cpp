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
    dx = -dx;
    // TODO: random perturbation.
}

void Ball::bounceY() {
    dy = -dy;
    // TODO: random perturbation.
}

void Ball::move(float deltaTime) {
    // Calculate movement distance.
    float xDistance = deltaTime * dx;
    float yDistance = deltaTime * dy;

    // Store current position.
    float yPosition = getPosition().y;
    float top = yPosition - getRadius();
    float bottom = yPosition + getRadius();

    // Don't let the ball move off-screen.
    // Top
    if (yDistance <= 0) {
        if (top + yDistance <= 0) {
            sf::CircleShape::move(0, -top);
            bounceY();
        } else {
            sf::CircleShape::move(0, yDistance);
        }
    }// Bottom
    else if (yDistance > 0) {
        if (bottom + yDistance >= GC::HEIGHT) {
            sf::CircleShape::move(xDistance, GC::HEIGHT - bottom);
            bounceY();
        } else {
            sf::CircleShape::move(xDistance, yDistance);
        }
    }

    // Move according to new speed vectors.
    sf::CircleShape::move(xDistance, yDistance);
    // TODO: Handle bounces.
}

// Randomize ball movement. Helper method for constructors.
void Ball::randomizeMovement() {
    // Set up a random number generator and distributions.
    std::default_random_engine randomEngine(std::random_device{}());
    std::uniform_real_distribution<float> speedDistribution(200, 250);
    std::uniform_int_distribution<int> directionDistribution(0, 3);

    // Generate x and y speeds in [200, 240]
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

    printf("dx: %lf\ndy: %lf\n", dx, dy);

    // Set speeds to generated numbers.
    setDx(dx);
    setDy(dy);
}
