#include "Juego.h"

using namespace tinyxml2;
using namespace std;



int main()
{
    //cout << "LLEGO1" << endl;
    Juego* juego = Juego::getInstance();
    juego->crearVentana();
    juego->cargarMapa();
    juego->cargarPlayer();
    juego->cargarEnemy();
    juego->cargarCivil();
    juego->cargarPetroleo();
    juego->cargarCamara();
    juego->bucleJuego();

    return 0;
}
