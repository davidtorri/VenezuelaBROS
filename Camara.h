#ifndef CAMARA_H
#define CAMARA_H

#include <iostream>
#include <SFML/Graphics.hpp>
    

class Camara{
public:
    Camara();
    
    ~Camara();

    void mueveCamaraRight();
    void mueveCamaraLeft();

    sf::View returnview();
    sf::View view1;
    sf::View view2;

private:


};

#endif 