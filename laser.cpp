#include "laser.h"
#include "main.h"

Laser::Laser(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 90;
    speed = .03;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
static int n = 100;
GLfloat g_vertex_buffer_data[9*n+15];
  int i;
  float pi = 3.14;
  
  for(i=0;i<n;i++)
  {
  	g_vertex_buffer_data[9*i] = 0.5*cos(2*pi*i/n);
	g_vertex_buffer_data[9*i+1] = 0.5*sin(2*pi*i/n);
	g_vertex_buffer_data[9*i+2] = 0.0f ;
	g_vertex_buffer_data[9*i+3] = 0.5*cos(2*pi*(i+1)/n);
	g_vertex_buffer_data[9*i+4] = 0.5*sin(2*pi*(i+1)/n);
	g_vertex_buffer_data[9*i+5] = 0.0f;
	g_vertex_buffer_data[9*i+6] = 0.0f;
	g_vertex_buffer_data[9*i+7] = 0.0f;
	g_vertex_buffer_data[9*i+8] = 0.0f;

  }
static const GLfloat vertex_buffer_data[] = {
       .5f,-.3f,0.0f,
       -.5f,-.3f,0.0f,
       -.5f,0.0f,0.0f,
       -.5f,0.0f,0.0f,
        .5f,0.0f,0.0f,
       .5f,-.3f,0.0f,
    };
static const GLfloat buffer_data[] = {
       4,-.2f,0.0f,
       -4,-.2f,0.0f,
       -4,.2f,0.0f,
       -4,.2f,0.0f,
       4,.2f,0.0f,
       4,-.2f,0.0f,
    };
    this->sides = create3DObject(GL_TRIANGLES,1.5*n, g_vertex_buffer_data, COLOR_BLACK, GL_FILL);
    this->extensions = create3DObject(GL_TRIANGLES,6, vertex_buffer_data, COLOR_Grey, GL_FILL);
    this->laser = create3DObject(GL_TRIANGLES,6, buffer_data, COLOR_RED, GL_FILL);
}

void Laser::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
     draw3DObject(this->sides);
     draw3DObject(this->extensions);
   
}
void Laser::drawlaser(glm::mat4 VP) {
     Matrices.model = glm::mat4(1.0f);
     glm::mat4 translate = glm::translate (this->laser_position);
     Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->laser);
}

void Laser::set_position(float x, float y) {
     this->laser_position =  glm::vec3(x, y, 0);
}

void Laser::tick() {
    ///this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

