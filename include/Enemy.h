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

    int getX();

    int getY();

    void checkColl(Bullet bullet);

    void draw(sf::RenderWindow &window);

    int getVida();

private:
    //sf::RectangleShape enemy;
    sf::Texture *Tenemy=NULL;
    sf::Sprite *sprite_enemy;
    sf::Sprite *sprite_enemy2;

    int vida;
};

#endif /* ENEMY_HPP */
