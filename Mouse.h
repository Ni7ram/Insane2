/********************************
  Name: Mouse
  Copyright:
  Author: Martin Cardozo
  Date: 05/07/08 02:12
  Description: Mouse Class
********************************/

/************************
        INCLUDES
************************/

/************************
        CLASS
************************/

class Mouse {   

public:
       
  //CONSTRUCTOR
  Mouse();
  
  //FUNCTIONS 
  void draw(BITMAP *dest);
 
  //VARIABLES
  
private:
  
  //FUNCTIONS
  int color;

  //VARIABLES  
};

/************************
      CONSTRUCTOR
************************/

Mouse::Mouse(){
    color = 170;
};

/************************
     PUBLIC METHODS
************************/

void Mouse::draw(BITMAP *dest){
     set_add_blender(0, 0, 0, 100);
     drawing_mode(DRAW_MODE_TRANS, 0, 0, 0);
     line(dest, 1, mouse_y, SCREEN_WIDTH,  mouse_y, makecol(color, 255, color));
     line(dest, mouse_x, 1, mouse_x, SCREEN_HEIGHT, makecol(color, 255, color));
     rectfill(dest, mouse_x-10, mouse_y-10, mouse_x+10, mouse_y+10, makecol(50, 50, 50));
     rect(dest, mouse_x-10, mouse_y-10, mouse_x+10, mouse_y+10, makecol(color, color, color));
     drawing_mode(DRAW_MODE_SOLID, 0, 0, 0);
     rectfill(dest, mouse_x-1, mouse_y-1, mouse_x+1, mouse_y+1, makecol(color, color, color));
     rect(dest, mouse_x-4, mouse_y-4, mouse_x+4, mouse_y+4, makecol(color, color, color));
};

/************************
     PRIVATE METHODS
************************/
