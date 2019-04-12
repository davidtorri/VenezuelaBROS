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
    //sprite_enemy->setTextureRect(sf::IntRect(0*154, 0*120, 154, 120));
    sprite_enemy->setTextureRect(sf::IntRect(0*45, 1*50, 45, 50));
    sprite_enemy->setScale(0.7,0.7);
    // Lo dispongo en el centro de la pantalla
    sprite_enemy->setPosition(400, 200);

    bool izquierda = true;

    //debe ser la misma coordenada X en la que se genera el enemigo
    posInicial = 400;

     //Construit Sprites
     SpriteDefault = sf::IntRect(0, 0, 154, 100);

   //  for(int i = 0; i < 5; i ++){
   //     SpriteRight[i] = sf::IntRect(i*134, 1*124, 134, 124);
   //     SpriteLeft[i] = sf::IntRect(i*134, 3*124, 134, 124);
  //  }
    int velocidadSprite = 0;
     for(int i = 0; i < 8; i ++){
        SpriteRight[i] = sf::IntRect(i*45, 3*50, 45, 50);
        SpriteLeft[i] = sf::IntRect(i*45, 1*50, 45, 50);
    }

   /*
    sprite_enemy2->setOrigin(130/2,40/2);
    //Cojo el sprite que me interesa por defecto del sheet
    sprite_enemy2->setTextureRect(sf::IntRect(1950, 1580, 95, 40));
    sprite_enemy2->setScale(1,1);
    // Lo dispongo en el centro de la pantalla
    sprite_enemy2->setPosition(500, 300); */
}


Enemy::~Enemy() {
    //esto es el destructor

    delete[] sprite_enemy;
}

void Enemy::mover(int speed){
    //if(getX())
    sprite_enemy->move(speed, 0);

    if(getX() == posInicial-50)
    {
        izquierda = false;
    }
    else if(getX()== posInicial +50)
    {
        izquierda = true;
    }
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
            //sprite_enemy->setPosition(sf::Vector2f(423442, 4234423));

        }
}

void Enemy::draw(sf::RenderWindow &window){
    if(vida > 0)
        window.draw(*sprite_enemy);

        if (velocidadSprite < 0 )
        velocidadSprite = 0;

        velocidadSprite++;

    if(disparado){
     if(izquierda)
        {
        mover(-2);
         sprite_enemy->setTextureRect(SpriteRight[velocidadSprite%6]);
         sprite_enemy->setScale(-0.85,0.85);
         std::cout <<  velocidadSprite << "  " << velocidadSprite %6 << std::endl;
        }
    else if(!izquierda)
        {
        sprite_enemy->setTextureRect(SpriteRight[velocidadSprite%6]);
        sprite_enemy->setScale(0.85,0.85);
        mover(1);
        std::cout << "Velocidad : " <<  velocidadSprite << "  " << velocidadSprite %6<< std::endl;
        }

        bala->draw(window);
        bala->fire(-8);

    }
}
