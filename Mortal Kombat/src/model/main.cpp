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

const string ruta_archivo_configuracion = "data/config/ejemplo.json";

int main( int argc, char* args[] )
{

	// Marco inicio de un nuevo run en el .log
	prepararLog();

	Mundo* mundo;

	try {
		ParserJSON* parser = new ParserJSON( ruta_archivo_configuracion );
		//mundo = parser->cargarMundo();
		mundo = CrearMundoDefault();
		log( "Se creo correctamente el Mundo de la partida.", LOG_DEBUG );
	} catch ( const std::exception &e ) {
		log( "No se pudo crear el Mundo. Se aborta la ejecucion del programa. " + string(e.what()), LOG_ERROR );
		return 1;
	}

	//Creo el Personaje
	Personaje* luchador = mundo->getPersonaje();

	/*
	//mostrar imagen inicio
	if(mundo->mostrarImagen("data/img/background/inicio.png")){
		//3 segundos
		usleep(3000000);
	}
	*/
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
	log("Se cierra el programa y se libera la memoria correspondiente al Mundo",LOG_DEBUG);

	return 0;
}


