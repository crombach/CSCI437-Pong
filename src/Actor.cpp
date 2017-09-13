//
// Created by cullen on 9/12/17.
//

#include <SFML/Graphics/RectangleShape.hpp>
#include "Actor.h"

Actor::Actor(float x, float y, sf::Shape *shape) {
    this->shape = shape;
    // Don't cause an exception if the pointer is null.
    if (this->shape != nullptr) {
        (this->shape)->setPosition(x, y);
    }
}

float Actor::getX() {
    return shape->getPosition().x;
}

float Actor::getY() {
    return shape->getPosition().y;
}

sf::Shape* Actor::getShape() {
    return shape;
}

void Actor::setShape(sf::Shape *shape) {
    this->shape = shape;
}

void Actor::move(float x, float y) {
    shape->move(x, y);
}
