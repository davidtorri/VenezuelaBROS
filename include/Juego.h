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
        void crearVentana();
        void cargarCamara();
        void cargarPlayer();
        void cargarEnemy();
        void cargarCivil();
        void cargarMapa();

        void bucleJuego();


        int right = 600;
        int left = 150;

         sf::RenderWindow window;
        sf::View view1;
        sf::View view2;




    private:
        Juego();
        static Juego* unica_instancia;

        void Update();       // Actualiza las condiciones del juego (todo)
        void Render(float);  // Renderiza todos los sprites
        void processEvents();  // Captura y procesa eventos
        void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);  // Maneja eventos

        Player* player; // Juego principal
        Enemy* enemy;   // Enemigo principal
        Civil* civil;   // Personaje NPC del juego
        Tilemap* map1;  // Mapa del juego
        //Camara* camara;

        //Arrays dinmicos para gestionar las balas del juego
        std::vector<Bullet> bulletVec;
        std::vector<Bullet> bulletVecEnemy;

        //Variables para controlar el disparo y algo raro de la derecha
        bool isFiring = false;
        bool derecha  = true;
        bool firstTime;


        //============================
        //  Relojes
        //============================
        sf::Clock cd;           // Cooldown del muro
        sf::Clock cd2;          // Cooldown de la bala
        sf::Clock cd3;          // Cooldown de la bala del enemigo
        sf::Clock render_time;  // Reloj que controla la velocidad del render (default 120fps)
        sf::Clock update_time;  // Reloj que controla la velocidad del update (default 15 fps)

        //Eventos
        bool			isMovingUp;
        bool			isMovingDown;
        bool			isMovingRight;
        bool			isMovingLeft;


};

#endif
