#include "rocket.h"
#include "main.h"

Rocket::Rocket(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 180;
    points = 2;
    speed = .09;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

static const GLfloat g_vertex_buffer_data[] = {
       .5,-.3,0.0f,
       -.5,-.3,0.0f,
       -.5,.3,0.0f,
       -.5,.3,0.0f,
       .5,.3,0.0f,
       .5,-.3,0.0f,

       .8,0,0,
       .5,-.3,0,
       .5,.3,0,

        -.5,-.3,0,
       -.8,-.3,0,
        -.5,.3,0,
      
       -.5,.3,0,
         -.5,-.3,0,
          -.8,.3,0,
        
    };
    this->centre = create3DObject(GL_TRIANGLES,6, g_vertex_buffer_data, COLOR_Met, GL_FILL);
    this->front = create3DObject(GL_TRIANGLES,3, g_vertex_buffer_data + 6*3, COLOR_RED, GL_FILL);
    this->back = create3DObject(GL_TRIANGLES,6, g_vertex_buffer_data + 9*3, COLOR_ORANGE, GL_FILL);
}

void Rocket::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
     draw3DObject(this->centre);
     draw3DObject(this->front);
     draw3DObject(this->back);
}

void Rocket::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Rocket::tick() {
    ///this->rotation += speed;
    this->position.x -= speed;
    // this->position.y -= speed;
}

