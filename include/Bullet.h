#ifndef NEWFILE_HPP
#define NEWFILE_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

class Bullet{
public:
    Bullet(sf::Vector2f size);

    ~Bullet();

    void fire(int speed);

    int getRight();

    int getLeft();

    int getTop();

    int getBottom();

    int getDmg();

    void draw(sf::RenderWindow &window);

    void setPos(sf::Vector2f newPos);

private:
    sf::RectangleShape sprite_bullet;
    //sf::Texture *Tbullet;
    //sf::Sprite *sprite_bullet;


};

#endif /* NEWFILE_HPP */
