#include "coins.h"
#include "main.h"

Coin::Coin(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    points = 1;
    speed = .03;
    type = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
static int n = 100;
GLfloat g_vertex_buffer_data[9*n+15];
  int i;
  float pi = 3.14;
  
  for(i=0;i<n;i++)
  {
  	g_vertex_buffer_data[9*i] = 0.2*cos(2*pi*i/n);
	g_vertex_buffer_data[9*i+1] = 0.2*sin(2*pi*i/n);
	g_vertex_buffer_data[9*i+2] = 0.0f ;
	g_vertex_buffer_data[9*i+3] = 0.2*cos(2*pi*(i+1)/n);
	g_vertex_buffer_data[9*i+4] = 0.2*sin(2*pi*(i+1)/n);
	g_vertex_buffer_data[9*i+5] = 0.0f;
	g_vertex_buffer_data[9*i+6] = 0.0f;
	g_vertex_buffer_data[9*i+7] = 0.0f;
	g_vertex_buffer_data[9*i+8] = 0.0f;

  }
    GLfloat vertex_buffer_data[9*n+15];
    for(i=0;i<n;i++)
  {
  	vertex_buffer_data[9*i] = 0.3*cos(2*pi*i/n);
	vertex_buffer_data[9*i+1] = 0.3*sin(2*pi*i/n);
	vertex_buffer_data[9*i+2] = 0.0f ;
	vertex_buffer_data[9*i+3] = 0.3*cos(2*pi*(i+1)/n);
	vertex_buffer_data[9*i+4] = 0.3*sin(2*pi*(i+1)/n);
	vertex_buffer_data[9*i+5] = 0.0f;
	vertex_buffer_data[9*i+6] = 0.0f;
	vertex_buffer_data[9*i+7] = 0.0f;
	vertex_buffer_data[9*i+8] = 0.0f;

  }

    this->shape1 = create3DObject(GL_TRIANGLES,3*n, g_vertex_buffer_data, COLOR_GOLD, GL_FILL);
    this->shape2 = create3DObject(GL_TRIANGLES,3*n, vertex_buffer_data, COLOR_CHOC, GL_FILL);
}

void Coin::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(this->type == 1)
    {
     draw3DObject(this->shape1);
    }
    else
    {
        draw3DObject(this->shape2);
    }
   
}

void Coin::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Coin::tick() {
    ///this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

