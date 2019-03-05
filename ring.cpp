#include "ring.h"
#include "main.h"

Ring::Ring(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    points = 2;
    speed = .03;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
static int n = 100;
GLfloat g_vertex_buffer_data[18*n+15];
  int i;
  float pi = 3.14;
  
  for(i=0;i<n;i++)
  {
  	g_vertex_buffer_data[9*i] = 1.5*cos(2*pi*i/n);
	g_vertex_buffer_data[9*i+1] = 1.5*sin(2*pi*i/n);
	g_vertex_buffer_data[9*i+2] = 0.0f ;
	g_vertex_buffer_data[9*i+3] = 1.5*cos(2*pi*(i+1)/n);
	g_vertex_buffer_data[9*i+4] = 1.5*sin(2*pi*(i+1)/n);
	g_vertex_buffer_data[9*i+5] = 0.0f;
	g_vertex_buffer_data[9*i+6] = 0.0f;
	g_vertex_buffer_data[9*i+7] = 0.0f;
	g_vertex_buffer_data[9*i+8] = 0.0f;

    g_vertex_buffer_data[9*i + 9*n] = 3*cos(2*pi*i/n);
	g_vertex_buffer_data[9*i+1 + 9*n] = 3*sin(2*pi*i/n);
	g_vertex_buffer_data[9*i+2 + 9*n] = 0.0f ;
	g_vertex_buffer_data[9*i+3 + 9*n] = 3*cos(2*pi*(i+1)/n);
	g_vertex_buffer_data[9*i+4 + 9*n] = 3*sin(2*pi*(i+1)/n);
	g_vertex_buffer_data[9*i+5 + 9*n] = 0.0f;
	g_vertex_buffer_data[9*i+6 + 9*n] = 0.0f;
	g_vertex_buffer_data[9*i+7 + 9*n] = 0.0f;
	g_vertex_buffer_data[9*i+8 + 9*n] = 0.0f;


  }

    this->inner = create3DObject(GL_TRIANGLES,1.5*n, g_vertex_buffer_data, COLOR_GREEN, GL_FILL);
    this->outer =  create3DObject(GL_TRIANGLES,1.5*n, g_vertex_buffer_data + 9*n, COLOR_BLUE, GL_FILL);
}

void Ring::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
     draw3DObject(this->outer);
     draw3DObject(this->inner);
   
}

void Ring::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ring::tick() {
    ///this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

