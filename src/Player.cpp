
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"

#define kVida 100

Player::Player(sf::Vector2f size) {
  //  sprite_player->setSize(size);
    //sprite_player->setFillColor(sf::Color::Green);

    muroPuesto = false;
    //actualmente esta a TRUE simplemente para probar el funcionamiento pero debera estas a false
    otandisponible = true;
    llamada = false;
    petroleo = 0;
    vida = kVida;

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
    delete[] sprite_otan;
    delete[] sprite_bomba;
}

int Player::getVida(){
    return vida;
}

int Player::getPetroleo(){
    return petroleo;
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

//ademas este metodo se encargará de comprobar que cuadno salga por pantalla el avion ya no exista
 void Player::moveOtan(sf::Vector2f dir){
    sprite_otan->move(dir);
    if(sprite_otan->getPosition().x>=sprite_player->getPosition().x+500){
        llamada = false;
    }
 }

 void Player::moveBomba(){
    //variable auxiliar para actualizar posicion X de cada bomba, asi no se tiraran todas en el mismo lugar
    int actu = -50;

    //Actualizo la posicion X de la bomba con respecto al avio
    //y la Y con respecto a la posicion anterior de la propia bomba
    for(int p  = 0; p<10;p++){
        bombas[p].setPosition(sprite_otan->getPosition().x+actu,bombas[p].getPosition().y+1.5);

        actu = actu+75;
    }
 }

 void Player::OTAN(){
    if(otandisponible && Totan==NULL)
    {
        CreaSpriteOtan();

        CreaSpriteBomba();

        llamada = true;
        petroleo = petroleo - 5;
    }
    else if(otandisponible){
        ResetPosOtan();
        ResetPosBombas();
        llamada = true;
        petroleo = petroleo - 5;
    }

 }

//implementacio no definitiva hay que tener en cuenta cuando y como vamos a llamar a este metodo
 void Player::setPetroleo(){
    petroleo++;

    if(vida < kVida){
        vida = vida + 10;
    }

    if(petroleo>=5)
    {
        otandisponible = true;
    }
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

 void Player::ResetPosOtan(){
    sprite_otan->setPosition(-100,0);
 }

 void Player::ResetPosBombas(){
    for(int q  = 0; q<10;q++){
        int mas = 0;

        bombas[q].setPosition(sprite_otan->getPosition().x+mas,sprite_otan->getPosition().y+40);

        mas = mas +50;
    }
 }

 void Player::CreaSpriteOtan(){
    Totan = new sf::Texture();
    Totan->loadFromFile("resources/plane.png");
    sprite_otan = new sf::Sprite(*Totan);
    sprite_otan->setOrigin(75/2,75/2);
    sprite_otan->setTextureRect(sf::IntRect(0*75, 0*75, 75, 75));
    sprite_otan->setScale(1.5,1.5);
    sprite_otan->setPosition(-100,0);
 }

 void Player::CreaSpriteBomba(){
    Tbomba = new sf::Texture();
    Tbomba->loadFromFile("resources/bomb.png");
    sprite_bomba = new sf::Sprite(*Tbomba);
    sprite_bomba->setOrigin(75/2,75/2);
    sprite_bomba->setTextureRect(sf::IntRect(0*75, 0*75, 75, 75));
    sprite_bomba->setScale(1,1);

    for(int i  = 0; i<10;i++)
        {
            bombas.push_back(*sprite_bomba);
        }

    for(int q  = 0; q<10;q++){
        int mas = 0;

        bombas[q].setPosition(sprite_otan->getPosition().x+mas,sprite_otan->getPosition().y+40);

        mas = mas +50;
    }
 }

 void Player::draw(sf::RenderWindow& window){

     window.draw(*sprite_player);

     if(muroPuesto)
        window.draw(*sprite_muro);

     if(llamada) {
        moveOtan(sf::Vector2f(5, 0));

        window.draw(*sprite_otan);

        moveBomba();

        //dibujo bombas
        for(int w  = 0; w<10;w++){
            window.draw(bombas[w]);
        }
     }

 }
