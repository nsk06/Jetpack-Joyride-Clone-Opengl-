#include "main.h"

#ifndef BALL_H
#define BALL_H


class Player {
public:
    Player() {}
    Player(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speedx,speedy;
    int Score;
    bool keypress;
    double timer;
    double magtimer;
    int type;
    int powertype;
    int powertime;
    int lives;
private:
    VAO *object;
    VAO *head;
    VAO *legs;
    VAO *shoes;
    VAO *jetpack;

    VAO *swordA;
    VAO *swordB;
};

#endif // BALL_H
