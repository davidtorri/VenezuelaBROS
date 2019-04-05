#include "Juego.h"

#define kVel 7




Juego* Juego::unica_instancia = 0;

Juego::Juego(){

}

Juego::~Juego()
{

}
void Juego::cargarCamara(){

    view1.reset(sf::FloatRect(200.f, 200.f, 300.f, 200.f));


    view2.setCenter(sf::Vector2f(350.f, 120.f));
    view2.setSize(sf::Vector2f(600.f, 300.f));

  //camara = new Camara();
}

void Juego::cargarEnemy(){
	enemy = new Enemy(sf::Vector2f(50,50));
	enemy->setPos(sf::Vector2f(400, 146));
}
void Juego::cargarPlayer(){
	player = new Player(sf::Vector2f(50,50));
}
void Juego::cargarMapa(){
	map1 = new Tilemap("resources/mapaunacapa.tmx");
   // map1->load("resources/mapaunacapa.tmx");
}
void Juego::crearVentana(){
	window.create(sf::VideoMode(800, 480), "Venezuela BROS");
    window.setKeyRepeatEnabled(true);
    cout << "VENTANA" << endl;
}
void Juego::bucleJuego(){

    sf::Clock cd;

	std::vector<Bullet> bulletVec;
	std::vector<Bullet> bulletVecEnemy;
    bool isFiring=false;
    bool derecha = true;

	while (window.isOpen())
    {
    	cout << "PlayerX"<< player->getX() << endl;
    	cout << "PlayerY"<< player->getY() << endl;
    	cout << "Player Vida"<<player->getVida() <<endl;
    	cout << "Enemy Vida"<< enemy->getVida() <<endl;
        //window.setView(camara->returnview());
        window.setView(view2);

        sf::Event event;

        while (window.pollEvent(event))
        {

            switch(event.type){

                //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    switch(event.key.code){
                        case sf::Keyboard::Escape:
                            window.close();
                            break;
                    }
                    break;
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                player->move(sf::Vector2f(0, -kVel));
            }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                player->move(sf::Vector2f(0, kVel));
            }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                player->move(sf::Vector2f(-kVel, 0));
                if(player->getX() <= left){
                    cout << "Muevo Cam?"<< endl;
                    view2.move(-7.f,0);
                	//camara->mueveCamaraLeft();
                	right -= 7;
                	left -= 7;
            	}
            	if(derecha)
                    derecha = false;
            }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                player->move(sf::Vector2f(kVel, 0));

                if(player->getX() >= right){
                view2.move(+7.f,0);
                //camara->mueveCamaraRight();
                left += 7;
                right += 7;
            	}
            	if(!derecha)
                    derecha = true;
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                isFiring = true;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
                player->Muro(derecha);
                cd.restart();
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
                player->OTAN();
            }
        }


        if(cd.getElapsedTime().asSeconds()>3){
            player->ReseteaMuro();
        }


        window.clear();

        //window.draw(backgroundSprite);
        map1->draw(window);

        if(isFiring == true){
            Bullet newBullet(sf::Vector2f(50, 5));
            newBullet.setPos(sf::Vector2f(player->getX(), player->getY()));
            bulletVec.push_back(newBullet);
            isFiring = false;

            Bullet newBullet2(sf::Vector2f(5,5));
            newBullet2.setPos(sf::Vector2f(enemy->getX(), enemy->getY()));
            bulletVecEnemy.push_back(newBullet2);
        }

        if(enemy->getVida() > 0){
            for(int i = 0; i < bulletVec.size(); i++){
                bulletVec[i].draw(window);
                bulletVec[i].fire(10);
                enemy->checkColl(bulletVec[i]);
            }
        }

        if(player->getVida() > 0){
            for(int i = 0;i < bulletVecEnemy.size(); i++){
                bulletVecEnemy[i].draw(window);
                bulletVecEnemy[i].fire(-5);
                player->checkColl(bulletVecEnemy[i]);
            }
        }


        player->draw(window);
        enemy->draw(window);

        window.display();
    }
}
