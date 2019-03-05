#include "powerups.h"
#include "main.h"

Powerup::Powerup(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = .022;
    type = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
static int n = 100;
static const GLfloat g_vertex_buffer_data[] = {
        1,-1,0,
        -1,-1,0,
        -1,1,0,    //outer box
        -1,1,0,
        1,1,0,
        1,-1,0,

        .4,0,0,
        0,-.8,0,   //heart bottom
        -.4,0,0,

        .1,0,0,
        -.1,0,0,
        -.1,.5,0,    //Sword up
        -.1,.5,0,
        .1,.5,0,
        .1,0,0,

        .3,0,0,
        -.3,0,0,
        -.3,.1,0,
        -.3,.1,0,    //Sword side
        .3,.1,0,
        .3,0,0,


        .15,-.8,0,
        -.15,-.8,0,
        -.15,0,0,
        -.15,0,0,     //Main sword
        .15,0,0,
        .15,-.8,0,

        .15,-.8,0,
        0,-1,0,         //tip sword
        -.15,-.8,0,


};
  GLfloat vertex_buffer_data[9*n+15];
  GLfloat buffer_data[18*n+15];
  float pi = 3.14;
    for(int i=0;i<n;i++)
  {
  	vertex_buffer_data[9*i] = 0.5*cos(2*pi*i/n);
	vertex_buffer_data[9*i+1] = 0.5*sin(2*pi*i/n);
	vertex_buffer_data[9*i+2] = 0.0f ;
	vertex_buffer_data[9*i+3] = 0.5*cos(2*pi*(i+1)/n);
	vertex_buffer_data[9*i+4] = 0.5*sin(2*pi*(i+1)/n);
	vertex_buffer_data[9*i+5] = 0.0f;
	vertex_buffer_data[9*i+6] = 0.0f;
	vertex_buffer_data[9*i+7] = 0.0f;
	vertex_buffer_data[9*i+8] = 0.0f;

  }
   for(int i=0;i<n;i++)
  {
  	buffer_data[9*i] = -.2+.2*cos(2*pi*i/n);
	buffer_data[9*i+1] = .2*sin(2*pi*i/n);
	buffer_data[9*i+2] = 0.0f ;
	buffer_data[9*i+3] = -.2 +.2*cos(2*pi*(i+1)/n);
	buffer_data[9*i+4] = .2*sin(2*pi*(i+1)/n);
	buffer_data[9*i+5] = 0.0f;
	buffer_data[9*i+6] = -.2f;
	buffer_data[9*i+7] = 0.0f;
	buffer_data[9*i+8] = 0.0f;

    buffer_data[9*i + 9*n] = .2+.2*cos(2*pi*i/n);
	buffer_data[9*i+1 + 9*n] = .2*sin(2*pi*i/n);
	buffer_data[9*i+2 + 9*n] = 0.0f ;
	buffer_data[9*i+3 + 9*n] = .2 + .2*cos(2*pi*(i+1)/n);
	buffer_data[9*i+4 + 9*n] = .2*sin(2*pi*(i+1)/n);
	buffer_data[9*i+5 + 9*n] = 0.0f;
	buffer_data[9*i+6 + 9*n] = 0.2f;
	buffer_data[9*i+7 + 9*n] = 0.0f;
	buffer_data[9*i+8 + 9*n] = 0.0f;


  }

    this->shape = create3DObject(GL_TRIANGLES,6, g_vertex_buffer_data, COLOR_Cyan, GL_FILL);
    this->coin = create3DObject(GL_TRIANGLES,3*n,vertex_buffer_data, COLOR_GOLD, GL_FILL);
    this->heartA = create3DObject(GL_TRIANGLES,1.5*n, buffer_data, COLOR_RED, GL_FILL);
    this->heartB = create3DObject(GL_TRIANGLES,1.5*n, buffer_data + 9*n, COLOR_RED, GL_FILL);
    this->heartC = create3DObject(GL_TRIANGLES,3,  g_vertex_buffer_data+6*3, COLOR_RED, GL_FILL);
    this->swordA = create3DObject(GL_TRIANGLES,12,  g_vertex_buffer_data+9*3, COLOR_PURE, GL_FILL);
    this->swordB = create3DObject(GL_TRIANGLES,9,  g_vertex_buffer_data+21*3, COLOR_Grey, GL_FILL);

}

void Powerup::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
     draw3DObject(this->shape);
     if(this->type == 1)
     {
        draw3DObject(this->coin);
     }
     else if(this->type == 2)
     {
        draw3DObject(this->heartA);
        draw3DObject(this->heartB);
        draw3DObject(this->heartC);
     }
     else if(this->type == 3)
     {
        draw3DObject(this->swordA);
        draw3DObject(this->swordB);
     }
}

void Powerup::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Powerup::tick() {
    this->position.x += this->speed;
    this->position.y = 2*sin(this->position.x);
    ///this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

