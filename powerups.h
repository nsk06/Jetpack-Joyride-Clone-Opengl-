#include "main.h"

#ifndef POWERUP_H
#define POWERUP_H


class Powerup {
public:
    Powerup() {}
    Powerup(float x, float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
   int type;
   double speed;
private:
    VAO *shape;
    VAO *coin;
    VAO *heartA;
    VAO *heartB;
    VAO *heartC;
    VAO *swordA;
    VAO *swordB;
};

#endif // BALL_H
