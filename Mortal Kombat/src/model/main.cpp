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

#include "../view/Ventana.h"
#include "../controller/KeyboardControl.h"
#include "Personaje.h"

string ruta_archivo_configuracion = "data/config/default.json";

int main( int argc, char* args[] )
{
	if (argc){
		log(string("Se cargara el archivo JSON por parametro: " + ruta_archivo_configuracion),LOG_DEBUG);
		ruta_archivo_configuracion = args[0];
	}
	else {
		log(string("Se cargara el archivo JSON default: " + ruta_archivo_configuracion),LOG_ERROR);

	}

	// Marco inicio de un nuevo run en el .log
	prepararLog();

	Mundo* mundo;

	try {
		ParserJSON* parser = new ParserJSON( ruta_archivo_configuracion );
		mundo = parser->cargarMundo();
		//mundo = CrearMundoDefault();
		log( "Se creo correctamente el Mundo de la partida.", LOG_DEBUG );
	} catch ( std::exception &e ) {
		log( "No se pudo crear el Mundo. Se aborta la ejecucion del programa. " + string(e.what()), LOG_ERROR );
		return 1;
	}

	//Creo el Personaje
	Personaje* luchador = mundo->getPersonaje();


	//mostrar imagen inicio
	if(mundo->mostrarImagen("data/img/background/inicio.png")){
		//3 segundos
		usleep(3000000);
	}

	//Creo el Controlador
	KeyboardControl* control_jugador_1 = new KeyboardControl(luchador);

	//While Principal
	while( !control_jugador_1->getQuit() ){
		control_jugador_1->KeyState();
		//Eventos */
		while( control_jugador_1->PollEvent() ){
			try {
				control_jugador_1->KeyPressed();
			// RELOAD
			// ESTA HECHO A LO VILLA PORQUE TOTAL DESPUES ESTO VUELA A LA MIERDA.
			} catch ( std::runtime_error &e ) {
				log ( "Refresh. Se recarga el mundo a partir del mismo archivo de configuracion JSON.", LOG_DEBUG );
				try {
					delete control_jugador_1;
					delete mundo;
					ParserJSON* parser = new ParserJSON( ruta_archivo_configuracion );
					mundo = parser->cargarMundo();
					//mundo = CrearMundoDefault();
					log( "Se creo correctamente el Mundo de la partida.", LOG_DEBUG );
					//Creo el Personaje
					luchador = mundo->getPersonaje();
					//Creo el Controlador
					control_jugador_1 = new KeyboardControl(luchador);
				} catch ( std::runtime_error &e ) {
					log( "No se pudo crear el Mundo. Se aborta la ejecucion del programa. " + string(e.what()), LOG_ERROR );
					return 1;
				}
			}
		}
		mundo->render();
		//Sleep(Microsegundos)
		usleep(50000);

	}

	delete mundo;
	log("Se cierra el programa y se libera la memoria correspondiente al Mundo",LOG_DEBUG);

	return 0;
}


