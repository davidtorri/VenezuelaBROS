#include <iostream>
#include <SFML/Graphics.hpp>
#include "Enemy.h"

#define kVida 30

Enemy::Enemy(sf::Vector2f size) {

    vida = kVida;

    disparado = false;

    Tenemy= new sf::Texture();

    Tenemy->loadFromFile("resources/soldier.png");
    sprite_enemy= new sf::Sprite(*Tenemy);


    //Le pongo el centroide donde corresponde
    sprite_enemy->setOrigin(75/2,75/2);
    //Cojo el sprite que me interesa por defecto del sheet
    sprite_enemy->setTextureRect(sf::IntRect(1*75, 1*75, 75, 75));
    sprite_enemy->setScale(0.7,0.7);
    // Lo dispongo en el centro de la pantalla
    sprite_enemy->setPosition(400, 200);

    bool izquierda = true;

    //debe ser la misma coordenada X en la que se genera el enemigo
    posInicial = 400;
}


Enemy::~Enemy() {
    //esto es el destructor

    delete[] sprite_enemy;
}

void Enemy::mover(int speed){

    sprite_enemy->move(speed, 0);

    if(getX() == posInicial-50)
        izquierda = false;
    else if(getX()== posInicial +50)
        izquierda = true;
}

int Enemy::getVida(){
    return vida;
}

int Enemy::getX(){
    return sprite_enemy->getPosition().x;
}

int Enemy::getY(){
    return sprite_enemy->getPosition().y;
}

void Enemy::setPos(sf::Vector2f newPos){
        sprite_enemy->setPosition(newPos);
}

void Enemy::resetBala(){
    disparado = false;
}

void Enemy::dispara(){
    if(!disparado)
    {
        bala = new Bullet(sf::Vector2f(50,50),1);
        bala->setPos(sprite_enemy->getPosition());
        disparado = true;
    }
}

void Enemy::checkColl(Bullet bullet){
        if(bullet.getRight() > sprite_enemy->getPosition().x &&
           bullet.getTop() < sprite_enemy->getPosition().y ){
            vida = vida - bullet.getDmg();
        }
}

void Enemy::draw(sf::RenderWindow &window){
    if(vida > 0)
        window.draw(*sprite_enemy);
        if(izquierda)
            mover(-1);
        else if(!izquierda)
            mover(1);

    if(disparado){
        bala->draw(window);
        bala->fire(-4);
    }
}
