/********************************
  Name: Insane 2 
  Copyright: 
  Author: Martin Cardozo
  Date: 17/06/08 12:31
  Description: Secuela de Insane
*********************************/

/*******************************************
        LISTA DE MEJORAS/TO DO LIST
/*******************************************
/*---------------------------------------------------------------------------.
*  - Que el fondo se mueva bien (no sea estático).                     | [X] | 
*  - Efecto de onda expansiva (es una explosion grande en realidad).   | [X] |
*  - IA de los enemigos.                                               | [ ] |
*  - Que no se dibuje lo que esta afuera del viewport (funcion en VP). | [ ] |
*  - Implementar radar (otro minibuffer abajo a la izquierda (como     |     |
*    vas a renderizas un pixel por objeto no hace falta hacer el zoom).| [ ] |
*  - dropBomb() tiene que ser parte de una clase Explosion (que es la  | [ ] |
*    misma que se usa para todas las explosiones. Parametros: X, Y,    |     |
*    calidad (cant de particulas (la bomba tira muchas mas)), color    |     |
*    y vida.                                                           |     |
*  - Que para tirar la bomba se cargue una barra (que se incrementa    | [ ] |
*    a medida que matas).                                              |     |
*  - Hacer andar los FPS.                                              | [X] |
*  - Hacer que una ventana te pregunte si queres jugar en fullscreen.  | [ ] |
*----------------------------------------------------------------------------´

/************************
INCLUDES/GLOBAL CONSTANTS
************************/

using namespace std;

#include <Math.h>
#include <allegro.h>
#include <vector>

//STATICS
const int SCREEN_WIDTH  = 800;
const int SCREEN_HEIGHT = 600;

bool EFFECTS      = false;
bool CLEAN_BUFFER = true;
bool PLAYING      = true;  //IF FALSE, PLAYER CAN'T MOVE OR SHOOT
bool blinked;

//MY CLASSES
#include "Timer.h"
Timer timer;
#include "MathHelper.h"
MathHelper MathFunc;
#include "Helper.h"
Helper GHelper; //GameHelper 

#include "Viewport.h"
Viewport camera(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
#include "Grid.h"
Grid     grid(0, 0, 2000);
#include "Mouse.h"
Mouse    mouse;
#include "Player.h"
Player   player;
#include "Enemy.h"
#include "Bullet.h"

/************************
    PRIVATE VARIABLES
************************/

//FUNCTIONS
void init();
void deinit();
void createEntities();
void addEnemies(int Number, int evilness);

void checkInput();
void process();
void checkCollisions();
void getFPS();  

void shoot();
void dropBomb();

void draw();
void drawBG();
void drawEffects();
void drawExplosions();
void drawShockWave();
void drawBullets();
void drawEnemies();
void drawPlayer();
void drawGUI();	

//VARIABLES
int weapon;
int cantBombs;
int charge;
int score;
int minBomb;

//ARRAYS
vector <Bullet*> bullet;
vector <Enemy*>  enemy;
vector <Bullet*> shockWave;

//GRAPHICS
BITMAP *Buffer;

//KEYS
bool F4;           //EFFECTS SWITCH
bool BOMB_RELEASE;
bool SHOOT;
bool F11;

//WEAPONS
bool WEAP2;
bool WEAP3;

//FPS
int tmpFPS;
int FPS;

/************************
       MAIN LOOP
************************/

int main() {
	init();
    
    weapon = 1;
    minBomb = 20;
    createEntities();
    
	while (!key[KEY_ESC]) {
        if (PLAYING)checkInput();
		process();
		draw();		
	}

	deinit();
	return 0;
};
END_OF_MAIN()

/************************
ALLEGRO's DEFAULT METHODS
************************/

void init() {
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}

	install_timer();
	install_keyboard();
	install_mouse();
};

void deinit(){
	clear_keybuf();
};

/************************
    PRIVATE METHODS
************************/

void createEntities(){     
    timer.init();
    Buffer = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
};

void addEnemies(int Number, int evilness){
    for (int i = 0; i<Number; i++){
        enemy.push_back(new Enemy(rand()%2000, rand()%2000, rand()%255, rand()%255, rand()%255, evilness, evilness*10)); //REEMPLAZAR ESE "2000" POR LOS LIMITES DEL MAPA
    }
};

void checkInput(){//ORDENAR TODO ESTE METODO (clase inputManager?) [que funcione como un state, en el sentido en que nada mas llama a cosas de aca]
    if (mouse_b & 1 && !SHOOT) shoot(); SHOOT = true;              
    
    if (key[KEY_SPACE] && !BOMB_RELEASE){ //CHECKEAR SI TIENE BOMBAS DISPONIBLES
        if (charge == minBomb || cantBombs){
            blinked = false;
            PLAYING      = false;
            BOMB_RELEASE = true;
            dropBomb();
            grid.fade(255);
            addEnemies(2, 4);
            if (score>3000)weapon = 3; WEAP3 = true;
        }
        if (charge == minBomb) charge = 0;
        if (cantBombs > 0)cantBombs--;
    }
    
    //CHANGE WEAPONS
    if (key[KEY_1]) weapon = 1; //PISTOL
    if (key[KEY_2] && WEAP2) weapon = 2; //SHOTGUN
    if (key[KEY_3] && WEAP3) weapon = 3; //INSANE
    //-CHANGE WEAPONS-
    
    if (key[KEY_F4]){
        if (!F4){
            F4 = true;
            EFFECTS = !EFFECTS;
        }
    }
    
    if (key[KEY_F11] && !F11)CLEAN_BUFFER = !CLEAN_BUFFER; F11 = true;
    
        //-KEY RELEASES-//
    if (!key[KEY_F4])   F4           = false;
    if (!key[KEY_SPACE])BOMB_RELEASE = false;
    if (!(mouse_b & 1)) SHOOT        = false;
    if (!key[KEY_F11])  F11          = false;
};

void process(){
    checkCollisions();
    getFPS();
};

void checkCollisions(){
     for (int i = 0; i<bullet.size(); i++){
         for (int j = 0; j<enemy.size(); j++){
             if (GHelper.hitArea(int(bullet[i]->X), int(bullet[i]->Y), bullet[i]->size, int(enemy[j]->X)-20, int(enemy[j]->Y)-20, enemy[j]->size*2)){
                 if (charge<minBomb){
                    charge ++;
                 }else{
                    if (weapon==1)weapon = 2; WEAP2 = true;
                    addEnemies(3, 3);
                    cantBombs++;
                    charge = 1;
                 }
                 bullet.erase(bullet.begin()+i);
                 score += enemy[j]->die(); //LLAMAR A ESTA FUNCION PARA HACER LA EXPLOSION Y PARA, POR EJEMPLO, CREAR MAS MALOS
                 enemy.erase(enemy.begin()+j);
             }
         }
     }
};

void getFPS(){
    if (timer.GetEllapsedTime() < 500){
        tmpFPS++;
    }else{
        addEnemies(1, 1);
        FPS    = tmpFPS * 2;
        tmpFPS = 0;
        timer.reset();
    }
};

void draw(){
    camera.X = int(player.X)-(SCREEN_WIDTH/2);
    camera.Y = int(player.Y)-(SCREEN_HEIGHT/2);
    
    drawBG();
    drawEffects();
    drawBullets();
    drawEnemies();
    drawPlayer();
    drawGUI();
    blit(Buffer, screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
};

void shoot(){
    double angle = atan2(mouse_y-player.Y, mouse_x-player.X);
    double INCY = sin(angle);
    double INCX = cos(angle);
    switch(weapon){
        case 1: //PISTOL
            bullet.push_back(new Bullet(player.X, player.Y, INCX, INCY, 200, 200, 255));
            break;
        case 2: //SHOTGUN
            bullet.push_back(new Bullet(player.X, player.Y, INCX, INCY, 128, 255, 128));
            INCY = sin(angle+.1f);
            INCX = cos(angle+.1f);
            bullet.push_back(new Bullet(player.X, player.Y, INCX, INCY, 128, 255, 128));
            INCY = sin(angle-.1f);
            INCX = cos(angle-.1f);
            bullet.push_back(new Bullet(player.X, player.Y, INCX, INCY, 128, 255, 128));
            break;
        case 3: //INSANE
            bullet.push_back(new Bullet(player.X, player.Y, INCX, INCY, 255, 128, 128));
            INCY = sin(angle+.05f);
            INCX = cos(angle+.05f);
            bullet.push_back(new Bullet(player.X, player.Y, INCX, INCY, 255, 128, 128));
            INCY = sin(angle-.05f);
            INCX = cos(angle-.05f);
            bullet.push_back(new Bullet(player.X, player.Y, INCX, INCY, 255, 128, 128));
            INCY = sin(angle+.1f);
            INCX = cos(angle+.1f);
            bullet.push_back(new Bullet(player.X, player.Y, INCX, INCY, 255, 128, 128));
            INCY = sin(angle-.1f);
            INCX = cos(angle-.1f);
            bullet.push_back(new Bullet(player.X, player.Y, INCX, INCY, 255, 128, 128));
            break;
        case 4: //PLASMA
            break;
    }
};

void dropBomb(){
    double X = player.X;
    double Y = player.Y;
    for (int i = 0; i<360; i++) {
        double INCY =  cos(i) * 3;
        double INCX = -sin(i) * 3;
        shockWave.push_back(new Bullet(X, Y, INCX, INCY, 0,  0,  0));
        //shockWave.push_back(new Bullet(X, Y, INCX, INCY, 200, 200, 255));
        //shockWave.push_back(new Bullet(X, Y, INCX, INCY, 100, 100, 255));
    }
    for (int i = 0; i<120; i+=3) {
        double INCY =  cos(i) * .8f;
        double INCX = -sin(i) * .8f;
        bullet.push_back(new Bullet(X, Y, INCX, INCY, 50,  50,  255));
    }
};

void drawBG(){ 
    grid.draw(Buffer);
};

void drawEffects(){
     drawExplosions();
     drawShockWave();
};

void drawExplosions(){
     //FOR
};

void drawShockWave(){
    for (int i = 0; i<shockWave.size(); i++){
        shockWave[i]->draw(Buffer);
    }
};

void drawBullets(){
    for (int i = 0; i<bullet.size(); i++) {
        if (!(bullet[i]->draw(Buffer))){
            //bullet[i]->kill(); //PREGUNTAR A DR IN VITRO SI HACE FALTA DESTRUIR CADA CLASESITA
            bullet.erase(bullet.begin()+i);
        }
    }
};

void drawEnemies(){
    for (int i = 0; i<enemy.size(); i++){
        enemy[i]->draw(Buffer);
    }
};

void drawPlayer(){
     player.draw(Buffer);
};

void drawGUI(){
     //BOMB BAR
     int limit  = 50+minBomb*10;
     int CHARGE = 50+charge*10;
     if (charge < minBomb && cantBombs == 0){
        rectfill(Buffer, 50, 10, CHARGE, 17, makecol(255,255,255));
     }else{
        if (blinked){
           rectfill(Buffer, 50, 10, 50+charge*10, 17, makecol(255,255,255));
        }else{
           rectfill(Buffer, 50, 10, CHARGE, 17, makecol(50,50,255));
        }
        blinked = !blinked;
     }
     textprintf_ex(Buffer, font,  10, 10, makecol(255,255,255), -1, "Bomb: ");
     rect(Buffer, 50, 10, limit, 17, makecol(255,255,255));
     if (cantBombs)textprintf_ex(Buffer, font, limit+4, 10, makecol(200,200,255), -1, "x%i", cantBombs);
     //-BOMB BAR
     textprintf_ex(Buffer, font,  10, 25, makecol(200,200,255), -1, "SCORE: %i", score);
     textprintf_ex(Buffer, font,  730, 10, makecol(255,255,255), -1, "FPS: %i", FPS);
     mouse.draw(Buffer);
};
