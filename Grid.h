/********************************
  Name: Grid
  Copyright:
  Author: Martin Cardozo
  Date: 09/07/08 15:32
  Description: Grid Class
********************************/

/************************
        INCLUDES
************************/

/************************
        CLASS
************************/

class Grid {   

public:

    //CONSTRUCTOR
    Grid(int XC, int YC, int sizeC);

    //FUNCTIONS 
    void draw(BITMAP *dest);   
    void fade(int value); 

    //VARIABLES
    int size;
    
private:

    //FUNCTIONS

    //VARIABLES
    int X;
    int Y;  
    
    int separation; //CAMBIAR NOMBRE
    
    bool fading;
    int  fadeValue;
    int  strenght;
};

/************************
      CONSTRUCTOR
************************/

Grid::Grid(int XC, int YC, int sizeC){
    X = XC;
    Y = YC;
    separation = 100;
    size       = sizeC/separation;
};

/************************
     PUBLIC METHODS
************************/

void Grid::draw(BITMAP *dest){
    X = X - camera.X;
    Y = Y - camera.Y;
    if (fading){
        if (fadeValue > 0){
            fadeValue -= 5;
            //if (EFFECTS)fadeValue -= 5;             //ESTO POR AHORA ANDA MAL (se desconfigura todo si desactivas los efectos en la mitad de
            //if (!EFFECTS)camera.shake(--fadeValue); //una explosion (limitar el F4 si una bomba esta tirada)
        }else{
            fading = false;
            PLAYING = true;
        }
    }
    int color = rand()%255; //JUST FOR THIS FRAME
    if (CLEAN_BUFFER)clear_to_color(dest, makecol(fadeValue,fadeValue,fadeValue));
    for (int j = 0; j < size; j++){ //HACER QUE EL TAMAÑO SEA DINAMICO (dependiendo de la resolucion)
        for (int i = 0; i < size; i++){
            putpixel(dest, i*separation+X,   j*separation+Y,   makecol(color,color,255));
        }
    }
    rect(dest, X, Y, size*separation, size*separation, makecol(color,color,255));
};

void Grid::fade(int value){     
     fadeValue   = value;     
     fading      = true;
};

/************************
     PRIVATE METHODS
************************/
