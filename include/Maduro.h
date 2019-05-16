#ifndef MADURO_HPP
#define MADURO_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>

#include "Bullet.h"
#include "Player.h"
using namespace std;
using namespace sf;


class Maduro{
public:
    Maduro(Vector2f size);

    ~Maduro();

    void setPos(Vector2f newPos);

    void mover(int speed);

    bool activado(Player &player);

    Bullet getBala();

    int getX();

    int getY();

    bool checkColl(Bullet bullet);

    void draw(RenderWindow &window);

    void expropiese(Player &player);

    int getVida();

    void resetBala();

    void dispara();

private:
    //sf::RectangleShape enemy;
    Texture *Tmaduro=NULL;
    Sprite *sprite_maduro;

    IntRect SpriteArray[6];

    Bullet *bala;

    Clock tmovi;

    Clock cd;

    int Spritevelocidad;
    int vida;
    bool disparado;
    bool izquierda;
    bool aturdido;
    int posInicial;
    bool Activado;
    int posXTrump;
    int posYTrump;

};

#endif /* MADURO_HPP */
