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

#include "../controller/KeyboardControl1.h"
#include "../controller/KeyboardControl2.h"
#include "../view/Ventana.h"
#include "Personaje.h"

string ruta_archivo_configuracion = "data/config/Parallax.json";

int main( int argc, char* args[] )
{


	// Marco inicio de un nuevo run en el .log
	prepararLog();

	if (argc > 1){
		ruta_archivo_configuracion = args[1];
	}

	ParserJSON* parser;
	Mundo* mundo;

	try {
		parser = new ParserJSON( ruta_archivo_configuracion );
		mundo = parser->cargarMundo();
		log( "Se creo correctamente el Mundo de la partida.", LOG_DEBUG );
	} catch ( std::exception &e ) {
		log( "No se pudo crear el Mundo. Se aborta la ejecucion del programa. " + string(e.what()), LOG_ERROR );
		delete parser;
		delete mundo;
		return 1;
	}

	//Creo los Personajes
	Personaje* luchador1 = mundo->getPersonaje(0);
	Personaje* luchador2 = mundo->getPersonaje(1);


	//mostrar imagen inicio
	if(mundo->mostrarImagen("data/img/background/inicio.png")){
		//3 segundos
		usleep(3000000);
	}

	//Creo los Controladores
	KeyboardControl1* control_jugador_1 = new KeyboardControl1(luchador1);
	KeyboardControl2* control_jugador_2 = new KeyboardControl2(luchador2);

	//While Principal
	while( !control_jugador_1->getQuit() && !control_jugador_2->getQuit() ){
		control_jugador_1->KeyState();
		//Eventos */
		while( control_jugador_1->PollEvent() ){
			try {
				control_jugador_1->KeyPressed();
			// RELOAD
			// ESTA HECHO A LO VILLA PORQUE TOTAL DESPUES ESTO VUELA A LA MIERDA.
			} catch ( std::runtime_error &e ) {
				log ( "Refresh. Se recarga el mundo a partir del mismo archivo de configuracion JSON.", LOG_DEBUG );
				delete parser;
				delete control_jugador_1;
				delete control_jugador_2;
				delete mundo;

				try {
					parser = new ParserJSON( ruta_archivo_configuracion );
					mundo = parser->cargarMundo();
					log( "Se creo correctamente el Mundo de la partida.", LOG_DEBUG );
					//Creo los Personajes
					luchador1 = mundo->getPersonaje(0);
					luchador2 = mundo->getPersonaje(1);
					//Creo los Controladores
					control_jugador_1 = new KeyboardControl1(luchador1);
					control_jugador_2 = new KeyboardControl2(luchador2);
				} catch ( std::runtime_error &e ) {
					log( "No se pudo crear el Mundo. Se aborta la ejecucion del programa. " + string(e.what()), LOG_ERROR );
					return 1;

				}

			}
		}
		control_jugador_2->KeyState();
		while ( control_jugador_2->PollEvent() ) {
			control_jugador_2->KeyPressed();
		}

		mundo->render();
		//Sleep(Microsegundos)
		usleep(50000);

	}
	delete parser;
	delete control_jugador_1;
	delete control_jugador_2;
	delete mundo;
	log("Se cierra el programa y se libera la memoria correspondiente al Mundo",LOG_DEBUG);

	return 0;
}
