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

		//Creo el Personaje
		Personaje* luchador = mundo->getPersonaje();

		//Creo el Controlador
		KeyboardControl* control_jugador_1 = new KeyboardControl(luchador);

		//Manejador de evento
		SDL_Event e;

		//While Principal
		while( !control_jugador_1->getQuit() ){
			//Eventos
			while( SDL_PollEvent( &e ) != 0 ){
				control_jugador_1->KeyPressed(e);
			}

			mundo->render();

			//Sleep(Microsegundos)
			usleep(50000);

		}

		mundo->~Mundo();
		log("Se cierra y libera el mundo",LOG_DEBUG);
	}

	return 0;
}


