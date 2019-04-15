#ifndef CIVIL_H
#define CIVIL_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Bullet.h"

using namespace std;
using namespace sf;

class Civil
{
    public:
        Civil(Vector2f size);
         ~Civil();

        void draw(RenderWindow &window);

        void moverCivil(int speed);

        int getX();

        int getY();

        void setPos(Vector2f newPos);

        bool checkCollCivil(Bullet bullet);


        int getVida();
    private:
        Texture *Tcivil=NULL;
        Sprite *sprite_civil;

        IntRect SpriteArrayCivil[6];

            int vida;
            bool izquierda;
            int posInicial;
            int SpritevelocidadCivil;

};

#endif // CIVIL_H
