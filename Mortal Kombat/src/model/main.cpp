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
#include "ParserJSON.h"

#include <algorithm>    // std::reverse (Tranfuguiada para que camine para atras)

#include "../controller/KeyboardControl.h"
#include "../view/Ventana.h"
#include "Personaje.h"

string ruta_archivo_configuracion = "data/config/Parallax.json";

Mundo* cargarMundo(){
	Mundo* unMundo;
	ParserJSON* parser;
	try {
			parser = new ParserJSON( ruta_archivo_configuracion );
			unMundo = parser->cargarMundo();
			log( "Se creo correctamente el Mundo de la partida.", LOG_DEBUG );
			delete parser;
		} catch ( std::exception &e ) {
			log( "No se pudo crear el Mundo. Se aborta la ejecucion del programa. " + string(e.what()), LOG_ERROR );
			delete parser;
			delete unMundo;
			return NULL;
	}
	return unMundo;
}

void free(Mundo* mundo,KeyboardControl* c1/*,KeyboardControl* c2*/){
	delete mundo;
	delete c1;
	//delete c2;
}

int main( int argc, char* args[] )
{


	// Marco inicio de un nuevo run en el .log
	prepararLog();

	if (argc > 1){
		ruta_archivo_configuracion = args[1];
	}


	Mundo* mundo = cargarMundo();
	if (mundo == NULL) {
		return 1;
	}

	SDL_Event event;

	//Creo los Controladores
	KeyboardControl* control_jugador_1 = new KeyboardControl(event, comandos, mundo->getPersonaje(0));
	//KeyboardControl* control_jugador_2 = new KeyboardControl(event, comandos, mundo->getPersonaje(1));

	//While Principal
	while( !control_jugador_1->getQuit() /*&& !control_jugador_2->getQuit()*/ ){
		control_jugador_1->KeyState();
		//control_jugador_2->KeyState();
		//Eventos */
		while( control_jugador_1->PollEvent() /*or control_jugador_2->PollEvent()*/ ){
			try {

				control_jugador_1->KeyPressed();
				//control_jugador_2->KeyPressed();

			} catch ( std::runtime_error &e ) {
				log ( "Refresh. Se recarga el mundo a partir del mismo archivo de configuracion JSON.", LOG_DEBUG );
				free(mundo,control_jugador_1/*,control_jugador_2*/);

				mundo = cargarMundo();
				if (mundo == NULL) return 1;
				log( "Se creo correctamente el Mundo de la partida.", LOG_DEBUG );

				//Creo los Controladores
				control_jugador_1 = new KeyboardControl(event, comandos, mundo->getPersonaje(0));
				//control_jugador_2 = new KeyboardControl(event, comandos, mundo->getPersonaje(1));

			}
		}

		mundo->render();


		//Sleep(Microsegundos)
		usleep(50000);
	}


	free(mundo,control_jugador_1/*,control_jugador_2*/);
	log("Se cierra el programa y se libera la memoria correspondiente al Mundo",LOG_DEBUG);

	return 0;
	//
}
