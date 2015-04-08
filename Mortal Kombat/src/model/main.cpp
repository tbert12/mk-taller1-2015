/*
 * main.cpp
 *
 *  Created on: 26/3/2015
 *      Author: tomi
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> //usleep
#include <vector>
#include "logging.h"
#include "DefaultSettings.h"
#include "Mundo.h"


#include <algorithm>    // std::reverse (Tranfuguiada para que camine para atras)

#include "../view/Ventana.h"
#include "../controller/KeyboardControl.h"
#include "Personaje.h"


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

/*
std::vector<Sprite*> CargaDePrueba(){
	std::vector<Frame*> framesInitial(9);
	std::vector<Frame*> framesCaminar(9);
	int wInitial = 72,wCaminar = 68;
	for (int i=0;i<9;i++){
		framesInitial[i] = new Frame(wInitial*i,0,133,wInitial);
		framesCaminar[i] = new Frame(wCaminar*i,0,133,wCaminar);
	}
	std::vector<Frame*> framesCaminarAtras (framesCaminar);
	std::reverse(framesCaminarAtras.begin(),framesCaminarAtras.end());


	std::string rutaInitial = "data/players/subzero/sprites/initial.png";
	std::string rutaCaminar = "data/players/subzero/sprites/walk.png";
	std::string rutaCaminarAtras = "data/players/subzero/sprites/walk.png";
	Sprite* Initial = new Sprite(rutaInitial,framesInitial,getRenderer());
	Sprite* Caminar = new Sprite(rutaCaminar,framesCaminar,getRenderer());
	Sprite* CaminarAtras = new Sprite(rutaCaminar,framesCaminarAtras,getRenderer());
	std::vector<Sprite*> sprites(3);
	sprites[0] = Initial;
	sprites[1] = Caminar;
	sprites[2] = CaminarAtras;
	return sprites;
}
*/

int main( int argc, char* args[] )
{

	// Marco inicio de un nuevo run en el .log
	prepararLog();

	Mundo* mundo = CrearMundoDefault();

	if(mundo == NULL){
		log( "No se pudo crear el Mundo", LOG_ERROR );
		return 1;
	} else {
		log( "Mundo creado por default", LOG_DEBUG );
		Ventana* ventana = mundo->getVentana();
		//Creo el Personaje
		//Personaje luchador = Personaje("Sub Zero",CargaDePrueba());
		Personaje* luchador = mundo->getPersonaje();

		//std::string rutaFondoAncho = "data/Fondos/largo.png";
		//std::strbackgroundsing rutaFondo2 = "data/Fondos/atras.png";

		//CapaFondo capaFondo = CapaFondo(SCREEN_HEIGHT,SCREEN_WIDTH, 0, 1068, 10,rutaFondoAncho,ventana->getRenderer(),ventana);
		//CapaFondo capaAtras = CapaFondo(SCREEN_HEIGHT,SCREEN_WIDTH, 1, 1068, 10,rutaFondo2,ventana->getRenderer(),ventana);

		//Creo el Controlador
		KeyboardControl* control_jugador_1 = new KeyboardControl(luchador);

		//flag para el Loop Principal
		bool quit = false;

		//Manejador de evento
		SDL_Event e;

		//Current animation frame
		int frame = 0;

		//While Principal
		while( !quit ){
			//Eventos
			while( SDL_PollEvent( &e ) != 0 ){
				//Usuario presiona [X]
				if( e.type == SDL_QUIT ){
					quit = true;
				}
				control_jugador_1->KeyPressed(e);
			}

			printf("%i\n",frame);

			ventana->Refresh(luchador->getSpriteActual());

			//FrameGuia
			++frame;

			//Sleep(Microsegundos)
			usleep(120000);
		}
		//Free resources and close SDL
		ventana->close_window();
	}

	return 0;
}


