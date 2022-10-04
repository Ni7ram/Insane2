/********************************
  Name: Timer
  Copyright:
  Author: Jorge Marino
  Date: 09/07/08 18:15
  Description: Timer Class
********************************/

/************************
        INCLUDES
************************/

extern "C" int _stdcall GetTickCount();

/************************
        CLASS
************************/

class Timer{
      	
public:
       
    //CONSTRUCTOR
    Timer();
    
    //FUNCTIONS    
    void  init();
	float GetEllapsedTime();
	void  reset();
    
    //VARIABLES
	
private:
    
    //FUNCTIONS    
    
    //VARIABLES
	double start;
}; 

/************************
      CONSTRUCTOR
************************/

Timer::Timer(){
};

/************************
     PUBLIC METHODS
************************/

void Timer::init()	{
    start = GetTickCount();
};

float Timer::GetEllapsedTime(){
    double t = GetTickCount();
    int  g   = (int)(t-start);
    return g;
};

void Timer::reset(){
   double t = GetTickCount();
   start = t;
};

/************************
     PRIVATE METHODS
************************/
