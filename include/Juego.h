#ifndef Juego_H
#define Juego_H

#include <sstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Tilemap.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
#include "Juego.h"
#include "Camara.h"
#include "Civil.h"

using namespace std;
using namespace sf;

//version con cd
class Juego
{
	public:
        ~Juego(void);
        static Juego *getInstance()
        {
            if(unica_instancia == 0)
            unica_instancia = new Juego();
            return unica_instancia;
        }

        static void ResetInstance()
        {
            delete unica_instancia;
            unica_instancia = 0;
        }


        int estado = 1;
        int gid_pos;
        void crearVentana();
        void cargarCamara();
        void cargarPlayer();
        void cargarEnemy();
        void cargarCivil();
        void cargarMapa();
        void cargarPetroleo();

        void bucleJuego();

        int right = 600;
        int left = 150;

        RenderWindow window;
        View view1;
        View view2;




    private:
        Juego();
        static Juego* unica_instancia;

        void Update();       // Actualiza las condiciones del juego (todo)
        void Render(float);  // Renderiza todos los sprites
        void processEvents();  // Captura y procesa eventos
        void handlePlayerInput(Keyboard::Key key, bool isPressed);  // Maneja eventos

        void comprueboMuertes();
        void enemigoDisparaYComprueboColisiones();
        void resetHabilidades();

        Player* player; // Juego principal
        Enemy* enemy;   // Enemigo principal
        Enemy* enemy2;  // Enemigo dos
        Civil* civil;   // Personaje NPC del juego
        Tilemap* map1;  // Mapa del juego

        Texture *Tpetroleo;
        Sprite *sprite_petroleo;
        Sprite *sprite_petroleo1;
        Sprite *sprite_petroleo2;
        Sprite *sprite_petroleo3;
        //Camara* camara;

        //Arrays dinmicos para gestionar las balas del juego
        vector<Bullet> bulletVec;
        vector<Bullet> bulletVecEnemy;


        //Variables para controlar el disparo y algo raro de la derecha
        bool isFiring = false;
        bool derecha  = true;
        bool firstTime;
        bool p1,p2,p3,p4;

        double jesustonto;


        //============================
        //  Relojes
        //============================
        Clock cd;           // Cooldown del muro
        Clock cd2;          // Cooldown de la bala
        Clock cd3;          // Cooldown de la bala del enemigo
        Clock cdE;
        Clock render_time;  // Reloj que controla la velocidad del render (default 120fps)
        Clock update_time;  // Reloj que controla la velocidad del update (default 15 fps)

        //Eventos
        bool			isMovingUp;
        bool			isMovingDown;
        bool			isMovingRight;
        bool			isMovingLeft;


};

#endif
