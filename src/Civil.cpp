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
    sprite_civil->setTextureRect(IntRect(0*132, 0*120, 132, 120));

    sprite_civil->setScale(0.3,0.3);
    // Lo dispongo en el centro de la pantalla
    sprite_civil->setPosition(size);

     bool izquierda = true;

    int SpritevelocidadCivil = 0;
    for(int i = 0; i < 5; i ++){
        SpriteArrayCivil[i] = IntRect(i*132, 2*120, 132, 120);
    }

    posInicial=size.x;
}

Civil::~Civil()
{
    /*delete sprite_civil;
    sprite_civil = NULL;*/
}

void Civil::moverCivil(int speed){

    sprite_civil->move(speed, 0);

    if(getX() == posInicial-40)
        izquierda = false;
    /*else if(getX()== posInicial +40)
        izquierda = true;*/
}

void Civil::setVida(int i){
    vida = vida - i;
}


int Civil::getX(){
    return sprite_civil->getPosition().x;
}

int Civil::getY(){
    return sprite_civil->getPosition().y;
}


void Civil::setPos(Vector2f newPos){
        sprite_civil->setPosition(newPos);
}

int Civil::getVida(){
    return vida;
}

bool Civil::checkCollCivil(Bullet bullet){

        sf::FloatRect posicion(bullet.getPositionSprite(),{32,32});

        if(sprite_civil->getGlobalBounds().intersects(posicion)){
            cout << "Colisionnnnnnnnnnnnnnnnnnnnnnnn" << endl;
            cout << "Vida civil" << vida << endl;
            //vida = vida - bullet.getDmg();
            return true;
        }
        else{
            return false;
        }
}


void Civil::draw(RenderWindow &window){
    if(vida > 0){
    window.draw(*sprite_civil);
    /*
    if(izquierda)
    moverCivil(-1);

    else if(!izquierda)
    moverCivil(1);
    }
    */

        if(SpritevelocidadCivil < 1){
            SpritevelocidadCivil = 0;
        }
        if(izquierda){
            moverCivil(-1);
            sprite_civil->setTextureRect(SpriteArrayCivil[SpritevelocidadCivil%4]);
            sprite_civil->setScale(-0.3,0.3);
            if(tmovi.getElapsedTime().asSeconds()>0.1){
                SpritevelocidadCivil++;
                tmovi.restart();
            }
        }
        else if(!izquierda){
            moverCivil(1);
            sprite_civil->setTextureRect(SpriteArrayCivil[SpritevelocidadCivil%4]);
            sprite_civil->setScale(0.3,0.3);
            if(tmovi.getElapsedTime().asSeconds()>0.1){
                SpritevelocidadCivil++;
                tmovi.restart();
            }
        }
    }
    else{
        //disponemos el sprite fuera de pantalla para que no nos moleste,
        //esto deberia hacerlo el delete borrando el sprite directamente pero no lo contemplamos
        sprite_civil->setPosition(0,0);
    }

}
