//
// Created by cullen on 9/12/17.
//

#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics/Color.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

typedef enum AIDirection {
    UP,
    DOWN,
    STATIC
} Direction;

class Paddle : public sf::RectangleShape {
private:
    float speed;
    Direction direction;
public:
    // Constructors
    Paddle(float x, float y);
    Paddle(float x, float y, sf::RectangleShape shape);
    // Movement methods.
    void moveUp(float distance);
    void moveDown(float distance);
    void noMove();
    void moveAsAI(float deltaTime, float ballDx, float ballDy, sf::Vector2f ballPosition, bool recalculate);
    void reset(bool left);
    // Getters and setters.
    float getSpeed();
    Direction getDirection();
};


#endif //PADDLE_H
