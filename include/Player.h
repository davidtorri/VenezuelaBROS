#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <stdlib.h>
#include <SFML/Graphics.hpp>

#include "Bullet.h"

using namespace std;
using namespace sf;


class Player{
public:
    Player(Vector2f size);

    ~Player();

    void move(Vector2f dir);

    void CalcularSprite();

    Bullet getBala();

    int getX();

    int getY();

    int getVida();

    int getPetroleo();

    void draw(RenderWindow &window, float);

    bool getBalaActivada();

    //En esta funcion de hace una llamada a la Ulti, la cual en cuanto llegue a la posicion actualdel personaje
    //eliminara a todos los enemigos y civiless que encuentre en el mapa
    void OTAN();

    //Dentro de esta funcino se comprueba la posicion del personaje, es decir hacce donde mira
    //y se dibujara un sprite del muro en dicho lugar
    void Muro(bool derecha);

    void dispara(bool derecha);

    void ReseteaMuro();

    void ResetPosOtan();

    void ResetPosBombas();

    void setPetroleo();

    void resetBala();

    void CreaSpriteOtan();

    void CreaSpriteBomba();

    void setVida(int i);

    bool checkColl(Bullet bullet);

    void setInterpolando(bool t){interpolando = false;};

private:

    //Variables de movimiento
    Vector2f pos_anterior;
    Vector2f pos_nueva;

    Vector2f pos_anteriorOTAN;
    Vector2f pos_nuevaOTAN;

    IntRect SpriteRight[6];
    IntRect SpriteLeft[6];
    IntRect SpriteDefault;

    bool interpolando = false;

   // sf::RectangleShape player;
    Texture *Tplayer=NULL;
    Sprite *sprite_player;

    Texture *Tmuro=NULL;
    Sprite *sprite_muro;

    Texture *Totan=NULL;
    Sprite *sprite_otan;

    Texture *Tbomba=NULL;
    Sprite *sprite_bomba;

    Bullet *bala;
    vector<Sprite> bombas;

    int petroleo;
    int vida;
    int velocidad;
    bool muroPuesto;
    bool otandisponible;
    bool llamada;
    bool disparado;
    bool disparoDerecha;

    void moveOtan(Vector2f dir);
    void moveBomba();

};

#endif /* PLAYER_HPP */
