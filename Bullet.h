/********************************
  Name: Bullet
  Copyright:
  Author: Martin Cardozo
  Date: 05/07/08 03:15
  Description: Bullet Class
*********************************/

/************************
        INCLUDES
************************/

/************************
        CLASS
************************/

class Bullet {   

public:
       
  //CONSTRUCTOR
  Bullet(float XC, float YC, double incXC, double incYC, int redC, int greenC, int blueC);
  
  //FUNCTIONS      
  bool draw(BITMAP *dest);
  void kill();
 
  //VARIABLES
  float X;
  float Y;
  int   size;
  
private:
  
  //FUNCTIONS
  bool update();
  bool checkBounds();

  //VARIABLES
  ParticleSystem* Effect;
  
  int red;
  int green;
  int blue;
  
  int speed;
  
  double incX;
  double incY;
    
  int minX;
  int maxX;
  int minY;
  int maxY;
};

/************************
      CONSTRUCTOR
************************/

Bullet::Bullet(float XC, float YC, double incXC, double incYC, int redC, int greenC, int blueC)
{                       
   X = XC;
   Y = YC;
   size = 3; 
   
   red   = redC;
   green = greenC;
   blue  = blueC;
   
   speed = 10;   
   incX = incXC * speed;
   incY = incYC * speed;
   
   minX = -100;
   minY = -100;
   maxX = SCREEN_WIDTH  + 100;
   maxY = SCREEN_HEIGHT + 100;
   
   Effect = new ParticleSystem(50, int(X), int(Y), 0, 0, 0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 10);
   Effect->changeColor(red,green,blue);
   Effect->start();
};

/************************
     PUBLIC METHODS
************************/

bool Bullet::draw(BITMAP *dest){
     if (!update())return false;
     X = X - camera.X;
     Y = Y - camera.Y;
     Effect->setNewLocation(X,Y);
     Effect->draw(dest);
     circle(dest, int(X), int(Y), size, makecol(red, green, blue));
     return true;
};

void Bullet::kill(){
    Effect->kill();
    delete Effect;
};

/************************
     PRIVATE METHODS
************************/

bool Bullet::update(){
    if (!checkBounds())return false;
    
    X += incX;
    Y += incY;
    return true;
};

bool Bullet::checkBounds(){
    if (Y < minY)return false;
              
    if (Y > maxY)return false;
                   
    if (X < minX)return false;
              
    if (X > maxX)return false;
    return true;
};
