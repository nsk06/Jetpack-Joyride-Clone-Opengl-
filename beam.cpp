#include "beam.h"
#include "main.h"

Beam::Beam(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.05;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
       .8f,-.1f,0.0f,
       -.8f,-.1f,0.0f,
       -.8f,.1f,0.0f,
       -.8f,.1f,0.0f,
       .8f,.1f,0.0f,
       .8f,-.1f,0.0f
    };
static int n = 100;
GLfloat g_vertex_buffer_data[18*n+15];
  int i;
  float pi = 3.14;
  
  for(i=0;i<n;i++)
  {
  	g_vertex_buffer_data[9*i] = -1+0.2*cos(2*pi*i/n);
	g_vertex_buffer_data[9*i+1] = 0.2*sin(2*pi*i/n);
	g_vertex_buffer_data[9*i+2] = 0.0f ;
	g_vertex_buffer_data[9*i+3] = -1+0.2*cos(2*pi*(i+1)/n);
	g_vertex_buffer_data[9*i+4] = 0+0.2*sin(2*pi*(i+1)/n);
	g_vertex_buffer_data[9*i+5] = 0.0f;
	g_vertex_buffer_data[9*i+6] = -1.0f;
	g_vertex_buffer_data[9*i+7] = 0.0f;
	g_vertex_buffer_data[9*i+8] = 0.0f;


    g_vertex_buffer_data[9*i+900] = 1+0.2*cos(2*pi*i/n);
	g_vertex_buffer_data[9*i+1 + 900] = 0.2*sin(2*pi*i/n);
	g_vertex_buffer_data[9*i+2 + 900] = 0.0f ;
	g_vertex_buffer_data[9*i+3 + 900] = 1+0.2*cos(2*pi*(i+1)/n);
	g_vertex_buffer_data[9*i+4+ 900] =0.2*sin(2*pi*(i+1)/n);
	g_vertex_buffer_data[9*i+5+ 900] = 0.0f;
	g_vertex_buffer_data[9*i+6+ 900] = 1.0f;
	g_vertex_buffer_data[9*i+7+ 900] = 0.0f;
	g_vertex_buffer_data[9*i+8+ 900] = 0.0f;

  }

    this->object = create3DObject(GL_TRIANGLES,6*n, g_vertex_buffer_data, COLOR_BLACK, GL_FILL);
    this->fire = create3DObject(GL_TRIANGLES,6, vertex_buffer_data, COLOR_RED, GL_FILL);
}

void Beam::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
     draw3DObject(this->fire);
    draw3DObject(this->object);
   
}

void Beam::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Beam::tick() {
    ///this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

