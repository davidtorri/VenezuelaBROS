#include <iostream>
#include <SFML/Graphics.hpp>
#include "Bullet.h"

Bullet::Bullet(Vector2f size,int tipo){

    Tbullet= new Texture();
    activada = false;

    //Es una bala del player
    if(tipo == 0){

        Tbullet->loadFromFile("resources/eeuu.png");
        sprite_bullet= new Sprite(*Tbullet);
        //Le pongo el centroide donde corresponde
        sprite_bullet->setOrigin(130/2,40/2);
        //Cojo el sprite que me interesa por defecto del sheet
        //sprite_bullet->setTextureRect(sf::IntRect(0*75, 0*75, 75, 75));
        sprite_bullet->setScale(0.0180,0.0180);
        // Lo dispongo en el centro de la pantalla
        sprite_bullet->setPosition(323, 160);
        dmg =  10;
    }
    //Es una bala del enemigo
    else{
        Tbullet->loadFromFile("resources/bala2.png");
        sprite_bullet= new Sprite(*Tbullet);
        //Le pongo el centroide donde corresponde
        sprite_bullet->setOrigin(130/2,40/2);
        //Cojo el sprite que me interesa por defecto del sheet
        //sprite_bullet->setTextureRect(IntRect(0*75, 0*75, 75, 75));
        sprite_bullet->setScale(0.04,0.04);
        // Lo dispongo en el centro de la pantalla
        sprite_bullet->setPosition(323, 160);
        dmg = 5;
    }

}

Bullet::~Bullet() {
/*    delete sprite_bullet;
    sprite_bullet = NULL;
    delete Tbullet;
    Tbullet = NULL;*/
}

void Bullet::activaBala()
{
    activada = true;
}

void Bullet::desactiva()
{
    activada = false;
    sprite_bullet->setPosition(0,-1000);

}

bool Bullet::getActivada()
{
    return activada;
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

const Vector2f Bullet::getPositionSprite(){
    return sprite_bullet->getPosition();
}

void Bullet::draw(RenderWindow &window){
    if(sprite_bullet!=NULL)
    {
        window.draw(*sprite_bullet);
    }
}

void Bullet::setPos(Vector2f newPos){
    sprite_bullet->setPosition(newPos);
}
