/********************************
  Name: Particle System
  Copyright: 
  Author: Martin Cardozo 
  Date: 12/06/08 11:17
  Description: Sistema de Partículas
*********************************/

/************************
      INCLUDES
************************/

#include "Particle.h"

#include <allegro.h>
#include <vector>

/************************
        CLASS
************************/

class ParticleSystem { 
        
public:
  
    //CONSTRUCTOR
    ParticleSystem (int maxParticlesC, int XC, int YC, int forceC, int amplitudeC, int minXC, int maxXC, int minYC, int maxYC, int lifeTimeC);
    
    //FUNCTIONS
    void start();
    void stop();
    void kill();
    void changeColor(int R, int G, int B);
    void draw(BITMAP *dest);
    
    void incrementMaxParticles();
    void decrementMaxParticles();
    void incrementLifeTime();
    void decrementLifeTime();
    
    //GETTERS/SETTERS
    void setForce(int Value);
    void setAmplitude(int Value);
    void setMaxParticles(int Value);
    void setLifeTime(int Value);
    void setNewLocation(float pointX, float pointY);
    
    //VARIABLES
    float force;
    float amplitude;
    int minX;
    int maxX;
    int minY;
    int maxY;
    
    int orMinX;
    int orMaxX;
    int orMinY;
    int orMaxY;

private: 

    //FUNCTIONS
    void addParticle();
    void renewArray();
    bool checkBounds();
    
    //VARIABLES
    vector <Particle*> ArrayP; //MAIN ARRAY
    
    float X;
    float Y;
    int red;
    int green;
    int blue;
    int cantParticles;
    int maxParticles;
    int lifeTime;  
};

/************************
      CONSTRUCTOR
************************/

ParticleSystem::ParticleSystem (int maxParticlesC, int XC, int YC, int forceC, int amplitudeC, int minXC, int maxXC, int minYC, int maxYC, int lifeTimeC)
{                               
    maxParticles   = maxParticlesC;
    X              = XC;
    Y              = YC;
    force          = forceC;
    amplitude      = amplitudeC;
    orMinX         = minXC;
    orMaxX         = maxXC;
    orMinY         = minYC;
    orMaxY         = maxYC;
    minX           = minXC;
    maxX           = maxXC;
    minY           = minYC;
    maxY           = maxYC;
    lifeTime       = lifeTimeC;
};

/************************
     PUBLIC METHODS
************************/

void ParticleSystem::start(){
    for (int i = 0; i<maxParticles; i++){
        addParticle();
    }
};

void ParticleSystem::kill(){
    for (int i = 0; i<ArrayP.size(); i++){
        delete ArrayP[i];
    }
    maxParticles = 0;
};

void ParticleSystem::changeColor(int R, int G, int B){
    red   = R;
    green = G;
    blue  = B;
};

void ParticleSystem::draw(BITMAP *dest){
    set_add_blender(0, 0, 0, 255);
    drawing_mode(DRAW_MODE_TRANS, 0, 0, 0);
    if (EFFECTS){
        for (int i = 0; i<ArrayP.size(); i++){
            int Xp      = int(ArrayP[i]->X); 
            int Yp      = int(ArrayP[i]->Y);
            int color   = makecol(ArrayP[i]->red, ArrayP[i]->green, ArrayP[i]->blue);
            if (ArrayP[i]->update()){
                //rect(dest, Xp, Yp, Xp+1, Yp+1, color);
                putpixel(dest, Xp,     Yp,   color);
                putpixel(dest, Xp+1,   Yp,   color);
                putpixel(dest, Xp+1,   Yp+1, color);
                //putpixel(dest, Xp,     Yp+3, color);
                //putpixel(dest, Xp-3,   Yp,   color);
                //putpixel(dest, Xp-3,   Yp+5, color);
                //putpixel(dest, Xp+5,   Yp+5, color);
            }else{
                ArrayP.erase(ArrayP.begin()+i);
                cantParticles--;
            }
        }
    }else{
      circle(dest, int(X), int(Y), 3, makecol(255, 255, 255));
    }
    drawing_mode(DRAW_MODE_SOLID, 0, 0, 0);

    renewArray();
};

void ParticleSystem::incrementMaxParticles(){
    for(int i=0; i<50; i++){
        maxParticles ++;
        addParticle();
    }
};

void ParticleSystem::decrementMaxParticles(){
    if (maxParticles>0) {maxParticles--;}
};

void ParticleSystem::incrementLifeTime(){
    lifeTime += 10;
};

void ParticleSystem::decrementLifeTime(){
    if (lifeTime>0){lifeTime -= 10;}
};

/************************
     GETTERS/SETTERS
************************/

void ParticleSystem::setForce(int Value){
    if (Value<100 && Value>-100){force = Value/10;}
};

void ParticleSystem::setAmplitude(int Value){
    if (Value>0){
        amplitude = Value/10;
    }else{
        amplitude = 1;
    }
};

void ParticleSystem::setMaxParticles(int Value){
    maxParticles = Value;
};

void ParticleSystem::setLifeTime(int Value){
    lifeTime = Value;
};

void ParticleSystem::setNewLocation(float pointX, float pointY){
    X = pointX;
    Y = pointY;
};

/************************
     PRIVATE METHODS
************************/

void ParticleSystem::addParticle(){
    ArrayP.push_back(new Particle(X, Y, minX, maxX, minY, maxY, lifeTime, amplitude, force, red, green, blue));
    cantParticles++;
};

void ParticleSystem::renewArray(){
    if (cantParticles < maxParticles){
        int tmpInt = maxParticles - cantParticles;
        for (int i=0; i<tmpInt; i++){
            addParticle();
        }
    }
};

bool ParticleSystem::checkBounds(){
    if (Y < minY){return false;}
             
    if (Y > maxY){return false;}
                   
    if (X < minX){return false;} 
              
    if (X > maxX){return false;}
     
    return true;
};
