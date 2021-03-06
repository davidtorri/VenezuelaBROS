
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"

#define UPDATE_TIME 1.0f/60.0f
#define RENDER_TIME 1.0f/120.0f
#define kVel 200*UPDATE_TIME

#define kVida 11100

Player::Player(Vector2f size) {
  //  sprite_player->setSize(size);
    //sprite_player->setFillColor(sf::Color::Green);

    muroPuesto = false;
    //actualmente esta a TRUE simplemente para probar el funcionamiento pero debera estas a false
    otandisponible = false;
    llamada = false;
    disparado = false;
    petroleo = 0;
    velocidad = 0;
    vida = kVida;
    velocidad = 0;
    Tplayer = new Texture();

    Tmuro = new Texture();
    Totan = new sf::Texture();

    Tbomba = new sf::Texture();

    Tplayer->loadFromFile("resources/trump.png");
    sprite_player= new sf::Sprite(*Tplayer);

    Tmuro->loadFromFile("resources/muro.jpg");
    sprite_muro = new sf::Sprite(*Tmuro);

    Totan->loadFromFile("resources/plane.png");
    sprite_otan = new sf::Sprite(*Totan);

    Tbomba->loadFromFile("resources/bomb.png");
    sprite_bomba = new sf::Sprite(*Tbomba);
    bala = new Bullet(sf::Vector2f(50,50),0);


    //Le pongo el centroide donde corresponde
    sprite_player->setOrigin(75/2,75/2);
    sprite_muro->setOrigin(75/2,75/2);
    sprite_otan->setOrigin(75/2,75/2);
    sprite_bomba->setOrigin(75/2,75/2);

    //Cojo el sprite que me interesa por defecto del sheet
    sprite_player->setTextureRect(sf::IntRect(0*75, 0*75, 75, 75));
    sprite_player->setScale(0.55,0.55);

    sprite_muro->setTextureRect(sf::IntRect(0*75,0*75,75,75));
    sprite_muro->setScale(0.25,0.75);

    sprite_otan->setTextureRect(sf::IntRect(0*75, 0*75, 75, 75));
    sprite_otan->setScale(1.5,1.5);

    sprite_bomba->setTextureRect(sf::IntRect(0*75, 0*75, 75, 75));
    sprite_bomba->setScale(1,1);

    // Lo dispongo en el centro de la pantalla
    sprite_player->setPosition(323, 146);
    sprite_otan->setPosition(sf::Vector2f(sprite_player->getPosition().x-100,0));
    sprite_bomba->setPosition(sprite_otan->getPosition().x,sprite_otan->getPosition().y+40);

    //Declaramos las posiciones del player
     pos_anterior = sf::Vector2f(323,146);
     pos_nueva = sf::Vector2f(323,146);
     //Declaramos las posiciones del ataque de la otan

     /*
     pos_anteriorOTAN = sf::Vector2f(-100,0);
     pos_nuevaOTAN = sf::Vector2f(-100,0);
     */

     pos_anteriorOTAN = sf::Vector2f(sprite_otan->getPosition().x,sprite_otan->getPosition().y+40);
     pos_nuevaOTAN = sf::Vector2f(sprite_otan->getPosition().x,sprite_otan->getPosition().y+40);

     pos_anteriorBOMBA  = sf::Vector2f(sprite_otan->getPosition().x,sprite_otan->getPosition().y+40);
     pos_nuevaBOMBA = sf::Vector2f(sprite_otan->getPosition().x,sprite_otan->getPosition().y+40);



    sprite_player->setPosition(size);

    //Declaramos las posiciones
     pos_anterior = sf::Vector2f(size);
     pos_nueva = sf::Vector2f(size);

    //Construit Sprites
     SpriteDefault = IntRect(0, 0, 100, 100);

     for(int i = 0; i < 5; i ++){
        SpriteRight[i] = IntRect(i*100, 1*100, 100, 100);
        SpriteLeft[i] = IntRect(i*100, 3*100, 100, 100);
    }
}

Player::~Player() {
    /*delete sprite_player;
    sprite_player = NULL;
    delete sprite_muro;
    sprite_muro = NULL;
    delete sprite_otan;
    sprite_otan = NULL;
    delete sprite_bomba;
    sprite_bomba = NULL;
    delete bala;
    bala = NULL;*/
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

 Bullet Player::getBala(){
    return *bala;
 }

 bool Player::getBalaActivada(){
    if(disparado == true)
        return true;
    else
        return false;
}

void Player::setVida(int i){
    vida = vida - i;
}


void Player::Ataque(){
    if(atacando==false){
        atacando=true;
        tiempoataque.restart();
    }
}

bool Player::getAtaque(){
    if(tiempoataque.getElapsedTime().asSeconds()>0.5){
    return false;
    }
    else return true;
}

void Player::CalcularSprite(){

    if(tiempoataque.getElapsedTime().asSeconds()<0.5){
    sprite_player->setTextureRect(IntRect(2*100, 2*100, 100, 100));
    }
    else{
         if (pos_anterior.x > pos_nueva.x ){
              sprite_player->setTextureRect(SpriteLeft[velocidad%5]);
              if(tmovimiento.getElapsedTime().asSeconds()>0.1){
                velocidad++;
                tmovimiento.restart();
              }
         }
         if (pos_anterior.x < pos_nueva.x ){
              sprite_player->setTextureRect(SpriteRight[velocidad%5]);
              if(tmovimiento.getElapsedTime().asSeconds()>0.1){
                    velocidad++;
                    tmovimiento.restart();
              }
         }
         if (pos_anterior.x == pos_nueva.x ){
          sprite_player->setTextureRect(SpriteDefault);
          velocidad=0;
          tmovimiento.restart();
        }
    }
}

 void Player::move(Vector2f dir){

     pos_anterior = pos_nueva; // La anterior es la que era nueva
     pos_nueva += dir;         // Actualiza la posición nueva
     interpolando = true;      // Estamos interpolando

     CalcularSprite();
}


//ademas este metodo se encargará de comprobar que cuadno salga por pantalla el avion ya no exista
 void Player::moveOtan(Vector2f dir){
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

    pos_anteriorOTAN = pos_nuevaOTAN; // La anterior es la que era nueva
    pos_nuevaOTAN += sf::Vector2f(kVel,0);         // Actualiza la posición nueva
    pos_anteriorBOMBA = pos_nuevaBOMBA; // La anterior es la que era nueva
    pos_nuevaBOMBA += sf::Vector2f(kVel,kVel/2);         // Actualiza la posición nueva


    if(sprite_otan->getPosition().x>=sprite_player->getPosition().x+500){//SI FUNCIONAN LAS BOMBAS HAY QUE METER AQUI CUANDO SE BORRAN
        llamada = false;
        pos_anteriorOTAN = sf::Vector2f(sprite_player->getPosition().x-100,0);
        pos_nuevaOTAN = sf::Vector2f(sprite_player->getPosition().x-100,0);

        pos_anteriorBOMBA = sf::Vector2f(sprite_player->getPosition().x-100,0);
        pos_nuevaBOMBA = sf::Vector2f(sprite_player->getPosition().x-100,0);
    }
  /*  if(otandisponible && Totan==NULL)
    {
        llamada = true;
        petroleo = petroleo - 5;
    }
    else if(otandisponible){
        ResetPosOtan();
        ResetPosBombas();
        llamada = true;
        petroleo = petroleo - 5;
    }
*/
 }



void Player::dispara(bool derecha){
    if(!disparado)
    {
        bala->activaBala();
        bala->setPos(sprite_player->getPosition());
        disparado = true;
        disparoDerecha = derecha;
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


void Player::ReseteaAtaque(){
    if(atacando==true)
        atacando = false;
 }


 void Player::ResetPosOtan(){
    sprite_otan->setPosition(-100,0);
    otandisponible = false;
 }

 void Player::ResetPosBombas(){
    for(int q  = 0; q<10;q++){
        int mas = 0;

        bombas[q].setPosition(sprite_otan->getPosition().x+mas,sprite_otan->getPosition().y+40);

        mas = mas +50;
    }
 }

 void Player::CreaSpriteOtan(){
    Totan = new Texture();
    Totan->loadFromFile("resources/plane.png");
    sprite_otan = new Sprite(*Totan);
    sprite_otan->setOrigin(75/2,75/2);
    sprite_otan->setTextureRect(IntRect(0*75, 0*75, 75, 75));
    sprite_otan->setScale(1.5,1.5);
    sprite_otan->setPosition(-100,0);
 }

 void Player::CreaSpriteBomba(){
    Tbomba = new Texture();
    Tbomba->loadFromFile("resources/bomb.png");
    sprite_bomba = new Sprite(*Tbomba);
    sprite_bomba->setOrigin(75/2,75/2);
    sprite_bomba->setTextureRect(IntRect(0*75, 0*75, 75, 75));
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

bool Player::checkColl(Bullet bullet){

        sf::FloatRect posicion(bullet.getPositionSprite(),{32,32});

        if(sprite_player->getGlobalBounds().intersects(posicion)){
            cout << "Colisionnnnnnnnnnnnnnnnnnnnnnnn" << endl;
            cout <<" Vida player:"<<vida<<endl;
            vida = vida - bullet.getDmg();
            return true;
            //sprite_enemy->setPosition(sf::Vector2f(423442, 4234423));
        }
        else{
            return false;
        }
}

bool Player::checkCollPetroleo(Sprite pet){

        sf::FloatRect posicion(sprite_player->getPosition(),{32,32});

        if(pet.getGlobalBounds().intersects(posicion)){
            //vida = vida - bullet.getDmg();
            return true;
            //sprite_enemy->setPosition(sf::Vector2f(423442, 4234423));
        }
        else{
            return false;
        }
}

void Player::resetBala(){
    disparado = false;
    bala->desactiva();

}

 void Player::draw(RenderWindow& window, float porcentaje_interpolacion){

    //Interpolacin de la posición
    if(interpolando)
    {
        Vector2f pos_interpolada = pos_anterior * (1 - porcentaje_interpolacion) + pos_nueva * porcentaje_interpolacion;
        sprite_player->setPosition(pos_interpolada);
        //cout << "Posicion personaje: " << pos_interpolada.x << "-"<< pos_interpolada.y << " con tiempo: " << porcentaje_interpolacion << endl;
        sf::Vector2f pos_interpolada_otan = pos_anteriorOTAN * (1 - porcentaje_interpolacion) + pos_nuevaOTAN * porcentaje_interpolacion;
        sprite_otan->setPosition(pos_interpolada_otan);

        sf::Vector2f pos_interpolada_bomba = pos_anteriorBOMBA* (1 - porcentaje_interpolacion) + pos_nuevaBOMBA * porcentaje_interpolacion;
        sprite_bomba->setPosition(pos_interpolada_bomba);
    }

    //Dibujado del player
    window.draw(*sprite_player);

     if(muroPuesto)
        window.draw(*sprite_muro);

    if(disparado){
        bala->draw(window);
        if(disparoDerecha)
            bala->fire(7);
        else
            bala->fire(-7);
    }

     if(llamada) {
        window.draw(*sprite_otan);
        window.draw(*sprite_bomba);
     }

 }
 bool Player::getLlamada(){
    return llamada;
 }

  void Player::setLlamada(bool b){
    llamada=b;
 }
