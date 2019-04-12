#ifndef CIVIL_H
#define CIVIL_H

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Civil
{
    public:
        Civil(Vector2f size);
         ~Civil();

        void draw(RenderWindow &window);

        int getVida();
    private:
        Texture *Tcivil=NULL;
        Sprite *sprite_civil;

        int vida;
};

#endif // CIVIL_H
