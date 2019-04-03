
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"

Player::Player(sf::Vector2f size) {
  //  sprite_player->setSize(size);
    //sprite_player->setFillColor(sf::Color::Green);
    
    Tplayer = new sf::Texture();
    
    Tplayer->loadFromFile("resources/sprites.png");
    sprite_player= new sf::Sprite(*Tplayer);
    
   
    
    //Le pongo el centroide donde corresponde
    sprite_player->setOrigin(75/2,75/2);
    //Cojo el sprite que me interesa por defecto del sheet
    sprite_player->setTextureRect(sf::IntRect(0*75, 0*75, 75, 75));
    sprite_player->setScale(0.5,0.5);
    // Lo dispongo en el centro de la pantalla
    sprite_player->setPosition(323, 146); 
}


Player::~Player() {
    delete[] sprite_player;
}

 int Player::getX(){
     return sprite_player->getPosition().x;
 }
 
 int Player::getY(){
    return sprite_player->getPosition().y;
 }
 
 void Player::move(sf::Vector2f dir){
     sprite_player->move(dir);
 }
 void Player::draw(sf::RenderWindow& window){
     window.draw(*sprite_player);
 }