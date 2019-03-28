#include <iostream>
#include <SFML/Graphics.hpp>
#include "Enemy.h"

Enemy::Enemy(sf::Vector2f size) {
    
    Tenemy= new sf::Texture();
    
    Tenemy->loadFromFile("resources/sprites.png");
    sprite_enemy= new sf::Sprite(*Tenemy);
    sprite_enemy2= new sf::Sprite(*Tenemy);
    
    
    //Le pongo el centroide donde corresponde
    sprite_enemy->setOrigin(75/2,75/2);
    //Cojo el sprite que me interesa por defecto del sheet
    sprite_enemy->setTextureRect(sf::IntRect(1*75, 1*75, 75, 75));
    sprite_enemy->setScale(0.5,0.5);
    // Lo dispongo en el centro de la pantalla
    sprite_enemy->setPosition(400, 200); 
    
   /*
    sprite_enemy2->setOrigin(130/2,40/2);
    //Cojo el sprite que me interesa por defecto del sheet
    sprite_enemy2->setTextureRect(sf::IntRect(1950, 1580, 95, 40));
    sprite_enemy2->setScale(1,1);
    // Lo dispongo en el centro de la pantalla
    sprite_enemy2->setPosition(500, 300); */ 
}


Enemy::~Enemy() { 
    //esto es el destructor
    
    delete[] sprite_enemy;
}

void Enemy::setPos(sf::Vector2f newPos){  
        sprite_enemy->setPosition(newPos);
    }

void Enemy::checkColl(Bullet bullet){
        
        if(bullet.getRight() > sprite_enemy->getPosition().x && 
           bullet.getTop() < sprite_enemy->getPosition().y ){
           
           
           sprite_enemy->setPosition(sf::Vector2f(423442, 4234423));
           
        }
    }

void Enemy::draw(sf::RenderWindow &window){
        window.draw(*sprite_enemy);
    }