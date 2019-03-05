#include "boomerang.h"
#include "main.h"

Boomerang::Boomerang(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    shift = 0;
    speed = .03;
    pos = 1;
    spawnpos = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
static int n = 100;
static const GLfloat g_vertex_buffer_data[] = {
        0,-.1,0,
        -1,-1,0,
        -1.2,-.8,0,
        -1.2,-.8,0,
        0,.1,0,
        0,-.1,0,

       0,-.1,0,
        1,-1,0,
        1.2,-.8,0,
        1.2,-.8,0,
        0,.1,0,
        0,-.1,0, 

};

    this->shape = create3DObject(GL_TRIANGLES,12, g_vertex_buffer_data, COLOR_TAN, GL_FILL);
}

void Boomerang::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
     draw3DObject(this->shape);
}

void Boomerang::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Boomerang::tick() {
    // if(this->pos == 1)
    // {
    //     this->position.x -= this->speed;
    // }
    // else if (this->pos == 2)
    // {
    //     this->position.y -= this->speed/2;
    //     if(abs(this->position.y-this->shift) > 3)
    //     {
    //         this->pos = 3;
    //     }
    // }
    // else if(this->pos == 3)
    // {
    //     this->position.x += this->speed;
    // }
    this->position.y += this->speed;
    this->position.x = pow(this->position.y,2)/2.0 + this->spawnpos;
    ///this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

