#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Bullet.h"

using namespace std;
using namespace sf;


class Enemy{
public:
    Enemy(Vector2f size);

    ~Enemy();

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
    Texture *Tenemy=NULL;
    Sprite *sprite_enemy;

    IntRect SpriteArray[6];

    Bullet *bala;

    int Spritevelocidad;
    int vida;
    bool disparado;
    bool izquierda;
    int posInicial;

};

#endif /* ENEMY_HPP */
