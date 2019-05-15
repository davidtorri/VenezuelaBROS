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

    //enemy = new Enemy(Vector2f(400,153));
    enemy = new Enemy(Vector2f(0,-1000));

    //enemy2 = new Enemy(Vector2f(556,76));
    enemy2 = new Enemy(Vector2f(0,-1000));


}

void Juego::cargarMaduro(){

    bossFinal = new Maduro(Vector2f(400,123));

}

void Juego::cargarPetroleo(){

        p1 = true;
        p2 = true;
        p3 = true;
        p4 = true;

        Tpetroleo = new Texture();
        Tpetroleo->loadFromFile("resources/petroleo.png");
        sprite_petroleo= new Sprite(*Tpetroleo);
        sprite_petroleo->setOrigin(130/2,40/2);
        sprite_petroleo->setScale(0.04,0.04);
        sprite_petroleo->setPosition(500, 143);

        sprite_petroleo1= new Sprite(*Tpetroleo);
        sprite_petroleo1->setOrigin(130/2,40/2);
        sprite_petroleo1->setScale(0.04,0.04);
        sprite_petroleo1->setPosition(435, 62);

        sprite_petroleo2= new Sprite(*Tpetroleo);
        sprite_petroleo2->setOrigin(130/2,40/2);
        sprite_petroleo2->setScale(0.04,0.04);
        sprite_petroleo2->setPosition(556, 62);

        sprite_petroleo3= new Sprite(*Tpetroleo);
        sprite_petroleo3->setOrigin(130/2,40/2);
        sprite_petroleo3->setScale(0.04,0.04);
        sprite_petroleo3->setPosition(759, 62);


}

void Juego::cargarCivil(){

    civil = new Civil(Vector2f(200,90));
}
void Juego::cargarPlayer(){
	player = new Player(Vector2f(93, 130));
}

void Juego::cargarMapa(){
	//map1 = new Tilemap("resources/mapaunacapa22.tmx");
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


    /*
    cout << "PlayerX"<< player->getX() << endl;
    cout << "PlayerY"<< player->getY() << endl;
    cout << "Player Vida"<<player->getVida() <<endl;
    */
    if(enemy!=NULL)
        //cout << "Enemy Vida"<< enemy->getVida() <<endl;


    //window.setView(camara->returnview());
    window.setView(view2);
    float horiz = 0.f, vertic=0.f;
    if(!firstTime)
        {
            sf::Vector2f vel;
            isMovingDown=true;
            if(player->getAtaque()==false){
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
            }

            if(player->getLlamada()==true){
             player->OTAN();
            }


            vel = Vector2f(horiz,vertic);

            player->move(vel);
        }


	firstTime=false;

	enemigoDisparaYComprueboColisiones();

    resetHabilidades();

    comprueboMuertes();
}

void Juego::resetHabilidades(){

    if(cd.getElapsedTime().asSeconds()>3){
        player->ReseteaMuro();
    }

    if(cd2.getElapsedTime().asSeconds()>2){
        player->resetBala();
    }

    if(cdE.getElapsedTime().asSeconds()>2){
        player->ReseteaAtaque();
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
}

void Juego::enemigoDisparaYComprueboColisiones(){

    if(enemy!=NULL){
        if(enemy->getX() - player->getX() < 150)
            enemy->dispara();
        if(player->getBalaActivada()){
            if(enemy->checkColl(player->getBala()))
                isFiring = false;
        }
        //if(){
            if(player->checkColl(enemy->getBala())){
                enemy->resetBala();
            }
        //}
    }

    if(enemy2!=NULL){
        if(enemy2->getX() - player->getX() < 150)
            enemy2->dispara();
        if(enemy2->getX() - civil->getX() < 150)
            enemy2->dispara();
        if(player->getBalaActivada()){
            if(enemy2->checkColl(player->getBala()))
                isFiring = false;
        }
        if(player->checkColl(enemy2->getBala()))
            enemy2->resetBala();
    }

    if(civil!=NULL){
        if(player->getBalaActivada())
            if(civil->checkCollCivil(player->getBala()))
                player->setVida(-10);

        if(civil->checkCollCivil(enemy->getBala()))
            civil->setVida(10);

        if(civil->checkCollCivil(enemy2->getBala()))
            civil->setVida(10);
    }

    if(player->checkCollPetroleo(*sprite_petroleo)){
        player->setPetroleo();
        p1 = false;
    }
    if(player->checkCollPetroleo(*sprite_petroleo1)){
        player->setPetroleo();
        p2 = false;
    }
    if(player->checkCollPetroleo(*sprite_petroleo2)){
        player->setPetroleo();
        p3 = false;
    }
    if(player->checkCollPetroleo(*sprite_petroleo3)){
        player->setPetroleo();
        p4 = false;
    }

}

void Juego::comprueboMuertes(){

    /*if(enemy!=NULL && enemy->getVida() <= 0){
        delete enemy;
        enemy = NULL;
    }

    if(enemy2!=NULL && enemy2->getVida() <= 0){
        delete enemy2;
        enemy2 = NULL;
    }

   // if(civil!=NULL && civil->getVida() <= 0){
        //delete civil;
        //civil = NULL;
   // }

    if(player!=NULL && player->getVida() <= 0){
        delete player;
        player = NULL;
    }*/
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
    if(bossFinal!=NULL)
        bossFinal->draw(window);

    if(civil!=NULL)
        civil->draw(window);

    if(p1)
        window.draw(*sprite_petroleo);
    if(p2)
        window.draw(*sprite_petroleo1);
    if(p3)
        window.draw(*sprite_petroleo2);
    if(p4)
        window.draw(*sprite_petroleo3);

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
    player->setLlamada(true);
    }
    else if (key == Keyboard::Space){
    isFiring=true;
    cd2.restart();
    }
    else if (key == Keyboard::Q){
     player->Muro(derecha);
     cd.restart();
    }

     else if (key == Keyboard::E){
     player->Ataque();
     cdE.restart();
    }

	else if (key == Keyboard::X && isPressed){


	}
}

