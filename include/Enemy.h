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

    void resetBala();

    void dispara();

    void mover(int speed);

private:
    //sf::RectangleShape enemy;
    sf::Texture *Tenemy=NULL;
    sf::Sprite *sprite_enemy;

    Bullet *bala;


    sf::IntRect SpriteRight[8];
    sf::IntRect SpriteLeft[8];
    //sf::IntRect SpriteRight[5];
    //sf::IntRect SpriteLeft[5];
    sf::IntRect SpriteDefault;

    int vida;
    bool disparado;
    bool izquierda;
    int posInicial;
    int velocidadSprite;


};

#endif /* ENEMY_HPP */
