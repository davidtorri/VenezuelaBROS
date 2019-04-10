#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <stdlib.h>
#include <SFML/Graphics.hpp>

#include "Bullet.h"


class Player{
public:
    Player(sf::Vector2f size);

    ~Player();

    void move(sf::Vector2f dir);

    void CalcularSprite();

    int getX();

    int getY();

    int getVida();

    int getPetroleo();

    void draw(sf::RenderWindow &window, float);

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

    void checkColl(Bullet bullet);

    void setInterpolando(bool t){interpolando = false;};

private:

    //Variables de movimiento
    sf::Vector2f pos_anterior;
    sf::Vector2f pos_nueva;

    sf::Vector2f pos_anteriorOTAN;
    sf::Vector2f pos_nuevaOTAN;

    sf::IntRect SpriteRight[6];
    sf::IntRect SpriteLeft[6];
    sf::IntRect SpriteDefault;

    bool interpolando = false;

   // sf::RectangleShape player;
    sf::Texture *Tplayer=NULL;
    sf::Sprite *sprite_player;

    sf::Texture *Tmuro=NULL;
    sf::Sprite *sprite_muro;

    sf::Texture *Totan=NULL;
    sf::Sprite *sprite_otan;

    sf::Texture *Tbomba=NULL;
    sf::Sprite *sprite_bomba;

    Bullet *bala;
    std::vector<sf::Sprite> bombas;

    int petroleo;
    int vida;
    int velocidad;
    bool muroPuesto;
    bool otandisponible;
    bool llamada;
    bool disparado;
    bool disparoDerecha;

    void moveOtan(sf::Vector2f dir);
    void moveBomba();

};

#endif /* PLAYER_HPP */
