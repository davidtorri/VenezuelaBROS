
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Enemy.h"

#define kVida 60

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
    sprite_enemy->setTextureRect(IntRect(1*45, 3*50, 45, 50));
    sprite_enemy->setScale(0.75,0.75);
    // Lo dispongo en el centro de la pantalla
    sprite_enemy->setPosition(size);

    bool izquierda = true;

    int Spritevelocidad = 0;
    for(int i = 0; i < 6; i ++){
        SpriteArray[i] = IntRect(i*45, 3*50, 45, 50);
    }

    //debe ser la misma coordenada X en la que se genera el enemigo
    posInicial = size.x;
}


Enemy::~Enemy() {
    /*delete sprite_enemy;
    sprite_enemy = NULL;
    delete Tenemy;
    Tenemy = NULL;
    delete bala;
    bala = NULL;*/
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
    bala->desactiva();
}

void Enemy::dispara(){
    if(!disparado)
    {
        int posXEnemigo = getX();
        int posYEnemigo = getY()-15;
        bala->activaBala();
        bala->setPos(sf::Vector2f(posXEnemigo,posYEnemigo));
        disparado = true;
    }
}

bool Enemy::checkColl(Bullet bullet){

        sf::FloatRect posicion(bullet.getPositionSprite(),{32,32});

        if(sprite_enemy->getGlobalBounds().intersects(posicion)){
            std::cout << "Colisionnnnnnnnnnnnnnnnnnnnnnnn" << std::endl;
            vida = vida - bullet.getDmg();
            cout<<"Vida enemigo: "<<vida<<endl;
            bullet.desactiva();
            return true;
            //sprite_enemy->setPosition(sf::Vector2f(423442, 4234423));
        }
        else
        {
            return false;
        }
}

void Enemy::draw(RenderWindow &window){
    if(vida > 0){
        window.draw(*sprite_enemy);

        if(Spritevelocidad < 1){
            Spritevelocidad = 0;
        }
        if(izquierda){
            mover(-1);
            sprite_enemy->setTextureRect(SpriteArray[Spritevelocidad%6]);
            sprite_enemy->setScale(-0.7,0.7);
             if(tmovi.getElapsedTime().asSeconds()>0.1){
                Spritevelocidad++;
                tmovi.restart();
              }
        }
        else if(!izquierda){
            mover(1);
            sprite_enemy->setTextureRect(SpriteArray[Spritevelocidad%6]);
            sprite_enemy->setScale(0.7,0.7);
            if(tmovi.getElapsedTime().asSeconds()>0.1){
                Spritevelocidad++;
                tmovi.restart();
              }
        }

    if(disparado && vida > 0){
        bala->draw(window);
        bala->fire(-4);
    }
    }
    else
        sprite_enemy->setPosition(-1000,0);
}

