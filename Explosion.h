/********************************
  Name: Explosion
  Copyright:
  Author: Martin Cardozo
  Date: 09/07/08 13:41
  Description: Explosion Class
*********************************/

/************************
        INCLUDES
************************/

/************************
        CLASS
************************/

class Explosion {   

public:
       
    //CONSTRUCTOR
    Explosion(float XC, float YC, int quality, int redC, int greenC, int blueC, int lifeC);                            
    
    //FUNCTIONS
    void draw(BITMAP *dest);
    
    //VARIABLES
  
private:
  
    //FUNCTIONS
    bool update();
    bool checkLife();
    
    //VARIABLES
    ParticleSystem* Effect;
    
    int speed;
    
    int red;
    int green;
    int blue;
    
    float X;
    float Y;
    double incX;
    double incY;
    
    int life;
};

/************************
      CONSTRUCTOR
************************/

Explosion::Explosion(float XC, float YC, int quality, int redC, int greenC, int blueC, int lifeC);     
{                       
    X = XC;
    Y = YC;
    
    red   = redC;
    green = greenC;
    blue  = blueC;
   
    incX = incXC * speed;
    incY = incYC * speed;

    life    = lifeC;
    speed   = 20;  

    Effect = new ParticleSystem(maxPart, int(X), int(Y), 0, 0, 0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, life);
    Effect->changeColor(red,green,blue);
    
    //create shit
    double X = player.X;
    double Y = player.Y;
    switch(qualityC){
        case 1:
             for (int i = 0; i<36; i++) {
                 double INCY =  cos(i*10);
                 double INCX = -sin(i*10);
                 shockWave.push_back(new Bullet(X, Y, INCX, INCY, 0,  0,  0));
             }
             break;
        case 2:
             
             break;
        case 3:
             
             break;
    }
    
    Effect->start();
};

/************************
     PUBLIC METHODS
************************/

bool Explosion::draw(BITMAP *dest){
    if (!update())return false;
    X = X - camera.X;
    Y = Y - camera.Y;
    Effect->setNewLocation(X,Y);
    Effect->draw(dest);
    return true;
};

/************************
     PRIVATE METHODS
************************/

bool Explosion::update(){
    if (!checkLife())return false;
    
    X += incX;
    Y += incY;
    return true;
};

bool Explosion::checkLife(){
     if (--life)return true;
     return true;
};
