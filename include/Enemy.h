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
    
    void checkColl(Bullet bullet);
    
    void draw(sf::RenderWindow &window);
    
    
    
private:
    //sf::RectangleShape enemy;
    sf::Texture *Tenemy=NULL;
    sf::Sprite *sprite_enemy;
    sf::Sprite *sprite_enemy2;
};

#endif /* ENEMY_HPP */