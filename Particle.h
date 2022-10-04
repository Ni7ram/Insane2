/********************************
  Name: Particle
  Copyright:
  Author: Martin Cardozo
  Date: 12/06/08 11:17
  Description: Particula Genérica
*********************************/

/************************
        INCLUDES
************************/

/************************
        CLASS
************************/

class Particle {   

public:
       
    //CONSTRUCTOR
    Particle(float XC, float YC, int minXC, int maxXC, int minYC, int maxYC, int lifeTimeC, float amplitudeC, float forceC, int redC, int greenC, int blueC);
    
    //FUNCTIONS      
    bool update();   
    
    //VARIABLES
    float X;
    float Y;
    
    int red;
    int green;
    int blue;

private:
    
    //FUNCTIONS
    bool  checkLife(); 
    float randFloat(float max);
    float GAR(float max);
    
    //VARIABLES
    int minX;
    int maxX;
    int minY;
    int maxY;
    int lifeTime;  
    float weight;
    float amplitude;
    float force;   
};

/************************
      CONSTRUCTOR
************************/

Particle::Particle(float XC, float YC, int minXC, int maxXC, int minYC, int maxYC, int lifeTimeC, float amplitudeC, float forceC, int redC, int greenC, int blueC)
{                       
    X          = XC;
    Y          = YC;
    minX       = minXC;
    maxX       = maxXC;
    minY       = minYC;
    maxY       = maxYC;
    amplitude  = randFloat(amplitudeC)/5000;
    force      = GAR(forceC + (randFloat(50)/5000));
    weight     = MathFunc.randFloat(1)/5000;
    force     += weight;
    lifeTime   = lifeTimeC;
    red        = redC;
    green      = greenC;
    blue       = blueC;
};

/************************
     PUBLIC METHODS
************************/

bool Particle::update(){
    if (!checkLife()){return false;}
    X += amplitude;
    Y += force;
};

bool Particle::checkLife(){
    if (!(lifeTime--)){return false;}
    return true;
};

/************************
     PRIVATE METHODS
************************/

float Particle::randFloat(float max){
    if (rand()%2){
        return -(MathFunc.randFloat(max));
    }else{
        return   MathFunc.randFloat(max);
    }
};

float Particle::GAR(float max){
    if (rand()%2){
        return (-max);
    }else{
        return max;
    }
};
