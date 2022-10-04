/********************************
  Name: Viewport
  Copyright:
  Author: Martin Cardozo
  Date: 07/07/08 22:38
  Description: Camera Class
*********************************/

/************************
        INCLUDES
************************/

/************************
        CLASS
************************/

class Viewport {   

public:
       
    //CONSTRUCTOR
    Viewport(int XC, int YC, int WIDHT, int HEIGHT);
    
    //FUNCTIONS 
    bool translate(double iX, double iY, int fX, int fY);
    void shake(int strength);
    void zoom(float factor);
    
    //VARIABLES
    int X;
    int Y;
    int WIDTH;
    int HEIGHT;
  
private:
  
    //FUNCTIONS

    //VARIABLES
};

/************************
      CONSTRUCTOR
************************/

Viewport::Viewport(int XC, int YC, int WIDTHC, int HEIGHTC)
{
    X      = XC;
    Y      = YC;
    WIDTH  = WIDTHC;
    HEIGHT = HEIGHTC;
};

/************************
     PUBLIC METHODS
************************/

bool Viewport::translate(double iX, double iY, int fX, int fY){
     //CONVERT COORDINATES     
};

void Viewport::shake(int strength){
     //SHAKE CAMERA
     if (strength>2){ //SI ES MENOR NO PUEDE HACER EN RAND Y SE ROMPE TODO
         X += rand()%(strength/2);
         Y += rand()%(strength/2);
     }
};

void Viewport::zoom(float factor){
     //ZOOM
};

/************************
     PRIVATE METHODS
************************/
