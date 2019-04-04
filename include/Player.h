#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Bullet.h"


class Player{
public:
    Player(sf::Vector2f size);

    ~Player();

    void move(sf::Vector2f dir);

    int getX();

    int getY();

    void draw(sf::RenderWindow &window);

    //En esta funcion de hace una llamada a la Ulti, la cual en cuanto llegue a la posicion actualdel personaje
    //eliminara a todos los enemigos y civiless que encuentre en el mapa
    void OTAN();

    //Dentro de esta funcino se comprueba la posicion del personaje, es decir hacce donde mira
    //y se dibujara un sprite del muro en dicho lugar
    void Muro(bool derecha);

    void ReseteaMuro();
private:
   // sf::RectangleShape player;
    sf::Texture *Tplayer=NULL;
    sf::Sprite *sprite_player;

    sf::Texture *Tmuro=NULL;
    sf::Sprite *sprite_muro;

    bool muroPuesto;

};

#endif /* PLAYER_HPP */
