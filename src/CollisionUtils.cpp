//
// Created by cullen on 9/13/17.
//

#include <CollisionUtils.h>

/* Check for collision between a ball and a paddle.
 * This is done by checking if the ball's origin (center) is
 * within one ball radius of the paddle.
 */
Collision CollisionUtils::check(Ball *ball, Paddle *paddle) {
    // Ball properties.
    float ballX = ball->getPosition().x;
    float ballY = ball->getPosition().y;
    float ballRadius = ball->getRadius();

    // Paddle boundaries.
    float paddleTop = paddle->getPosition().y - (paddle->getSize().y / 2);
    float paddleBottom = paddle->getPosition().y + (paddle->getSize().y / 2);
    float paddleLeft = paddle->getPosition().x - (paddle->getSize().x / 2);
    float paddleRight = paddle->getPosition().x + (paddle->getSize().x / 2);

    // Top collisions.
    if (ballY <= paddleTop) {
        // Top left corner
        if (ballX <= paddleLeft) {
            if (getDistance(ballX, ballY, paddleLeft, paddleTop) <= ballRadius) {
                printf("TOP LEFT\n");
                return TOP_LEFT;
            }
        }
            // Top right corner
        else if (ballX >= paddleRight) {
            if (getDistance(ballX, ballY, paddleRight, paddleTop) <= ballRadius) {
                printf("TOP RIGHT\n");
                return TOP_RIGHT;
            }
        }
            // Top flat area
        else {
            if (paddleTop - ballY <= ballRadius) {
                printf("TOP\n");
                return TOP;
            }
        }
    }

    // Bottom collisions.
    if (ballY >= paddleBottom) {
        // Bottom left corner
        if (ballX <= paddleLeft) {
            if (getDistance(ballX, ballY, paddleLeft, paddleBottom) <= ballRadius) {
                printf("BOTTOM LEFT\n");
                return BOTTOM_LEFT;
            }
        }
            // Bottom right corner
        else if (ballX >= paddleRight) {
            if (getDistance(ballX, ballY, paddleRight, paddleBottom) <= ballRadius) {
                printf("BOTTOM RIGHT\n");
                return BOTTOM_RIGHT;
            }
        }
            // Bottom flat area.
        else {
            if (ballY - paddleBottom <= ballRadius) {
                printf("BOTTOM\n");
                return BOTTOM;
            }
        }
    }

    // Left side collisions.
    // center is left of the paddle.
    // center is not above the top of the paddle
    // center is not below the paddle
    // center is less than or equal to one radius away from the paddle.
    if ((ballX <= paddleLeft) && (ballY >= paddleTop) && (ballY <= paddleBottom) && (paddleLeft - ballX <= ballRadius)) {
        printf("LEFT\n");
        return LEFT;
    }

    // Right side collisions.
    if ((ballX >= paddleRight) && (ballY >= paddleTop) && (ballY <= paddleBottom) && (ballX - paddleRight <= ballRadius)) {
        printf("RIGHT\n");
        return RIGHT;
    }

    // If no collision was detected, return NONE.
    return NONE;
}

// Get the distance between two 2-dimensional points.
float CollisionUtils::getDistance(float x1, float y1, float x2, float y2) {
    return std::sqrt(std::pow(x2 - x1, 2.f) + std::pow(y2 - y1, 2.f));
}
