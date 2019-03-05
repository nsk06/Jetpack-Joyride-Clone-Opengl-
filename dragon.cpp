#include "dragon.h"
#include "main.h"

Dragon::Dragon(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = .05;
    timer = -1;
    lives = 3;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
static int n = 100;
GLfloat g_vertex_buffer_data[9*n+15];
  int i;
  float pi = 3.14;
  
  for(i=0;i<n;i++)
  {
  	g_vertex_buffer_data[9*i] = -1+0.1*cos(2*pi*i/n);
	g_vertex_buffer_data[9*i+1] = .45+0.1*sin(2*pi*i/n);
	g_vertex_buffer_data[9*i+2] = 0.0f ;
	g_vertex_buffer_data[9*i+3] = -1+0.1*cos(2*pi*(i+1)/n);
	g_vertex_buffer_data[9*i+4] = .45+0.1*sin(2*pi*(i+1)/n);
	g_vertex_buffer_data[9*i+5] = 0.0f;
	g_vertex_buffer_data[9*i+6] = -1.0f;
	g_vertex_buffer_data[9*i+7] = 0.45f;
	g_vertex_buffer_data[9*i+8] = 0.0f;

  }
static const GLfloat vertex_buffer_data[] = {
    0,.8,0,
    -1.5,.1,0,
    .4,2,0,
    0,-.8,0,
    -1.5,-.1,0,
    .4,-2,0,

    -1,.35,0,
    -.9,0.1,0,
    -.6,.55,0,
    -.6,.55,0,
    -.45,.1,0,
    -.3,.7,0,

    -1,-.35,0,
    -.9,-0.1,0,
    -.6,-.55,0,
    -.6,-.55,0,
    -.45,-.1,0,
    -.3,-.7,0,

    0,-.85,0,
    1,0,0,
    0,.85,0,

    0,-.85,0,
    1.7,0,0,
    0,.85,0,

    0,-.85,0,
    2.4,0,0,
    0,.85,0,

    0,.8,0,
    2.4,0,0,
    .4,2,0,
    0,-.8,0,
    2.4,0,0,
    .4,-2,0,
};
    this->eye = create3DObject(GL_TRIANGLES,3*n, g_vertex_buffer_data, COLOR_PURE, GL_FILL);
    this->face = create3DObject(GL_TRIANGLES,6, vertex_buffer_data, COLOR_DGREEN, GL_FILL);
    this->teeth = create3DObject(GL_TRIANGLES,12, vertex_buffer_data + 6*3, COLOR_OLIVE, GL_FILL);
    this->back3 = create3DObject(GL_TRIANGLES,3, vertex_buffer_data + 24*3, COLOR_DGREEN, GL_FILL);
    this->back2 = create3DObject(GL_TRIANGLES,3, vertex_buffer_data + 21*3, COLOR_FGREEN, GL_FILL);
    this->back1 = create3DObject(GL_TRIANGLES,3, vertex_buffer_data + 18*3, COLOR_YGREEN, GL_FILL);
    this->sides = create3DObject(GL_TRIANGLES,6, vertex_buffer_data + 27*3, COLOR_SGREEN, GL_FILL);
}

void Dragon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
     draw3DObject(this->face);
     draw3DObject(this->eye);  
     draw3DObject(this->teeth);  
     draw3DObject(this->back3);    
     draw3DObject(this->back2);    
     draw3DObject(this->back1);
     draw3DObject(this->sides);    
}

void Dragon::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Dragon::tick() {
    ///this->rotation += speed;
    if(this->timer >= 0)
    {
        this->timer += 1.0/60.0;
        if(this->timer > 6)
        {
            this->timer = -1;
        }
    }
}

