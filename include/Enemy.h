#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Bullet.h"


class Enemy{
public:
    Enemy(sf::Vector2f size);

    ~Enemy();

    void setPos(sf::Vector2f newPos);

    void mover(int speed);

    int getX();

    int getY();

    void checkColl(Bullet bullet);

    void draw(sf::RenderWindow &window);

    int getVida();

    void resetBala();

    void dispara();

private:
    //sf::RectangleShape enemy;
    sf::Texture *Tenemy=NULL;
    sf::Sprite *sprite_enemy;

    Bullet *bala;

    int vida;
    bool disparado;
    bool izquierda;
    int posInicial;

};

#endif /* ENEMY_HPP */
