#include <iostream>
#include <SFML/Graphics.hpp>
#include "Bullet.h"

Bullet::Bullet(sf::Vector2f size,int tipo){

    Tbullet= new sf::Texture();

    //Es una bala del player
    if(tipo == 0){

        Tbullet->loadFromFile("resources/eeuu.png");
        sprite_bullet= new sf::Sprite(*Tbullet);
        //Le pongo el centroide donde corresponde
        sprite_bullet->setOrigin(130/2,40/2);
        //Cojo el sprite que me interesa por defecto del sheet
        //sprite_bullet->setTextureRect(sf::IntRect(0*75, 0*75, 75, 75));
        sprite_bullet->setScale(0.020,0.020);
        // Lo dispongo en el centro de la pantalla
        sprite_bullet->setPosition(323, 160);
        dmg =  10;
    }
    //Es una bala del enemigo
    else{
        Tbullet->loadFromFile("resources/plane.png");
        sprite_bullet= new sf::Sprite(*Tbullet);
        //Le pongo el centroide donde corresponde
        sprite_bullet->setOrigin(130/2,40/2);
        //Cojo el sprite que me interesa por defecto del sheet
        sprite_bullet->setTextureRect(sf::IntRect(0*75, 0*75, 75, 75));
        sprite_bullet->setScale(1,1);
        // Lo dispongo en el centro de la pantalla
        sprite_bullet->setPosition(323, 160);
        dmg = 5;
    }

}

Bullet::~Bullet() {
    //delete[] sprite_bullet;
}

void Bullet::fire(int speed){
    sprite_bullet->move(speed, 0);
}

int Bullet::getRight(){
    //return sprite_bullet.getPosition().x + sprite_bullet.getSize().x;
    return sprite_bullet->getPosition().x;
}

int Bullet::getLeft(){
    return sprite_bullet->getPosition().x;
}

int Bullet::getTop(){
    return sprite_bullet->getPosition().y;
}

int Bullet::getBottom(){
    return sprite_bullet->getPosition().y + sprite_bullet->getScale().y;
}

int Bullet::getDmg(){
    return dmg;
}

const sf::Vector2f Bullet::getPositionSprite(){
    return sprite_bullet->getPosition();
}

void Bullet::draw(sf::RenderWindow &window){
    window.draw(*sprite_bullet);
}

void Bullet::setPos(sf::Vector2f newPos){
    sprite_bullet->setPosition(newPos);
}
