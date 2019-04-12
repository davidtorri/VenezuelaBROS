#include <iostream>
#include <SFML/Graphics.hpp>
#include "Civil.h"

#define kVida 10

Civil::Civil(sf::Vector2f size)
{
    vida = kVida;

    Tcivil = new sf::Texture();

    Tcivil->loadFromFile("resources/soldier.png");
    sprite_civil= new sf::Sprite(*Tcivil);

    //Le pongo el centroide donde corresponde
    sprite_civil->setOrigin(75/2,75/2);
    //Cojo el sprite que me interesa por defecto del sheet
    sprite_civil->setTextureRect(sf::IntRect(0*45, 0*50, 45, 50));
    sprite_civil->setScale(0.7,0.7);
    // Lo dispongo en el centro de la pantalla
    sprite_civil->setPosition(100, 160);
}

Civil::~Civil()
{
    delete[] sprite_civil;
}

void Civil::draw(sf::RenderWindow &window){

    window.draw(*sprite_civil);
}
