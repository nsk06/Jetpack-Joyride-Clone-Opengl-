#include "main.h"

#ifndef LASER_H
#define LASER_H


class Laser {
public:
    Laser() {}
    Laser(float x, float y);
    glm::vec3 position;
    glm::vec3 laser_position;
    float rotation;
    void draw(glm::mat4 VP);
    void drawlaser(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
   double speed;
private:
    VAO *laser;
    VAO *sides;
    VAO *extensions;
};

#endif // BALL_H
