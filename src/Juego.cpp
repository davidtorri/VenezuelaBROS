#include "Juego.h"

#define kVel 4
#define UPDATE_TIME 1.0f/60.0f
#define RENDER_TIME 1.0f/120.0f

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

void Juego::cargarCivil(){
    civil = new Civil(sf::Vector2f(50,50));
}

void Juego::cargarPlayer(){
	player = new Player(sf::Vector2f(50,50));
}

void Juego::cargarMapa(){
	map1 = new Tilemap("resources/mapaunacapa22.tmx");
   // map1->load("resources/mapaunacapa.tmx");
}

void Juego::crearVentana(){
	window.create(sf::VideoMode(800, 480), "This is America v.1.0");
    window.setKeyRepeatEnabled(true);
    cout << "VENTANA" << endl;
}

void Juego::bucleJuego(){
    // Para el interpolado
    float tiempo_acumulado_update;

	while (window.isOpen())
    {
        //Actualiza las condiciones del juego

        processEvents();

        if(update_time.getElapsedTime().asSeconds() >= UPDATE_TIME)
        {
            Update();
            //Actualizamos el tiempo
            update_time.restart();
            tiempo_acumulado_update = 0;
        }

        // Fracción entre tiempo transcurrido hasta el siguiente update / tiempo
        // que hay entre updates
        tiempo_acumulado_update = std::min(1.f, update_time.getElapsedTime().asSeconds()/UPDATE_TIME);

        //Renderiza todo el juego
        if(render_time.getElapsedTime().asSeconds() >= RENDER_TIME)
        {
            Render(tiempo_acumulado_update);

            //Actualizamos el tiempo
            render_time.restart();
        }
    }
}

void Juego::Update()
{

    //Cancelamos interpolación por si no se mueve el personaje en este update
    player->setInterpolando(false);


    /*
    cout << "PlayerX"<< player->getX() << endl;
    cout << "PlayerY"<< player->getY() << endl;
    cout << "Player Vida"<<player->getVida() <<endl;
    cout << "Enemy Vida"<< enemy->getVida() <<endl;
    */

    //window.setView(camara->returnview());
    window.setView(view2);
    float horiz = 0.f, vertic=0.f;
    if(!firstTime)
        {
            sf::Vector2f vel;
            if(isMovingDown)
                vertic = kVel;
            if(isMovingUp)
                vertic = -kVel;
            if(isMovingLeft)
                horiz = -kVel;
            if(isMovingRight)
                horiz = kVel;

            vel = sf::Vector2f(horiz,vertic);

            player->move(vel);
        }

	firstTime=false;


    if(cd.getElapsedTime().asSeconds()>3){
        player->ReseteaMuro();
    }

    if(isFiring == true){
        Bullet newBullet(sf::Vector2f(50, 5));
        newBullet.setPos(sf::Vector2f(player->getX(), player->getY()));
        bulletVec.push_back(newBullet);
        isFiring = false;

        Bullet newBullet2(sf::Vector2f(5,5));
        newBullet2.setPos(sf::Vector2f(enemy->getX(), enemy->getY()));
        bulletVecEnemy.push_back(newBullet2);
    }
}


void Juego::Render(float tiempo_fraccion)
{

    window.clear();

    //window.draw(backgroundSprite);
    map1->draw(window);

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


    player->draw(window, tiempo_fraccion);
    enemy->draw(window);
    civil->draw(window);

    window.display();
}


/************** EVENTOS ****************/

void Juego::processEvents()   //Captura y procesa eventos
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::KeyPressed:
				handlePlayerInput(event.key.code, true);
				break;

			case sf::Event::KeyReleased:
				handlePlayerInput(event.key.code, false);
				break;

			case sf::Event::Closed:
				window.close();
				break;
		}
	}
}

// Realiza las operaciones correspondientes a cada Evento
void Juego::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::Up) {           //Traslaciones
		isMovingUp = isPressed;
    }
	else if (key == sf::Keyboard::Down){
		isMovingDown = isPressed;
    }
	else if (key == sf::Keyboard::Left){
        derecha=false;
		isMovingLeft = isPressed;
		if(player->getX() <= left){
                    view2.move(-kVel,0);
                    right -= kVel;
                    left -= kVel;
        }
    }
	else if (key == sf::Keyboard::Right){
        derecha=true;
		isMovingRight = isPressed;
		if(player->getX() >= right){
                        view2.move(kVel,0);
                        left += kVel;
                        right += kVel;
        }
    }
    else if (key == sf::Keyboard::R){
     player->OTAN();
    }
    else if (key == sf::Keyboard::Space){
    isFiring=true;
    }
    else if (key == sf::Keyboard::Q){
     player->Muro(derecha);
     cd.restart();
    }

	else if (key == sf::Keyboard::X && isPressed){


	}
}

