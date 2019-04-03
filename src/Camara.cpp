#include "Camara.h"



Camara::Camara(){

	 view1.reset(sf::FloatRect(200.f, 200.f, 300.f, 200.f));

    
    view2.setCenter(sf::Vector2f(350.f, 120.f));
    view2.setSize(sf::Vector2f(600.f, 300.f));

}

Camara::~Camara(){

}

sf::View Camara::returnview(){
return view2;
}

void Camara::mueveCamaraRight(){
	returnview().move(+7.f,0);
}
void Camara::mueveCamaraLeft(){
	returnview().move(-7.f,0);
}