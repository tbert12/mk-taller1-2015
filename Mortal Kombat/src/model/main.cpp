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

Mundo* mundo;
Controller* control;

string ruta_archivo_configuracion = "data/config/Parallax.json";
map<string, int>* mapa_comandos1;
map<string, int>* mapa_comandos2;

Mundo* cargarMundo(){
	Mundo* unMundo;
	ParserJSON* parser;
	try {
			parser = new ParserJSON( ruta_archivo_configuracion );
			unMundo = parser->cargarMundo();
			log( "Se creo correctamente el Mundo de la partida.", LOG_DEBUG );
			mapa_comandos1 = parser->getComandos1();
			mapa_comandos2 = parser->getComandos2();
			mapa_comandos1 = parser->getComandos();
			mapa_comandos2 = mapa_comandos1;
			delete parser;
		} catch ( std::exception &e ) {
			log( "No se pudo crear el Mundo. Se aborta la ejecucion del programa. " + string(e.what()), LOG_ERROR );
			delete parser;
			if (unMundo)
				delete unMundo;
			return NULL;
	}
	return unMundo;
}

void free(Mundo* un_mundo,Controller* c1){
	delete un_mundo;
	delete c1;
}

bool _recargarMundo(){
	log ( "Refresh. Se recarga el mundo a partir del mismo archivo de configuracion JSON.", LOG_WARNING );
	free(mundo,control);
	log ( "Refresh: se libero la memoria de lo cargado anteriormente", LOG_WARNING );


	mundo = cargarMundo();
	if (mundo == NULL){
		log ( "No se pudo cargar el mundo luego del refresh, se cierra el programa", LOG_ERROR );
		return false;
	}

	log( "Se creo correctamente el Mundo de la partida, luego del refresh", LOG_DEBUG );

	//Creo el Controlador
	control = new Controller(mundo->getPersonaje(0),mundo->getPersonaje(1),mapa_comandos1, mapa_comandos2);
	control = new Controller(mundo->getPersonaje(0),mundo->getPersonaje(1),mapa_comandos1,mapa_comandos2);
	return true;
}

int main( int argc, char* args[] )
{


	// Marco inicio de un nuevo run en el .log
	prepararLog();

	if (argc > 1){
		ruta_archivo_configuracion = args[1];
	}

	mundo = cargarMundo();
	if (mundo == NULL) {
		return 1;
	}

	//Creo el Controlador
	control = new Controller(mundo->getPersonaje(0),mundo->getPersonaje(1),mapa_comandos1, mapa_comandos2);
	control = new Controller(mundo->getPersonaje(0),mundo->getPersonaje(1),mapa_comandos1,mapa_comandos2);

	//While Principal
	while( !control->Quit()){
		control->KeyState();
		while( control->PollEvent()){
			try {

				control->Pressed();

			} catch ( std::runtime_error &e ) {
				if(!_recargarMundo()) return 1;
			}
		}

		//si no esta en pausa
		if (!control->pausa()){
			if(mundo->partida_finalizada){
				if(!_recargarMundo()) return 1;
			}
			mundo->render();
		}

		//Sleep(Microsegundos)
		usleep(control->getSleep());
	}


	free(mundo,control);
	log("Se cierra el programa y se libera la memoria correspondiente al Mundo",LOG_DEBUG);

	return 0;
}
