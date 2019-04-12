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

    view1.reset(FloatRect(200.f, 200.f, 300.f, 200.f));
    view2.setCenter(Vector2f(350.f, 120.f));
    view2.setSize(Vector2f(600.f, 300.f));

  //camara = new Camara();
}

void Juego::cargarEnemy(){

    enemy = new Enemy(Vector2f(400,133));

    enemy2 = new Enemy(Vector2f(556,56));

}

void Juego::cargarCivil(){
    civil = new Civil(Vector2f(50,160));
}

void Juego::cargarPlayer(){
	player = new Player(Vector2f(93, 133));
}

void Juego::cargarMapa(){
	map1 = new Tilemap("resources/mapaunacapa22.tmx");
   // map1->load("resources/mapaunacapa.tmx");
}

void Juego::crearVentana(){
	window.create(VideoMode(800, 480), "This is America v.1.0");
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
        tiempo_acumulado_update = min(1.f, update_time.getElapsedTime().asSeconds()/UPDATE_TIME);

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

    if(enemy!=NULL)
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

            vel = Vector2f(horiz,vertic);

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
        if(enemy != NULL)
            enemy->resetBala();
        if(enemy2 != NULL)
            enemy2->resetBala();
        cd3.restart();
    }

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

    if(enemy!=NULL && enemy->getVida() <= 0){
        delete enemy;
        enemy = NULL;
    }

    if(enemy2!=NULL && enemy2->getVida() <= 0){
        delete enemy2;
        enemy2 = NULL;
    }
}


void Juego::Render(float tiempo_fraccion)
{

    window.clear();

    //window.draw(backgroundSprite);
    map1->draw(window);

    player->draw(window, tiempo_fraccion);

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
	Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
			case Event::KeyPressed:
				handlePlayerInput(event.key.code, true);
				break;

			case Event::KeyReleased:
				handlePlayerInput(event.key.code, false);
				break;

			case Event::Closed:
				window.close();
				break;
		}
	}
}

// Realiza las operaciones correspondientes a cada Evento
void Juego::handlePlayerInput(Keyboard::Key key, bool isPressed)
{
	if (key == Keyboard::Up) {           //Traslaciones
		isMovingUp = isPressed;
    }
	else if (key == Keyboard::Down){
		//isMovingDown = isPressed;
    }
	else if (key == Keyboard::Left){
        derecha=false;
		isMovingLeft = isPressed;
		if(player->getX() <= left){
                    view2.move(-kVel,0);
                    right -= kVel;
                    left -= kVel;
        }
    }
	else if (key == Keyboard::Right){
        derecha=true;
		isMovingRight = isPressed;
		if(player->getX() >= right){
                        view2.move(kVel,0);
                        left += kVel;
                        right += kVel;
        }
    }
    else if (key == Keyboard::R){
     player->OTAN();
    }
    else if (key == Keyboard::Space){
    isFiring=true;
    cd2.restart();
    }
    else if (key == Keyboard::Q){
     player->Muro(derecha);
     cd.restart();
    }

	else if (key == Keyboard::X && isPressed){


	}
}

