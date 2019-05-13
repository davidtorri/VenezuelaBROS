#ifndef MADURO_HPP
#define MADURO_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Bullet.h"

using namespace std;
using namespace sf;


class Maduro{
public:
    Maduro(Vector2f size);

    ~Maduro();

    void setPos(Vector2f newPos);

    void mover(int speed);

    Bullet getBala();

    int getX();

    int getY();

    void checkColl(Bullet bullet);

    void draw(RenderWindow &window);

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

    int Spritevelocidad;
    int vida;
    bool disparado;
    bool izquierda;
    int posInicial;

};

#endif /* MADURO_HPP */
