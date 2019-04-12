#ifndef NEWFILE_HPP
#define NEWFILE_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Bullet{
public:
    Bullet(Vector2f size,int tipo);

    ~Bullet();

    void fire(int speed);

    int getRight();

    int getLeft();

    int getTop();

    int getBottom();

    int getDmg();

    const Vector2f getPositionSprite();

    void draw(RenderWindow &window);

    void setPos(Vector2f newPos);

private:
    //sf::RectangleShape sprite_bullet;
    Texture *Tbullet;
    Sprite *sprite_bullet;

    int dmg;


};

#endif /* NEWFILE_HPP */
