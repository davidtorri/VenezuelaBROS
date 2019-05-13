#include <iostream>
#include <SFML/Graphics.hpp>
#include "Maduro.h"

#define kVida 3000

Maduro::Maduro(Vector2f size) {

    vida = kVida;

    disparado = false;

    Tmaduro= new Texture();

    Tmaduro->loadFromFile("resources/soldier.png");
    sprite_maduro = new Sprite(*Tmaduro);

    bala = new Bullet(Vector2f(50,50),1);


    //Le pongo el centroide donde corresponde
    sprite_maduro->setOrigin(75/2,75/2);
    //Cojo el sprite que me interesa por defecto del sheet
    sprite_maduro->setTextureRect(IntRect(1*45, 3*50, 45, 50));
    sprite_maduro->setScale(0.75,0.75);
    // Lo dispongo en el centro de la pantalla
    sprite_maduro->setPosition(size);

    bool izquierda = true;

    int Spritevelocidad = 0;
    for(int i = 0; i < 6; i ++){
        SpriteArray[i] = IntRect(i*45, 3*50, 45, 50);
    }

    //debe ser la misma coordenada X en la que se genera el enemigo
    posInicial = size.x;
}


Maduro::~Maduro() {
    /*delete sprite_enemy;
    sprite_enemy = NULL;
    delete Tenemy;
    Tenemy = NULL;
    delete bala;
    bala = NULL;*/
}

void Maduro::mover(int speed){

    sprite_maduro->move(speed, 0);

    if(getX() == posInicial-40)
        izquierda = false;
    else if(getX()== posInicial +40)
        izquierda = true;
}

Bullet Maduro::getBala(){
    return *bala;
}

int Maduro::getVida(){
    return vida;
}

int Maduro::getX(){
    return sprite_maduro->getPosition().x;
}

int Maduro::getY(){
    return sprite_maduro->getPosition().y;
}

void Maduro::setPos(Vector2f newPos){
        sprite_maduro->setPosition(newPos);
}

void Maduro::resetBala(){
    disparado = false;
}

void Maduro::dispara(){
    if(!disparado)
    {
        int posXEnemigo = getX();
        int posYEnemigo = getY()-15;
        bala->setPos(sf::Vector2f(posXEnemigo,posYEnemigo));
        disparado = true;
    }
}

void Maduro::checkColl(Bullet bullet){

        sf::FloatRect posicion(bullet.getPositionSprite(),{32,32});

        if(sprite_maduro->getGlobalBounds().intersects(posicion)){
            std::cout << "Colisionnnnnnnnnnnnnnnnnnnnnnnn" << std::endl;
            vida = vida - bullet.getDmg();
            //sprite_enemy->setPosition(sf::Vector2f(423442, 4234423));
        }
}

void Maduro::draw(RenderWindow &window){
    if(vida > 0)
        window.draw(*sprite_maduro);

        if(Spritevelocidad < 1){
            Spritevelocidad = 0;
        }
        if(izquierda){
            mover(-1);
            sprite_maduro->setTextureRect(SpriteArray[Spritevelocidad%6]);
            sprite_maduro->setScale(-0.7,0.7);
             if(tmovi.getElapsedTime().asSeconds()>0.1){
                Spritevelocidad++;
                tmovi.restart();
              }
        }
        else if(!izquierda){
            mover(1);
            sprite_maduro->setTextureRect(SpriteArray[Spritevelocidad%6]);
            sprite_maduro->setScale(0.7,0.7);
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
