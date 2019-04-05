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

    Player* player;
    Enemy* enemy;
    Civil* civil;
    Tilemap* map1;
    //Camara* camara;


};

#endif
