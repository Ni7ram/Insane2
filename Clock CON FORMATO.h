/********************************
  Name: Clock
  Copyright:
  Author: Jorge Marino
  Date: 09/07/08 18:15
  Description: Clock Class
********************************/

class Clock{
      	
public:
       
    //CONSTRUCTOR
    void Clock();
    
    //FUNCTIONS    
    void Init();
	float GetEllapsedSeconds();
    
    //VARIABLES
	
private:
    
    //CONSTRUCTOR
    
    //FUNCTIONS    
    
    //VARIABLES
	DWORD start;
}; 

/************************
      CONSTRUCTOR
************************/

void Clock::Clock(){
};

/************************
     PUBLIC METHODS
************************/

void Clock::Init()	{
    start = GetTickCount();
};

float Clock::GetEllapsedSeconds(){
    DWORD t = GetTickCount();
    float g = (float)(t-start);
    start = t;
    return g/1000.0f;
};

/************************
     PRIVATE METHODS
************************/
