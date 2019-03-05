#include "main.h"

#ifndef DRAGON_H
#define DRAGON_H


class Dragon {
public:
    Dragon() {}
    Dragon(float x, float y);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
   double speed;
   double timer;
   int lives;
private:
    VAO *eye;
    VAO *face;
    VAO *teeth;
    VAO *back1;
    VAO *back2;
    VAO *back3;
    VAO *sides;
};

#endif // BALL_H
