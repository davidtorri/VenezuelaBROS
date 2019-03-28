#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
    

class Player{
public:
    Player(sf::Vector2f size);
    
    ~Player();
    
    void move(sf::Vector2f dir);

    int getX();
    
    int getY();
    
    void draw(sf::RenderWindow &window);
private:
   // sf::RectangleShape player;
    sf::Texture *Tplayer=NULL;
    sf::Sprite *sprite_player;
    
    

};

#endif /* PLAYER_HPP */