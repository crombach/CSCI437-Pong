//
// Created by cullen on 9/12/17.
//

#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics/Color.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Paddle : public sf::RectangleShape {
    float speed;
public:
    // Constructors
    Paddle(float x, float y);
    Paddle(float x, float y, sf::RectangleShape shape);
    // Movement methods.
    void moveUp(float distance);
    void moveDown(float distance);
    void moveAsAI(sf::Vector2f ballPosition, float deltaTime);
    void reset(bool left);
    // Getters and setters.
    float getSpeed();
    void setSpeed(float speed);
};


#endif //PADDLE_H
