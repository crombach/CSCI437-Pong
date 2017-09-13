//
// Created by cullen on 9/12/17.
//

#ifndef ACTOR_H
#define ACTOR_H

#include <SFML/Graphics/Shape.hpp>

class Actor {
    sf::Shape* shape = nullptr;

protected:
    Actor(float x, float y, sf::Shape *shape);

public:
    float getX();
    float getY();
    void move(float x, float y);
    sf::Shape* getShape();
    void setShape(sf::Shape *shape);
};


#endif //ACTOR_H
