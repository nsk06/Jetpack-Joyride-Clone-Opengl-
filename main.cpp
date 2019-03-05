#include "main.h"
#include "timer.h"
#include "player.h"
#include "beam.h"
#include "coins.h"
#include "laser.h"
#include "rocket.h"
#include "magnet.h"
#include "ring.h"
#include "platform.h"
#include "stage.h"
#include "boomerang.h"
#include "powerups.h"
#include "ballon.h"
#include "dragon.h"
#include "fireball.h"
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Player player;
Rocket rocket1,rocket2;
Magnet magnet;
Laser l1,l2,l3,l4,l5,l6;
std::vector <Beam> beam;
std::vector <Coin> coins;
Ring ring;
std::vector <Platform> back;
std::vector <Stage> stage;
std::vector <Stage> stageup;
std::vector <Ballon> ballons;
std::vector <Fireball> fireballs;
Boomerang boomerang;
Powerup power;
Dragon dragon;
bounding_box_t play;
bounding_box_t line ;
bounding_box_t coin;
bounding_box_t L1,L2;
bounding_box_t R1,R2;
bounding_box_t ringbox;
bounding_box_t boombox;
bounding_box_t powerbox;
bounding_box_t ballonbox;
bounding_box_t fireballbox;
bounding_box_t dragbox;

float screen_zoom = .6, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 90;
long long  int frame_count = 0;
    int count_beam = 0;
    int check_laser = -1;
    int check_rocket = 0;
    int check_magnet = -1;
    int check_ring = -1;
    int check_power = -1;
    int check_bullet = -1;
    int check_boom=-1;
    int check_dragon = -1;
    bool inring = false;
    float camspeedx = .04f;
    float camx = 0;
Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f) + camx, 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (camx, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane
    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    vector<Platform>:: iterator itr;
    for(auto itr = back.begin();itr!=back.end();itr++)
    {
        (*itr).draw(VP);
    }
    vector<Stage>:: iterator itrr;
    for(auto itrr = stage.begin();itrr!=stage.end();itrr++)
    {
        (*itrr).draw(VP);
    }
    vector<Stage>:: iterator itru;
    for(auto itru = stageup.begin();itru!=stageup.end();itru++)
    {
        (*itru).draw(VP);
    }
    if(check_ring > 0)
    {
        ring.draw(VP);
    }
    if(check_boom > 0)
    {
        boomerang.rotation += 4;
        boomerang.draw(VP);
    }
    if(check_power > 0)
    {
        power.draw(VP);
    }
    if(check_dragon > 0)
    {
        dragon.draw(VP);
    }
    player.draw(VP);
    if(check_rocket == 1)
    {
        rocket1.draw(VP);
        rocket2.draw(VP);
    }
    if(check_laser > 0)
            {
                l1.draw(VP);
                l2.draw(VP);
                l4.draw(VP);
                l5.draw(VP);
                if(check_laser > 90)
                {
                    l3.drawlaser(VP);
                    l6.drawlaser(VP);
                    L1.x = l3.laser_position.x;
                    L1.y = l3.laser_position.y;
                    L2.x = l6.laser_position.x;
                    L2.y = l6.laser_position.y;
                }
            }
    if(check_magnet > 0)
    {
        magnet.draw(VP);
    }
    vector<Beam>::iterator my_iterator;
    for(auto my_iterator = beam.begin();my_iterator!=beam.end();my_iterator++)
    {
        if(frame_count%20 == 0)
        {
            (*my_iterator).rotation = rand()%360;
        }
        (*my_iterator).draw(VP);
    }

     vector<Coin>::iterator my_iterator2;
     for(auto my_iterator2 = coins.begin();my_iterator2!=coins.end();my_iterator2++)
    {
        if(frame_count%10 == 0)
        {
            (*my_iterator2).rotation = rand()%360;
        }
        (*my_iterator2).draw(VP);
    }
       vector<Ballon>::iterator my_iterator3;
       if(ballons.size() > 0)
       {
            for(auto my_iterator3 = ballons.begin();my_iterator3!=ballons.end();my_iterator3++)
            {
                (*my_iterator3).draw(VP);
            }
       }
        vector<Fireball>::iterator my_iterator4;
       if(fireballs.size() > 0)
       {
            for(auto my_iterator4 = fireballs.begin();my_iterator4!=fireballs.end();my_iterator4++)
            {
                (*my_iterator4).draw(VP);
            }
       }
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window,GLFW_KEY_SPACE);
    int bul = glfwGetKey(window,GLFW_KEY_B);
    if(inring == false)
    {
        if (left) {
            if(player.position.x > camx - 4 / screen_zoom+2)
            {
                player.position.x -= player.speedx;
            }
        }
        else if(right)
        {
            if(player.position.x < camx + 4 / screen_zoom-2)
            {
                player.position.x += player.speedx;
            }
        }
        else if(up)
        {
             if(player.position.y > 5)
            {
                return;
            }
            player.position.y += player.speedy;
            player.keypress = true;
        }
    }
    if(bul && check_bullet < 0)
    {
        check_bullet = 0;
        ballons.push_back(Ballon(player.position.x+1,player.position.y));
    }
}

void tick_elements() {
    if(check_rocket == 1)
    {
        rocket1.tick();
        rocket2.tick();
    }
    if(check_boom >= 0)
    {
        boomerang.tick();
    }
    if(check_power >= 0)
    {
        power.tick();
    }
       vector<Ballon>::iterator my_iterator3;
    if(ballons.size()>0)
    {
        for(auto my_iterator3 = ballons.begin();my_iterator3!=ballons.end();my_iterator3++)
        {
            (*my_iterator3).tick();
            if((*my_iterator3).timer > 5)
            {
                ballons.erase(my_iterator3);
                if(ballons.size() == 0)
                {
                    break;
                }
            }
        }
    }
      vector<Fireball>::iterator my_iterator4;
      if(fireballs.size()>0)
      {
        for(auto my_iterator4 = fireballs.begin();my_iterator4!=fireballs.end();my_iterator4++)
        {
            (*my_iterator4).tick();
            if((*my_iterator4).position.y < -5)
            {
                fireballs.erase(my_iterator4);
                if(fireballs.size() == 0)
                {
                    break;
                }
            }
        }
      }
    if(inring == true)
    {
        player.position.x += player.speedx/3;
        player.position.y = ring.position.y+ sqrt(abs(9-pow(player.position.x-ring.position.x,2)));
        return;
    }
     if(check_magnet > 0)
    {
        if (magnet.position.x < player.position.x)
        {
            player.position.x -= .03*player.magtimer/60.0;
        }
        else if(magnet.position.x > player.position.x+1)
        {
            player.position.x += .03*player.magtimer/60.0;
        }
        if (magnet.position.y < player.position.y)
        {
            //player.position.y -= player.speedy/1.5;
            player.type = 2;
        }
        else{
            player.type=1;
            //player.position.y += player.speedy/1.5;
        }
        
    }
    player.tick();
    if(check_dragon > 0)
    {
        if(dragon.position.x-player.position.x < 3)
        {
            dragon.position.x += dragon.speed;
        }
        if(dragon.position.y < player.position.y+2)
        {
            dragon.position.y+=dragon.speed;
        }
        else{
            dragon.position.y-=dragon.speed;
        }
    dragon.tick();
    }   // camera_rotation_angle += 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    glClearColor (30/255.0,30/255.0,30/255.0,0.0); // R, G, B, A
    glClearDepth (.5f);
    back.push_back(Platform(0,0));
    for(int i=7;i<=50;i+=7)
    {
        back.push_back(Platform(i,0));
        back.push_back(Platform(-i,0));
    }
    for(int i=0;i<=50;i+=7)
    {
        stage.push_back(Stage(i,-6));
        stage.push_back(Stage(-i,-6));
        Stage a = Stage(i,6);
        Stage b = Stage(-i,6);
        a.rotation = 180;
        b.rotation = 180;
        stageup.push_back(a);
        stageup.push_back(b);
    }
    player       = Player(-4,-4, COLOR_RED);
       // Create the models
    //beam.push_back(Beam(0,0));
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
    for(int i =0;i<15;i++)
    {
        Coin c = Coin(rand()%6-3,rand()%6-3);
        c.points = rand()%5;
        coins.push_back(c);
    }

    reshapeWindow (window, width, height);

    // Background color of the scene
   
    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 1080;
    int height = 960;
    double tim;
   
    window = initGLFW(width, height);

    initGL (window, width, height);
    play.height = 1.5f;
    play.width = 1.0f;
    line.width = 1.5;
    line.height = 1.5;
    coin.height = .4;
    coin.width = 0.4;
    L1.height = .2;
    L2.height = .2;
    L1.width = 8;
    L2.width = 8;
    R1.height = .6;
    R1.width = 1.6;
    R2.height = .6;
    R2.width = 1.6;
    ringbox.height = 3;
    ringbox.width = 3;
    boombox.height = .8;
    boombox.width = 1.8;
    powerbox.height = 2;
    powerbox.width = 2;
    ballonbox.height = .5;
    ballonbox.width = .5;
    fireballbox.height = .3;
    fireballbox.width = .3;
    dragbox.height = 3;
    dragbox.width = 3.5;
    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
             system("clear");
            cout << "SCORE" << "::" << player.Score << endl;
            cout << "LIVES" << "::" << player.lives << endl;

            string score = " *** JetPack Joyride ****     SCORE::  " + to_string(player.Score) + "    Lives:: " + to_string(player.lives);
            if(player.powertime > 0)
            {
                score += "Power " + to_string(5-int(player.powertime/60));
            }
            const char *_score = score.c_str();
            glfwSetWindowTitle(window,_score);
            if(player.lives <=0)
            {
                quit(window);
            }
            frame_count++;
            if(player.position.x - camx > 4)
            {
                camx += camspeedx;
            }
            else if(player.position.x - camx < -4 )
            {
                camx -= camspeedx;                
            }
             if((int(abs(player.position.x))%35 == 0))
            {
                if(player.position.x > 7)
                {
                    for(int i=7;i<=50;i+=7)
                    {
                        back.push_back(Platform(player.position.x+i,0));
                        stage.push_back(Stage(player.position.x+i,-6));
                        Stage a = Stage(player.position.x+i,6);
                        a.rotation = 180;
                        stageup.push_back(a);
                    }
                }
                else if(player.position.x < -7)
                {
                    for(int i=7;i<=50;i+=7)
                    {
                        back.push_back(Platform(player.position.x-i,0));
                        stage.push_back(Stage(player.position.x-i,-6));
                        Stage a = Stage(player.position.x-i,6);
                        a.rotation = 180;
                        stageup.push_back(a);
                    }
                }
            }
            if(frame_count%3000 == 0)
            {
                dragon = Dragon(player.position.x+4,player.position.y);                   //DRAGON GENERATION
                check_dragon = 0;
            }
            if(check_dragon >= 0)
            {
                check_dragon++;
                if(check_dragon%30 == 0)
                {
                    fireballs.push_back(Fireball(dragon.position.x-2,dragon.position.y));
                }
                if(check_dragon > 360)
                {
                    check_dragon = -1;
                }
                
            }
            if(frame_count%1500 == 0)
            {
                power = Powerup(player.position.x-3,0);                                 //POWERUPS
                power.type = rand()%3+1;
                check_power = 0;
            }
            if(check_power >= 0)
            {   
                check_power++;
                powerbox.x = power.position.x;
                powerbox.y = power.position.y;
                if(detect_collision(play,powerbox)==true)
                {
               system("aplay powerup_collect.wav&");                    
                    if(power.type == 1)
                    {
                        player.Score += 100;
                    }
                    else if(power.type == 2)
                    {                                                                      //Collectin Powerups
                        player.lives += 1;
                    }
                    else if(power.type == 3)
                    {
                        player.powertime = 0;
                    }
                    check_power = -1;
                }
                if(check_power > 400)
                {
                    check_power = -1;
                }
            }
            if(check_bullet >=0)
            {
                check_bullet++;
                if(check_bullet > 60)                                                         //bullet gaps
                {
                    check_bullet = -1;
                }
            }
            if(frame_count%2100==0)
            {
                boomerang = Boomerang(player.position.x+5,-4.5);                            //boomerang
                boomerang.spawnpos = player.position.x-4;
                check_boom = 0;
            }
            if(check_boom >=0)
            {
                check_boom++;
                    boombox.x = boomerang.position.x;
                    boombox.y = boomerang.position.y;
                    if(detect_collision(play,boombox) && inring == false && player.powertime < 0)
                    {
                        player.lives -=1;  
                        check_boom = -1; 
                    }
                    if(check_boom > 900)
                    {
                        check_boom = -1;
                    }
            }
            if(frame_count % 1200 == 0)
            {
                check_laser=0;
                l1 = Laser(-4+camx,-4);
                l2 = Laser(4+camx,-4);
                l2.rotation = -90;
                l3 = Laser(camx,0);
                l3.set_position(camx,-4);                                                          //lasers 
                l4 = Laser(-4+camx,-1);
                l5 = Laser(4+camx,-1);
                l5.rotation = -90;
                l6 = Laser(camx,0);
                l6.set_position(camx,-1);
            }
            if(check_laser >=0)
            {
                check_laser++;
                 if((detect_collision(play,L1) == true|| detect_collision(play,L2)==true) && inring == false && check_laser > 110 && player.powertime < 0)
                {
                     player.lives -= 1;
                     check_laser = -1;
                }
                if(check_laser > 300)
                {
                    check_laser = -1;
                }
            }
            if(frame_count%900 == 0)
            {

                rocket1 = Rocket(player.position.x+8,rand()%3-4);                                    //Rockets
                rocket2 = Rocket(player.position.x+8,rand()%4);
               system("aplay missile_warning.wav&");
                check_rocket = 1;
            }
            if(check_rocket == 1)
            {
                R1.x = rocket1.position.x;
                R1.y = rocket1.position.y;
                R2.x = rocket2.position.x;
                R2.y = rocket2.position.y;
                if(detect_collision(play,R1) == true|| detect_collision(play,R2)==true && inring == false && player.powertime < 0)
                {
                    player.lives -=1;
                    check_rocket = 0;
                }
            }

            if(frame_count%1020 == 0)
            {
                magnet = Magnet(rand()%9-4+player.position.x,rand()%9-4);
                check_magnet = 0;                                                                         //Magnets
            }
            if(check_magnet >= 0)
            {
                check_magnet++;
                if(player.magtimer < 0)
                {
                 player.magtimer = 0;
                }
                if(check_magnet > 200)
                {
                    check_magnet = -1;
                    player.magtimer = -1;
                    player.type = 3;
                }

            }
            player.keypress = false;
            if(inring == false)
            {
                player.timer += 1.0/60.0;
            }
        if(frame_count%240 == 0)
            {
                count_beam++;
                Beam b = Beam(10+player.position.x,rand()%6-3);                                               //Beams
                b.rotation = rand()%145 + 45;
                beam.push_back(b);
            }
            if(frame_count%200 == 0)
            {
                for(int i =0;i<15;i++)
                    {
                        Coin c = Coin(rand()%20+camx,rand()%7-3);
                        c.type  = rand()%2+1;
                        if(c.type == 1)
                        {
                            c.points = 1;
                        }
                        else {
                            c.points = 3;
                        }
                        coins.push_back(c);
                    }
            }

            if(frame_count%1800 == 0)
            {
                    ring         = Ring(player.position.x+3,3);                                              //Rings
                    check_ring = 0;
            }
            if(check_ring >= 0 )
            {
                check_ring ++;
                if(abs(player.position.x-ring.position.x) <= 3 && player.position.y > ring.position.y)
                {
                    inring = true;
                }
                if(check_ring > 300)
                {
                    check_ring = -1;
                    inring = false;
                }
            }
            //cout << frame_count << endl;
             vector<Coin>::iterator it2;
            for(auto it2=coins.begin();it2!=coins.end();it2++)
                {
                   (*it2).position.x -= (*it2).speed;
                }

             for(auto it2=coins.begin();it2!=coins.end();it2++)                                         //Coin collection
            {
                
                coin.x = (*it2).position.x;
                coin.y = (*it2).position.y;
                if(detect_collision(play,coin))
                {   
                    player.Score += (*it2).points;
               system("aplay coin_pickup_1.wav&");
                   coins.erase(it2);
                   break;
                   
                } 
            }

            draw();
        
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);
            tick_input(window);
            tick_elements();
            play.x = player.position.x;
            play.y = player.position.y;                                                              //Updating player movements
            vector<Beam>::iterator it;
            for(auto it=beam.begin();it!=beam.end();it++)
            {
                (*it).position.x -= (*it).speed;
                line.x = (*it).position.x;
                line.y = (*it).position.y;
          
                if(detect_collision(play,line) && inring == false && player.powertime < 0)
                {   
                  // quit(window); 
                  player.lives -=1; 
                  beam.erase(it);
                  break;                                                              // beam collision
                }
                if(beam.size() == 0)
                {
                    break;
                }
                 vector<Ballon>::iterator my_iterator3;
                for(auto my_iterator3 = ballons.begin();my_iterator3!=ballons.end();my_iterator3++)
                {
                        ballonbox.x = (*my_iterator3).position.x;
                        ballonbox.y = (*my_iterator3).position.y;
                        if(detect_collision(ballonbox,line)==true)                                               //Water Ballon Collision-Beam
                        {
                            beam.erase(it);
                            break;
                        }
                }
                if(beam.size() == 0)
                    {
                        break;
                    }
                if((*it).position.x < player.position.x-15)
                    {
                        beam.erase(it);
                    }
               
            }
            vector<Ballon>::iterator my_iterator3;
            for(auto my_iterator3 = ballons.begin();my_iterator3!=ballons.end();my_iterator3++)
            {
                ballonbox.x = (*my_iterator3).position.x;
                ballonbox.y = (*my_iterator3).position.y;
                if(check_rocket == 1)
                {
                    if(detect_collision(ballonbox,R1)==true || detect_collision(ballonbox,R2)==true)            //Water Ballon Collision-Rocket
                    {
                            check_rocket = 0;
                    }
                }
                if(check_dragon > 0)
                {
                    dragbox.x = dragon.position.x;
                    dragbox.y = dragon.position.y;
                    if(detect_collision(ballonbox,dragbox)==true)
                    {
                        dragon.lives -= 1;
                        if(dragon.lives <=0)
                        {
                            check_dragon = -1;
                        }
                        ballons.erase(my_iterator3);
                        break;
                    }
                }
                if(ballons.size() == 0)
                {
                    break;
                }
            }
            vector<Fireball>::iterator my_iterator4;
                for(my_iterator4=fireballs.begin();my_iterator4!=fireballs.end();my_iterator4++)
                {
                        fireballbox.x = (*my_iterator4).position.x;
                        fireballbox.y = (*my_iterator4).position.y;
                        if(detect_collision(play,fireballbox)==true && inring == false && player.powertime < 0)
                        {
                            player.lives -= 1;
                            fireballs.erase(my_iterator4);
                            break;
                        }
                        if(fireballs.size() == 0)
                        {
                            break;
                        }
                }
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
        
    }
    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
