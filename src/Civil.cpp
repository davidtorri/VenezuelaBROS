#include <iostream>
#include <SFML/Graphics.hpp>
#include "Civil.h"

#define kVida 10

Civil::Civil(Vector2f size)
{
    vida = kVida;

    Tcivil = new Texture();

    Tcivil->loadFromFile("resources/civil-min.png");
    sprite_civil= new Sprite(*Tcivil);

    //Le pongo el centroide donde corresponde
    sprite_civil->setOrigin(75/2,75/2);
    //Cojo el sprite que me interesa por defecto del sheet
    sprite_civil->setTextureRect(IntRect(0*132, 3*120, 132, 120));
    sprite_civil->setScale(0.3,0.3);
    // Lo dispongo en el centro de la pantalla
    sprite_civil->setPosition(size);
}

Civil::~Civil()
{
    delete[] sprite_civil;
}

void Civil::draw(RenderWindow &window){

    window.draw(*sprite_civil);
}
