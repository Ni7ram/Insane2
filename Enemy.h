/********************************
  Name: Enemy
  Copyright:
  Author: Martin Cardozo
  Date: 08/07/08 09:29
  Description: Enemy Class
********************************/

/************************
        INCLUDES
************************/

/************************
        CLASS
************************/

class Enemy {   

public:
       
    //CONSTRUCTOR
    Enemy(int XC, int YC, int redC, int greenC, int blueC, int speedM, int scoreC);
    
    //FUNCTIONS 
    void draw(BITMAP *dest);
    bool alreadyHited();
    int die();
    
    //VARIABLES
    double X;
    double Y;
    int    size;

private:

    //FUNCTIONS
    void init();
    bool update();
    bool checkBounds();
    void inertia();
    
    void goUp();
    void goDown();
    void goRight();
    void goLeft();
    
    //VARIABLES  
    ParticleSystem* Effect;
    
    int minX;
    int maxX;
    int minY;
    int maxY;
    
    int red;
    int green;
    int blue;
    
    int   maxSpeed; 
    float speedX;
    float speedY; 
    float aceleration;
    float inercia;
    
    bool firstHit; //FLAG
    int speedMultiplier;
    int score;
};

/************************
      CONSTRUCTOR
************************/

Enemy::Enemy(int XC, int YC, int redC, int greenC, int blueC, int speedM, int scoreC){    
    X = XC;
    Y = YC;
    size = 12;            

    red   = redC;
    green = greenC;
    blue  = blueC;
    
    score           = scoreC;
    speedMultiplier = speedM;
   
    //Effect = new ParticleSystem(75, int(X), int(Y), 0, 0, 0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 10);
    init();
};

/************************
     PUBLIC METHODS
************************/

void Enemy::draw(BITMAP *dest){
     //if (update()){
         double angle = atan2(player.Y-Y, player.X-X);
         double INCY = sin(angle);
         double INCX = cos(angle);
    
         X += INCX * speedMultiplier;
         Y += INCY * speedMultiplier;
    
         X = (X - camera.X);
         Y = (Y - camera.Y);
         //Effect->setNewLocation(X,Y);
         //if (EFFECTS){
          // Effect->draw(dest);
         //}else{
         int sizeRect = size*2;
         switch(speedMultiplier){
             case 1:
                 circle(dest, int(X), int(Y), size, makecol(red, green, blue));
                 set_trans_blender(0, 0, 0, 75);
                 drawing_mode(DRAW_MODE_TRANS, 0, 0, 0);
                 circlefill(dest, int(X), int(Y), size, makecol(red, green, blue));
                 drawing_mode(DRAW_MODE_SOLID, 0, 0, 0);
                 circle(dest, int(X), int(Y), 3, makecol(red, green, blue));
                 break;
             case 2:
                 rect(dest, int(X), int(Y), int(X)+size, int(Y)+size, makecol(red, green, blue));
                 set_trans_blender(0, 0, 0, 75);
                 drawing_mode(DRAW_MODE_TRANS, 0, 0, 0);
                 circlefill(dest, int(X), int(Y), size, makecol(red, green, blue));
                 drawing_mode(DRAW_MODE_SOLID, 0, 0, 0);
                 circle(dest, int(X), int(Y), 3, makecol(red, green, blue));
                 break;
             case 3:
                 rect(dest, int(X), int(Y), int(X)+sizeRect, int(Y)+sizeRect, makecol(red, green, blue));
                 set_trans_blender(0, 0, 0, 75);
                 drawing_mode(DRAW_MODE_TRANS, 0, 0, 0);
                 rectfill(dest, int(X), int(Y), int(X)+sizeRect, int(Y)+sizeRect, makecol(red, green, blue));
                 drawing_mode(DRAW_MODE_SOLID, 0, 0, 0);
                 rect(dest, int(X)+8, int(Y)+8, int(X)+16, int(Y)+16, makecol(red, green, blue));
                 break;
             case 4:
                 circlefill(dest, int(X), int(Y), size, makecol(red, green, blue));
                 break;
         }
         //}
     //}
};

bool Enemy::alreadyHited(){
    if (!firstHit){
        firstHit = true;
        return false;
    }
    return true;
};

int Enemy::die(){
     //CREAR EXPLOSION
     switch(speedMultiplier){
         case 1:
             break;
         case 2:
             break;
         case 3:
             break;
         case 4:
             //enemy.push_back(new Enemy(X, Y, rand()%255, rand()%255, rand()%255, 1, 10));  no puede acceder a enemy :S (xq no esta creado)
             //enemy.push_back(new Enemy(X+50, Y+50, rand()%255, rand()%255, rand()%255, 1, 10));
             break;
     }
     return score;
};

/************************
     PRIVATE METHODS
************************/
void Enemy::init(){
    aceleration = .3f;
    inercia     = .1f;
    maxSpeed    = 10;
    minX = 0; 
    minY = 0;
    maxX = SCREEN_WIDTH;
    maxY = SCREEN_HEIGHT;
    //Effect->changeColor(red, green, blue);
    //Effect->start();
};

bool Enemy::update(){
    if (!checkBounds()) return false;
    inertia();
     
    return true;
};

bool Enemy::checkBounds(){
    if (Y < minY)return false;

    if (Y > maxY)return false;

    if (X < minX)return false;

    if (X > maxX)return false;
     
    return true;
};

void Enemy::inertia(){
     if (speedX){
         if (speedX > 0){
             speedX -= inercia;
         }else{
             if (speedX){
                 speedX +=inercia;
             }
         }          
     } 
    
     if (speedY){
         if (speedY > 0){
             speedY -= inercia;
         }else{
             if (speedY){
                 speedY += inercia;
             }
         }
     }
};

void Enemy::goUp(){
    if (speedY>-maxSpeed)speedY -= aceleration;
};

void Enemy::goDown(){
    if (speedY<maxSpeed) speedY += aceleration;
};

void Enemy::goRight(){
    if (speedX<maxSpeed) speedX += aceleration;
};

void Enemy::goLeft(){
    if (speedX>-maxSpeed)speedX -= aceleration;
};
