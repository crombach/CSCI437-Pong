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
    // Set up a random number generator and distributions.
    std::default_random_engine randomEngine(std::random_device{}());
    std::uniform_real_distribution<float> perturbationDistribution(-5, 5);
    float deltaDx = perturbationDistribution(randomEngine);
    float deltaDy = perturbationDistribution(randomEngine);

    // Add a small random perturbation.
    dx = -(dx + deltaDx);
    dy = dy + deltaDy;
}

void Ball::bounceY() {
    // Set up a random number generator and distributions.
    std::default_random_engine randomEngine(std::random_device{}());
    std::uniform_real_distribution<float> perturbationDistribution(-5, 5);
    float deltaDx = perturbationDistribution(randomEngine);
    float deltaDy = perturbationDistribution(randomEngine);

    // Add a small random perturbation.
    dy = -(dy + deltaDy);
    dx = dx + deltaDx;
}

void Ball::move(float deltaTime, Paddle *playerPaddle, Paddle *aiPaddle) {
    // Calculate movement distance.
    float xDistance = deltaTime * dx;
    float yDistance = deltaTime * dy;

    // Store current position.
    float yPosition = getPosition().y;
    float top = yPosition - getRadius();
    float bottom = yPosition + getRadius();

    // Don't let the ball move off-screen on the top or bottom.
    if ((yDistance <= 0) && (top + yDistance <= 0)) {
        // Collide with top.
        sf::CircleShape::move(0, -top);
        bounceY();
    } else if ((yDistance > 0) && (bottom + yDistance >= GC::HEIGHT)) {
        // Collide with bottom.
        sf::CircleShape::move(xDistance, GC::HEIGHT - bottom);
        bounceY();
    }

    // Check for paddle hits.
    sf::FloatRect ballRect = getGlobalBounds();
    sf::FloatRect playerPaddleRect = playerPaddle->getGlobalBounds();
    sf::FloatRect aiPaddleRect = aiPaddle->getGlobalBounds();
    if (ballRect.intersects(playerPaddleRect)) {
        // Reverse direction.
        bounceX();
        // Move the ball so it doesn't intersect with the paddle anymore.
        float newX = (playerPaddle->getPosition().x) + (playerPaddle->getLocalBounds().width / 2.f) + (getLocalBounds().width/2.f) + 4.f;
        setPosition(newX, getPosition().y);
    }
    else if (ballRect.intersects(aiPaddleRect)) {
        // Reverse direction.
        bounceX();
        // Move the ball so it doesn't intersect with the paddle anymore.
        float newX = (aiPaddle->getPosition().x) - (aiPaddle->getLocalBounds().width / 2.f) - (getLocalBounds().width/2.f) - 4.f;
        setPosition(newX, getPosition().y);
    }

    // Move normally.
    sf::CircleShape::move(xDistance, yDistance);
}

// Randomize ball movement. Helper method for constructors.
void Ball::randomizeMovement() {
    // Set up a random number generator and distributions.
    std::default_random_engine randomEngine(std::random_device{}());
    std::uniform_real_distribution<float> speedDistribution(250, 300);
    std::uniform_int_distribution<int> directionDistribution(0, 3);

    // Generate x and y speeds in [250, 300]
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
