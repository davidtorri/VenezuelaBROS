#include <iostream>
#include <SFML/Graphics.hpp>
#include "Maduro.h"

#define kVida 300

Maduro::Maduro(Vector2f size) {

    vida = kVida;

    disparado = false;

    Tmaduro= new Texture();

    Activado = false;

    Tmaduro->loadFromFile("resources/maduro1.png");
    sprite_maduro = new Sprite(*Tmaduro);

    bala = new Bullet(Vector2f(50,50),1);


    //Le pongo el centroide donde corresponde
    sprite_maduro->setOrigin(512/2,512/2);
    //Cojo el sprite que me interesa por defecto del sheet
    sprite_maduro->setTextureRect(IntRect(45, 50, 512, 512));
    sprite_maduro->setScale(0.2,0.2);
    // Lo dispongo en el centro de la pantalla
    sprite_maduro->setPosition(size);

    bool izquierda = true;

    //int Spritevelocidad = 0;
    for(int i = 0; i < 6; i ++){
        SpriteArray[i] = IntRect(45, 50, 512, 512);
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

    //mientras no este activado no se movera, seactivara cuando ve al player a cierta distancia
    if(!Activado)
    {
        sprite_maduro->move(0,0);
    }
    else
    {

        if(posXTrump < getX())
        {
            sprite_maduro->move(speed,0);
        }
        else if(posXTrump > getX())
        {
            sprite_maduro->move(-speed,0);
        }
    }
}

//activamos el bossfinal si esta cerca del player o si el palyer ha pasado de largo
bool Maduro::activado(Player &trump)
{
    if(!Activado)
    {
        int posX = trump.getX();
        int posY = trump.getY();

        if(((getX()-posX) < 200) || posX > getX())
        {
            Activado = true;
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return true;
    }
}

void Maduro::expropiese(Player &trump)
{
    posXTrump = trump.getX();
    posYTrump = trump.getY();

    dispara();

    if(cd.getElapsedTime().asSeconds() > 1)
    {
        resetBala();
        cd.restart();
        Tmaduro->loadFromFile("resources/maduro2.png");
    }
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
        //Tmaduro->loadFromFile("resources/maduro2.png");
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
            sprite_maduro->setScale(-0.2,0.2);
             if(tmovi.getElapsedTime().asSeconds()>0.1){
                Spritevelocidad++;
                tmovi.restart();
              }
        }
        else if(!izquierda){
            mover(1);
            sprite_maduro->setTextureRect(SpriteArray[Spritevelocidad%6]);
            sprite_maduro->setScale(0.2,0.2);
            if(tmovi.getElapsedTime().asSeconds()>0.1){
                Spritevelocidad++;
                tmovi.restart();
              }
        }

    if(disparado && vida > 0){


        if(posXTrump < getX())
        {
             bala->fire(-4);
        }
        else if(posXTrump > getX())
        {
             bala->fire(4);
        }
        bala->draw(window);
    }
}
