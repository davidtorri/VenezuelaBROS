#ifndef CIVIL_H
#define CIVIL_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Civil
{
    public:
        Civil(sf::Vector2f size);
         ~Civil();

        void draw(sf::RenderWindow &window);

        int getVida();
    private:
        sf::Texture *Tcivil=NULL;
        sf::Sprite *sprite_civil;

        int vida;
};

#endif // CIVIL_H
