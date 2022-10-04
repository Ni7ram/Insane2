/********************************
  Name: Math Helper
  Copyright: 
  Author: Martin Cardozo 
  Date: 12/06/08 11:17
  Description: Funciones Matemáticas Auxiliares
*********************************/

/************************
        CLASS
************************/

class MathHelper {   

public:
           
    //CONSTRUCTOR
    MathHelper();
    
    //FUNCTIONS      
    float randFloat(float max);
    int randInt(int max);
    float floatDelta();    
    int intDelta(int Value1, int Value2);
    
    //VARIABLES

private:
    
    //FUNCTIONS
    
    //VARIABLES
};

/************************
      CONSTRUCTOR
************************/

MathHelper::MathHelper(){                    
};

/************************
     PUBLIC METHODS
************************/

float MathHelper::randFloat(float max){
    return rand()/(float(max)+1);
};

int MathHelper::randInt(int max){
};

float MathHelper::floatDelta(){
}; 

int MathHelper::intDelta(int Value1, int Value2){
    return Value2 - Value1;
};   

/************************
     PRIVATE METHODS
************************/
