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
#include <algorithm>
#include "../controller/ControlModo.h"
#include "../controller/ControlSelectPlayer.h"
#include "MenuSeleccion.h"
#include "SelectPlayer.h"
#include "../view/Ventana.h"
#include "Personaje.h"

//Variables
Mundo* mundo;
ParserJSON* parser;

string ruta_archivo_configuracion = "data/config/Parallax.json";

Mundo* cargarDatos(){
	Mundo* unMundo;
	try {
			parser = new ParserJSON( ruta_archivo_configuracion );
			unMundo = parser->cargarMundo();
			log( "Se creo correctamente el Mundo de la partida.", LOG_DEBUG );
			delete parser;
		} catch ( std::exception &e ) {
			log( "No se pudo crear el Mundo. Se aborta la ejecucion del programa. " + string(e.what()), LOG_ERROR );
			if (unMundo)
				delete unMundo;
			return NULL;
	}
	return unMundo;
}

bool _recargarMundo(){

	log ( "Refresh. Se recarga el mundo a partir del mismo archivo de configuracion JSON.", LOG_WARNING );
	delete mundo;
	log ( "Refresh: se libero la memoria de lo cargado anteriormente", LOG_WARNING );


	mundo = cargarDatos();
	if (mundo == NULL){
		log ( "No se pudo cargar el mundo luego del refresh, se cierra el programa", LOG_ERROR );
		return false;
	}
	log( "Se creo correctamente el Mundo de la partida, luego del refresh", LOG_DEBUG );
	return true;
}

int main( int argc, char* args[] )
{
	// Marco inicio de un nuevo run en el .log
	prepararLog();

	if (argc > 1){
		ruta_archivo_configuracion = args[1];
	}

	//cargo los datos
	mundo = cargarDatos();
	if (mundo == NULL) {
		return 1;
	}

	while(!mundo->Quit()){

		MenuSeleccion* menu = new MenuSeleccion(mundo->getVentana());
		if (menu == NULL)
			return 1;
		ControlModo* controlModo = new ControlModo(menu);
		if (controlModo == NULL)
			return 1;

		//While Seleccion de modo
		while (!controlModo->Quit() && !menu->modeSelected()){
			while( controlModo->PollEvent() ){
				controlModo->Pressed();
			}
			menu->render();
		}

		if (controlModo->Quit()){
			delete menu;
			delete controlModo;
			delete mundo;
			delete parser;
			return 0;
		}

		int modoDeJuego = menu->modoDeJuego();
		delete menu;
		delete controlModo;

		SelectPlayer* selectPlayer = new SelectPlayer(mundo->getVentana(),modoDeJuego,mundo->getPersonajes());
		ControlSelectPlayer* controlSelect = new ControlSelectPlayer(selectPlayer,(modoDeJuego == MODO_JUGADOR_VS_JUGADOR));

		while(!controlSelect->Quit() && !selectPlayer->playersSelected() ){
			while( controlSelect->PollEvent() ){
				controlSelect->Pressed();
			}

			selectPlayer->render();
		}

		if (controlSelect->Quit()){
			delete controlSelect;
			delete selectPlayer;
			delete menu;
			delete controlModo;
			delete mundo;
			delete parser;
			return 0;
		}
		Personaje* personaje_uno;
		Personaje* personaje_dos;

		if (selectPlayer->playersSelected()){
			personaje_uno = selectPlayer->getPersonajeUno();
			personaje_dos = selectPlayer->getPersonajeDos();
			delete controlSelect;
			delete selectPlayer;
		}

		if (personaje_uno->getNombreDeCarga() == personaje_dos->getNombreDeCarga() ){
			printf("CAMBIO DE COLOR\n");
			personaje_dos = parser->cambiarColorPersonaje(personaje_dos);
		}

		//seteo modo de juego
		mundo->setPersonajesDeJuego(personaje_uno,personaje_dos);
		mundo->setModoDeJuego(modoDeJuego);

		//While Juego
		while( !mundo->Fin() and !mundo->Quit()){

			//si no esta en pausa
			mundo->render();

			usleep(mundo->getSleep());
			//usleep(50000);
		}
		if (mundo->Fin()){
			mundo->reset();
		}
	}
	delete parser;
	delete mundo;
	log("Se cierra el programa y se libera la memoria correspondiente al Mundo",LOG_DEBUG);

	return 0;
}
