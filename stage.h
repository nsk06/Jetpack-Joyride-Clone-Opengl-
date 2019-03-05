#include "main.h"

#ifndef STAGE_H
#define STAGE_H


class Stage {
public:
    Stage() {}
    Stage(float x, float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
   int points;
   double speed;
private:
    VAO *squareB;
    VAO *squareW;
    VAO *head;
};

#endif // BALL_H
