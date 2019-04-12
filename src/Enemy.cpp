#include <iostream>
#include <SFML/Graphics.hpp>
#include "Enemy.h"

#define kVida 30

Enemy::Enemy(Vector2f size) {

    vida = kVida;

    disparado = false;

    Tenemy= new Texture();

    Tenemy->loadFromFile("resources/soldier.png");
    sprite_enemy= new Sprite(*Tenemy);

    bala = new Bullet(Vector2f(50,50),1);


    //Le pongo el centroide donde corresponde
    sprite_enemy->setOrigin(75/2,75/2);
    //Cojo el sprite que me interesa por defecto del sheet
    sprite_enemy->setTextureRect(IntRect(1*75, 1*75, 75, 75));
    sprite_enemy->setScale(0.75,0.75);
    // Lo dispongo en el centro de la pantalla
    sprite_enemy->setPosition(size);

    bool izquierda = true;

    //debe ser la misma coordenada X en la que se genera el enemigo
    posInicial = size.x;
}


Enemy::~Enemy() {
    delete Tenemy;
    Tenemy = NULL;
    delete sprite_enemy;
    sprite_enemy = NULL;
    delete bala;
    bala = NULL;
}

void Enemy::mover(int speed){

    sprite_enemy->move(speed, 0);

    if(getX() == posInicial-40)
        izquierda = false;
    else if(getX()== posInicial +40)
        izquierda = true;
}

Bullet Enemy::getBala(){
    return *bala;
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

void Enemy::setPos(Vector2f newPos){
        sprite_enemy->setPosition(newPos);
}

void Enemy::resetBala(){
    disparado = false;
}

void Enemy::dispara(){
    if(!disparado)
    {
        bala->setPos(sprite_enemy->getPosition());
        disparado = true;
    }
}

void Enemy::checkColl(Bullet bullet){

        sf::FloatRect posicion(bullet.getPositionSprite(),{32,32});

        if(sprite_enemy->getGlobalBounds().intersects(posicion)){
            std::cout << "Colisionnnnnnnnnnnnnnnnnnnnnnnn" << std::endl;
            vida = vida - bullet.getDmg();
            //sprite_enemy->setPosition(sf::Vector2f(423442, 4234423));
        }
}

void Enemy::draw(RenderWindow &window){

    if(vida > 0)
        window.draw(*sprite_enemy);
        if(izquierda)
            mover(-1);
        else if(!izquierda)
            mover(1);

    if(disparado && vida > 0){
        bala->draw(window);
        bala->fire(-4);
    }
}
