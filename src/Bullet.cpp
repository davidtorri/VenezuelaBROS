#include <iostream>
#include <SFML/Graphics.hpp>
#include "Bullet.h"

#define kDmg 10

Bullet::Bullet(sf::Vector2f size){

    sprite_bullet.setSize(size);
    sprite_bullet.setFillColor(sf::Color::White);

//Tbullet->loadFromFile("resources/sprites.png");
//sprite_bullet= new sf::Sprite(*Tbullet);



//Le pongo el centroide donde corresponde
//  sprite_bullet->setOrigin(130/2,40/2);
//Cojo el sprite que me interesa por defecto del sheet
//sprite_bullet->setTextureRect(sf::IntRect(1950, 1580, 95, 40));
//sprite_bullet->setScale(1,1);
// Lo dispongo en el centro de la pantalla
//sprite_bullet->setPosition(323, 160);
}
//Bullet::Bullet(sf::Vector2f size) {
  //  sprite_bullet->setSize(size);
//}

Bullet::~Bullet() {
    //delete[] sprite_bullet;
}

void Bullet::fire(int speed){
    sprite_bullet.move(speed, 0);
}

int Bullet::getRight(){
    return sprite_bullet.getPosition().x + sprite_bullet.getSize().x;
}

int Bullet::getLeft(){
    return sprite_bullet.getPosition().x;
}

int Bullet::getTop(){
    return sprite_bullet.getPosition().y;
}

int Bullet::getBottom(){
    return sprite_bullet.getPosition().y + sprite_bullet.getSize().y;
}

int Bullet::getDmg(){
    return kDmg;
}

void Bullet::draw(sf::RenderWindow &window){
    window.draw(sprite_bullet);
}

void Bullet::setPos(sf::Vector2f newPos){
    sprite_bullet.setPosition(newPos);
}
