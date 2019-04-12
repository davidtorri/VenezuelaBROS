#include "Juego.h"

#define UPDATE_TIME 1.0f/60.0f
#define RENDER_TIME 1.0f/120.0f
#define kVel 200*UPDATE_TIME

Juego* Juego::unica_instancia = 0;

Juego::Juego(){
isMovingDown=false;
isMovingUp=false;
isMovingRight=false;
isMovingLeft=false;

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

    enemy = new Enemy(sf::Vector2f(400,133));

    enemy2 = new Enemy(sf::Vector2f(556,56));

}

void Juego::cargarCivil(){
    civil = new Civil(sf::Vector2f(50,160));
}

void Juego::cargarPlayer(){
	player = new Player(sf::Vector2f(93, 133));
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

       /* double jesustontito = update_time.getElapsedTime().asSeconds();

        jesustonto = jesustontito;*/

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



    cout << "PlayerX"<< player->getX() << endl;
    cout << "PlayerY"<< player->getY() << endl;
    cout << "Player Vida"<<player->getVida() <<endl;
    cout << "Enemy Vida"<< enemy->getVida() <<endl;


    //window.setView(camara->returnview());
    window.setView(view2);
    float horiz = 0.f, vertic=0.f;
    if(!firstTime)
        {
            sf::Vector2f vel;
            isMovingDown=true;
            if(isMovingDown){
                //vertic = kVel;
                int gid_pos = map1->getGid(1, player->getY()+(kVel+25), player->getX());

                if(gid_pos!=14 && gid_pos!=15){
                    vertic = kVel;
                }
            }
            if(isMovingUp){
                int gid_pos = map1->getGid(1, player->getY()+(-kVel+25), player->getX());

                if(gid_pos!=14 && gid_pos!=15){
                    vertic = -kVel;
                }
            }
                //vertic = -kVel;
            if(isMovingLeft){
                int gid_pos = map1->getGid(1, player->getY(), player->getX()+(-kVel-18));

                if(gid_pos!=14 && gid_pos!=15){
                    horiz = -kVel;
                }
            }

            if(isMovingRight){
                int gid_pos = map1->getGid(1, player->getY(), player->getX()+(+kVel+10));

                if(gid_pos!=14 && gid_pos!=15){
                    horiz = kVel;
                }
            }

            vel = sf::Vector2f(horiz,vertic);

            player->move(vel);
        }


	firstTime=false;


    if(cd.getElapsedTime().asSeconds()>3){
        player->ReseteaMuro();
    }

    if(cd2.getElapsedTime().asSeconds()>2){
        player->resetBala();
    }

    if(cd3.getElapsedTime().asSeconds()>3){
        enemy->resetBala();
        enemy2->resetBala();
        cd3.restart();
    }

    if(enemy2->getX() - player->getX() < 150)
        enemy2->dispara();

    if(isFiring == true){
        player->dispara(derecha);
        isFiring = false;
    }

    if(enemy!=NULL){
        if(enemy->getX() - player->getX() < 150)
            enemy->dispara();
        if(player->getBalaActivada())
            enemy->checkColl(player->getBala());
    }

    if(enemy2!=NULL){
        if(enemy2->getX() - player->getX() < 150)
            enemy2->dispara();
        if(player->getBalaActivada())
            enemy2->checkColl(player->getBala());
    }
}


void Juego::Render(float tiempo_fraccion)
{

    window.clear();

    //window.draw(backgroundSprite);
    map1->draw(window);

    player->draw(window, tiempo_fraccion);
    player->checkColl(enemy->getBala());
    player->checkColl(enemy2->getBala());

    if(enemy!=NULL)
        enemy->draw(window);

    if(enemy2!=NULL)
        enemy2->draw(window);

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
		//isMovingDown = isPressed;
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
    cd2.restart();
    }
    else if (key == sf::Keyboard::Q){
     player->Muro(derecha);
     cd.restart();
    }

	else if (key == sf::Keyboard::X && isPressed){


	}
}

