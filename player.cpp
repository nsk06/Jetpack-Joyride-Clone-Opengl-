#include "player.h"
#include "main.h"

Player::Player(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speedx = .05;
    speedy = .07;
    Score = 0;
    keypress = false;
    timer = 0.0f;
    type = 0;
    powertype = 1;
    powertime = -1;
    lives = 1;
    magtimer = -1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat g_vertex_buffer_data[] = {
        0.5f,0.0f,0.0f,
        -0.2f,0.0f,0.0f,
        -0.2f,.5f,0.0f,       //Face
        -0.2f,.5f,0.0f,
        0.5f,.5f,0.0f,
        0.5f,0.0f,0.0f,

        
        .5f,.0f,0.0f,
        .5f,-.5f,0.0f,
        -.2f,-.5f,0.0f,      //Legs
        -.2f,-.5f,0.0f,
        -.2f,.0f,0.0f,
        .5f,.0f,0.0f,

        .5f,-.5f,0.0f,
        .5f,-.7f,0.0f,
        -.2f,-.7f,0.0f,
        -.2f,-.7f,0.0f,      //shoes
        -.2f,-.5f,0.0f,
        .5f,-.5f,0.0f,
        .6f,-.7f,0.0f,
        .5f,-.7f,0.0f,     
        .5f,-.5f,0.0f,
        
        -.2f,-0.0f,0.0f,
        -.2f,-.6f,0.0f,     //Jetpack
        -.5f,-0.0f,0.0f,

        -.3f,0.0f,0.0f,
        -.5f,-.6f,0.0f,
        -.5f,0.0f,0.0f,  
    };
    static const GLfloat vertex_buffer_data[] ={
        .5f,.5f,0.0f,
        -.2f,.5f,0.0f,
        -.2f,.3f,0.0f,      //Hair
        -.2f,.3f,0.0f,
        .5f,.3f,0.0f,
        .5f,.5f,0.0f,

        -.2f,.5f,0.0f,
        -.2f,.0f,0.0f,
        -.3f,.0f,0.0f,      //Back
        -.3f,.0f,0.0f,
        -.3f,.5f,0.0f,
        -.2f,.5f,0.0f,

        .5f,.15f,0.0f,
        .3f,.25f,0.0f, 
        .3f,.15f,0.0f,    //googles
        .3f,.25f,0.0f,
        .5f,.25f,0.0f,
        .5f,.15f,0.0f,


        1.1,0,0,
        .9,0,0,
        .9,.5,0,    //Sword up
        .9,.5,0,
        1.1,.5,0,
        1.1,0,0,

        1.3,0,0,
        .7,0,0,
        .7,.1,0,
        .7,.1,0,    //Sword side
        1.3,.1,0,
        1.3,0,0,


        1.15,-.8,0,
        .85,-.8,0,
        .85,0,0,
        .85,0,0,     //Main sword
        1.15,0,0,
        1.15,-.8,0,

        1.15,-.8,0,
        1,-1,0,         //tip sword
        .85,-.8,0,

         
    };
    this->object = create3DObject(GL_TRIANGLES,6, g_vertex_buffer_data, COLOR_Peach, GL_FILL);
    this->legs = create3DObject(GL_TRIANGLES,6, g_vertex_buffer_data+6*3, COLOR_RED, GL_FILL);
    this->shoes = create3DObject(GL_TRIANGLES,9, g_vertex_buffer_data+6*6, COLOR_BLUE, GL_FILL);
    this->jetpack = create3DObject(GL_TRIANGLES,6, g_vertex_buffer_data+21*3, COLOR_ORANGE, GL_FILL);
    this->head = create3DObject(GL_TRIANGLES,18,vertex_buffer_data,COLOR_BLACK,GL_FILL);

    this->swordA = create3DObject(GL_TRIANGLES,12,  vertex_buffer_data+18*3, COLOR_PURE, GL_FILL);
    this->swordB = create3DObject(GL_TRIANGLES,9,  vertex_buffer_data+30*3, COLOR_Met, GL_FILL);
}

void Player::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->jetpack);
    draw3DObject(this->shoes); 
    draw3DObject(this->legs);
    draw3DObject(this->head);

    if(this->powertime > 0)
    {
        draw3DObject(this->swordA);
        draw3DObject(this->swordB);
    }
}

void Player::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Player::tick() {
    ///this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;

    if(this->powertime >= 0)
    {
        this->powertime++;
        if(this->powertime > 300)
        {
            this->powertime = -1;
        }
    }
    if(this->magtimer >= 0)
    {
        this->magtimer++;
    }
    if(this->position.y < - 5 )
    {
        this->position.y = - 5;
    }
    if(this->keypress == true)
    {
        this->timer = 0;
    }
    else
    {
        if(this->position.y > -5)
        {
            if(this->type == 1)
            {
                this->position.y -= .03*this->timer;
            }
            else if(this->type == 2)
            {
                this->position.y -= .14*this->timer;
            }
            else
            {
                this->position.y -= .09*this->timer;
            }
        }
    }
}

