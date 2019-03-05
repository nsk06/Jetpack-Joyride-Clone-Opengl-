#include "main.h"

#ifndef BEAM_H
#define BEAM_H


class Beam {
public:
    Beam() {}
    Beam(float x, float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
    VAO *fire;
};

#endif // BALL_H
