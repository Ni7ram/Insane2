/********************************
  Name: Player
  Copyright:
  Author: Martin Cardozo
  Date: 12/06/08 11:17
  Description: Player Class
********************************/

/************************
        INCLUDES
************************/

#include "ParticleSystem.h"

/************************
        CLASS
************************/

class Player {   

public:
       
    //CONSTRUCTOR
    Player();
    
    //FUNCTIONS 
    void draw(BITMAP *dest);
    
    //VARIABLES
    double X;
    double Y;
    int size;
  
private:
  
    //FUNCTIONS
    void init();
    void update();
    void checkInput();
    void inertia();
    
    void goUp();
    void goDown();
    void goRight();
    void goLeft();
    
    //VARIABLES  
    ParticleSystem* Effect;
    
    int minX;
    int maxX;
    int minY;
    int maxY;
    
    int   maxSpeed;  
    float speedX;
    float speedY;
    float aceleration;
    float inercia;
};

/************************
      CONSTRUCTOR
************************/

Player::Player(){
    aceleration = .3f;
    inercia     = .1f;
    maxSpeed    = 5;
    minX = 0; 
    minY = 0;
    maxX = SCREEN_WIDTH;
    maxY = SCREEN_HEIGHT;
    X    = SCREEN_WIDTH/2;
    Y    = SCREEN_HEIGHT/2;
    size = 15;
    Effect = new ParticleSystem(500, int(X), int(Y), 0, 0, 0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 15);
    init();
};

/************************
     PUBLIC METHODS
************************/

void Player::draw(BITMAP *dest){
     update();
     X = X - camera.X;
     Y = Y - camera.Y;
     Effect->setNewLocation(X,Y);
     Effect->draw(dest);
     set_add_blender(0, 0, 0, 255);
     if (!blinked){
        circlefill(dest, int(X), int(Y), size, makecol(0, 0, 0));
        circle(dest, int(X), int(Y), size, makecol(150, 150, 255));
     }else{
        circlefill(dest, int(X), int(Y), size, makecol(150, 150, 255));
        circle(dest, int(X), int(Y), size, makecol(255, 255, 255));
     }
};

/************************
     PRIVATE METHODS
************************/
void Player::init(){
    Effect->changeColor(128,128,255);
    Effect->start();
};

void Player::checkInput(){
          //-MOVEMENT-//
    if (key[KEY_W]) {goUp();   }
    if (key[KEY_S]) {goDown(); }
    if (key[KEY_D]) {goRight();}
    if (key[KEY_A]) {goLeft(); }
    
          //-ACTIONS-//
};

void Player::update(){
    if (PLAYING)checkInput();
    X += speedX;
    Y += speedY;
    inertia();
};

void Player::inertia(){
     if (speedX){
         if (speedX > 0){
             speedX -= inercia;
         }else{
             if (speedX){
                 speedX +=inercia;
             }
         }          
     } 
    
     if (speedY){
         if (speedY > 0){
             speedY -= inercia;
         }else{
             if (speedY){
                 speedY += inercia;
             }
         }
     }
};

void Player::goUp(){
     if (speedY>-maxSpeed) speedY -= aceleration;
};

void Player::goDown(){
     if (speedY<maxSpeed)  speedY += aceleration;
};

void Player::goRight(){
     if (speedX<maxSpeed)  speedX += aceleration;
};

void Player::goLeft(){
     if (speedX>-maxSpeed) speedX -= aceleration;
};
