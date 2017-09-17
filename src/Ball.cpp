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

float Ball::getDx() {
    return dx;
}

void Ball::setDx(float dx) {
    this->dx = dx;
}

float Ball::getDy() {
    return dy;
}

void Ball::setDy(float dy) {
    this->dy = dy;
}

void Ball::bounceX() {
    // Set up a random number generator and distributions.
    // The ball should speed up over time.
    std::default_random_engine randomEngine(std::random_device{}());
    std::uniform_real_distribution<float> perturbationDistribution(-5, 20);
    float deltaDx = perturbationDistribution(randomEngine);

    // Add a small random perturbation.
    if (dx < 0) {
        dx = -(dx - deltaDx);
    }
    else {
        dx = -(dx + deltaDx);
    }
}

void Ball::bounceY() {
    // Set up a random number generator and distributions.
    // The ball should speed up over time.
    std::default_random_engine randomEngine(std::random_device{}());
    std::uniform_real_distribution<float> perturbationDistribution(-5, 20);
    float deltaDy = perturbationDistribution(randomEngine);

    // Add a small random perturbation.
    if (dy < 0) {
        dy = -(dy - deltaDy);
    }
    else {
        dy = -(dy + deltaDy);
    }
}

void Ball::move(float deltaTime, Paddle &leftPaddle, Paddle &rightPaddle) {
    // Calculate movement distance.
    float xDistance = deltaTime * dx;
    float yDistance = deltaTime * dy;

    // Move.
    sf::CircleShape::move(xDistance, yDistance);

    // Check for paddle hits.
    // Left paddle.
    switch (CollisionUtils::check(*this, leftPaddle)) {
        case RIGHT : {
            bounceX();
            float newX = leftPaddle.getGlobalBounds().left + leftPaddle.getGlobalBounds().width + getRadius() + .1f;
            setPosition(newX, getPosition().y);
            paddleHit(leftPaddle);
            break;
        }
        case TOP : {
            bounceY();
            float newY = leftPaddle.getGlobalBounds().top - getRadius() - .1f;
            setPosition(getPosition().x, newY);
            paddleHit(leftPaddle);
            break;
        }
        case TOP_RIGHT : {
            bounceX();
            paddleHit(leftPaddle);
            break;
        }
        case BOTTOM : {
            bounceY();
            float newY = leftPaddle.getGlobalBounds().top + leftPaddle.getGlobalBounds().height + getRadius() + .1f;
            setPosition(getPosition().x, newY);
            paddleHit(leftPaddle);
            break;
        }
        case BOTTOM_RIGHT : {
            bounceX();
            paddleHit(leftPaddle);
            break;
        }
        default : break;
    }
    // Right paddle.
    switch (CollisionUtils::check(*this, rightPaddle)) {
        case LEFT : {
            bounceX();
            float newX = rightPaddle.getGlobalBounds().left - getRadius() - .1f;
            setPosition(newX, getPosition().y);
            paddleHit(rightPaddle);
            break;
        }
        case TOP : {
            bounceY();
            float newY = rightPaddle.getGlobalBounds().top - getRadius() - .1f;
            setPosition(getPosition().x, newY);
            paddleHit(rightPaddle);
            break;
        }
        case TOP_LEFT : {
            bounceX();
            paddleHit(rightPaddle);
            break;
        }
        case BOTTOM : {
            bounceY();
            float newY = rightPaddle.getGlobalBounds().top + rightPaddle.getGlobalBounds().height + getRadius() + .1f;
            setPosition(getPosition().x, newY);
            paddleHit(rightPaddle);
            break;
        }
        case BOTTOM_LEFT : {
            bounceX();
            paddleHit(rightPaddle);
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
    std::uniform_real_distribution<float> speedDistribution((GC::WIDTH / 2.5f), ((GC::WIDTH / 2.5f) + (GC::WIDTH / 16.f)));
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

/*
 * When the ball hits a paddle, take the speed and direction of the paddle into account
 * when the ball bounces. That way, the player has some control over the ball's direction.
 * The paddle speed has a set factor on the y-speed of the ball.
 * Also, the closer the ball hits to the end of the paddle the more its x-speed will increase.
 * Hitting the middle half of the paddle will slow the ball's x-speed.
 */
void Ball::paddleHit(Paddle paddle) {
    // Set speed factors.
    float verticalSpeedFactor = 0.2f;
    float horizontalSpeedFactor = 0.25f;

    // If the ball and paddle are moving the same direction, speed the ball up.
    if ((dy > 0) && (paddle.getDirection() == DOWN)) {
        dy += paddle.getSpeed() * verticalSpeedFactor;
    }
    else if ((dy < 0) && (paddle.getDirection() == UP)) {
        dy -= paddle.getSpeed() * verticalSpeedFactor;
    }
    // If the ball and paddle are moving opposite directions, speed the ball down.
    else if ((dy > 0) && (paddle.getDirection() == UP)) {
        dy -= paddle.getSpeed() * verticalSpeedFactor;
    }
    else if ((dy < 0) && (paddle.getDirection() == DOWN)) {
        dy += paddle.getSpeed() * verticalSpeedFactor;
    }

    // Check how far the ball hit from the center of the ball.
    float distanceFromCenter = std::abs(getPosition().y - paddle.getPosition().y);
    // Hitting the middle half of the paddle slows the ball down.
    if (distanceFromCenter < (paddle.getLocalBounds().height / 4.f)) {
        if (dx > 0) {
            dx -= (paddle.getLocalBounds().height - distanceFromCenter) * horizontalSpeedFactor;
        }
        else {
            dx += (paddle.getLocalBounds().height - distanceFromCenter) * horizontalSpeedFactor;
        }
    }
    // Hitting the outer two quarters of the paddle speeds the ball up.
    else {
        if (dx > 0) {
            dx += distanceFromCenter * horizontalSpeedFactor;
        }
        else {
            dx -= distanceFromCenter * horizontalSpeedFactor;
        }
    }
}
