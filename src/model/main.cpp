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
#include "SoundMenu.h"
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
	Mundo* unMundo = NULL;
	try {
			parser = new ParserJSON( ruta_archivo_configuracion );
			unMundo = parser->cargarMundo();
			log( "Se creo correctamente el Mundo de la partida.", LOG_DEBUG );
		} catch ( std::exception &e ) {
			log( "No se pudo crear el Mundo. Se aborta la ejecucion del programa. " + string(e.what()), LOG_ERROR );
			if (unMundo)
				delete unMundo;
			return NULL;
	}
	return unMundo;
}

void _cambiarPersonajes(){

	std::vector<Personaje*> personajes = mundo->getPersonajes();
	Personaje* p_nuevo = NULL;
	Personaje* p_uno = mundo->getPersonajeUno();
	Personaje* p_dos = mundo->getPersonajeDos();

	for (unsigned int i = 0; i < personajes.size();i++){
		if (personajes[i]->getNombreDeCarga() != p_dos->getNombreDeCarga())
			p_nuevo = personajes[i];
	}

	if (p_nuevo == NULL){
		p_nuevo = personajes[rand() % personajes.size()];
		while (p_dos == p_nuevo)
			p_nuevo = personajes[rand() % personajes.size()];
	}
	else p_dos = p_nuevo;

	if (p_dos->getNombreDeCarga() == p_uno->getNombreDeCarga()){
		p_dos = parser->cambiarColorPersonaje(p_dos);
	}

	mundo->setPersonajesDeJuego(p_uno,p_dos);
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

		SoundMenu* sonido = new SoundMenu();

		MenuSeleccion* menu = new MenuSeleccion(mundo->getVentana(),sonido);
		if (menu == NULL){
			delete sonido;
			return 1;
		}
		ControlModo* controlModo = new ControlModo(menu);
		if (controlModo == NULL){
			delete sonido;
			delete menu;
			return 1;
		}

		//MUSICA DE FONDO
		sonido->play(FONDO);

		//While Seleccion de modo
		while (!controlModo->Quit() && !menu->modeSelected()){
			while( controlModo->PollEvent() ){
				controlModo->Pressed();
			}
			menu->render();
		}

		if (controlModo->Quit()){
			delete sonido;
			delete menu;
			delete controlModo;
			delete mundo;
			delete parser;
			return 0;
		}

		int modoDeJuego = menu->modoDeJuego();
		delete menu;
		delete controlModo;

		SelectPlayer* selectPlayer = new SelectPlayer(mundo->getVentana(),modoDeJuego,mundo->getPersonajes(),sonido);
		ControlSelectPlayer* controlSelect = new ControlSelectPlayer(selectPlayer,(modoDeJuego == MODO_JUGADOR_VS_JUGADOR));

		while(!controlSelect->Quit() && !selectPlayer->playersSelected() ){
			while( controlSelect->PollEvent() ){
				controlSelect->Pressed();
			}

			selectPlayer->render();
		}

		if (controlSelect->Quit()){
			delete sonido;
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
			personaje_dos = parser->cambiarColorPersonaje(personaje_dos);
		}

		//seteo modo de juego
		mundo->setPersonajesDeJuego(personaje_uno,personaje_dos);
		mundo->setModoDeJuego(modoDeJuego);

		sonido->stop(FONDO);
		delete sonido;

		//While Juego
		if (modoDeJuego == MODO_JUGADOR_VS_PC){
			//3 peleas
			for (int i = 0; i < 3 ;i++){
				while( !mundo->Fin() and !mundo->Quit()){
					//si no esta en pausa
					mundo->render();

					SDL_Delay(mundo->getSleep()/1000);
					//usleep(50000);
				}
				if (mundo->Fin()){
					if (mundo->ganoCPU()) break;
					_cambiarPersonajes();
					mundo->reset();
				}
			}
		}
		else{
			while( !mundo->Fin() and !mundo->Quit()){

				//si no esta en pausa
				mundo->render();

				SDL_Delay(mundo->getSleep()/1000);
				//usleep(50000);
			}
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
