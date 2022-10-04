/*******************************************
  Name: Helper
  Copyright:
  Author: Martin Cardozo
  Date: 29/07/08 22:58
  Description: Common methods used in games
*******************************************/

/************************
        INCLUDES
************************/

/************************
        CLASS
************************/

class Helper {

public:

    //CONSTRUCTOR
    Helper();

    //FUNCTIONS
    bool hitArea(int x1, int y1, int s1, int x2, int y2, int s2);

    //VARIABLES

private:

    //FUNCTIONS

    //VARIABLES
};

/************************
      CONSTRUCTOR
************************/

Helper::Helper(){
};

/************************
     PUBLIC METHODS
************************/

bool Helper::hitArea(int x1, int y1, int s1, int x2, int y2, int s2){
     if (x1>x2 && x1+s1<x2+s2 && y1>y2 && y1+s1<y2+s2){
         return true;
     }else{
         return false;
     }
};

/************************
     PRIVATE METHODS
************************/
