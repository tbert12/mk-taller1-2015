/* main.cpp
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

#include "../controller/Controller.h"
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

void free(Mundo* mundo,Controller* c1){
	delete mundo;
	delete c1;
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

	//Creo el Controlador
	Controller* control = new Controller(mundo->getPersonaje(0),mundo->getPersonaje(1));

	//While Principal
	while( !control->Quit()){
		control->KeyState();
		while( control->PollEvent()){
			try {

				control->Pressed();

			} catch ( std::runtime_error &e ) {
				log ( "Refresh. Se recarga el mundo a partir del mismo archivo de configuracion JSON.", LOG_DEBUG );
				free(mundo,control);

				mundo = cargarMundo();
				if (mundo == NULL) return 1;
				log( "Se creo correctamente el Mundo de la partida.", LOG_DEBUG );

				//Creo el Controlador
				control = new Controller(mundo->getPersonaje(0),mundo->getPersonaje(1));
			}
		}

		mundo->render();


		//Sleep(Microsegundos)
		usleep(50000);
	}


	free(mundo,control);
	log("Se cierra el programa y se libera la memoria correspondiente al Mundo",LOG_DEBUG);

	return 0;
	//
}
