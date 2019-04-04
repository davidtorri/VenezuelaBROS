
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"

Player::Player(sf::Vector2f size) {
  //  sprite_player->setSize(size);
    //sprite_player->setFillColor(sf::Color::Green);

    muroPuesto = false;

    Tplayer = new sf::Texture();

    Tmuro = new sf::Texture();

    Tplayer->loadFromFile("resources/sprites.png");
    sprite_player= new sf::Sprite(*Tplayer);

    Tmuro->loadFromFile("resources/PixelAtlas.png");
    sprite_muro = new sf::Sprite(*Tmuro);




    //Le pongo el centroide donde corresponde
    sprite_player->setOrigin(75/2,75/2);
    sprite_muro->setOrigin(75/2,75/2);
    //Cojo el sprite que me interesa por defecto del sheet
    sprite_player->setTextureRect(sf::IntRect(0*75, 0*75, 75, 75));
    sprite_player->setScale(0.5,0.5);

    sprite_muro->setTextureRect(sf::IntRect(0*75,0*75,75,75));
    sprite_muro->setScale(0.25,0.75);
    // Lo dispongo en el centro de la pantalla
    sprite_player->setPosition(323, 146);
}


Player::~Player() {
    delete[] sprite_player;
    delete[] sprite_muro;
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

 void Player::OTAN(){

 }

 void Player::Muro(bool derecha){

    if(!muroPuesto){
        if(derecha){
            sprite_muro->setPosition(sprite_player->getPosition().x+50,sprite_player->getPosition().y);
        }
        else{
            sprite_muro->setPosition(sprite_player->getPosition().x-50,sprite_player->getPosition().y);
        }
        muroPuesto = true;
    }

 }

 void Player::ReseteaMuro(){
    if(muroPuesto)
        muroPuesto = false;
 }
 void Player::draw(sf::RenderWindow& window){
     window.draw(*sprite_player);

     if(muroPuesto)
        window.draw(*sprite_muro);
 }
