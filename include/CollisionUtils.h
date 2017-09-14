//
// Created by cullen on 9/13/17.
//

#ifndef COLLISIONUTILS_H
#define COLLISIONUTILS_H

#include <Ball.h>

typedef enum Collision {
    LEFT,
    RIGHT,
    TOP,
    TOP_LEFT,
    TOP_RIGHT,
    BOTTOM,
    BOTTOM_LEFT,
    BOTTOM_RIGHT,
    NONE
} Collision;

class CollisionUtils {
public:
    // Check for collision between a ball and a paddle.
    static Collision check(Ball *ball, Paddle *paddle);
private:
    static float getDistance(float x1, float y1, float x2, float y2);
};


#endif //COLLISIONUTILS_H
