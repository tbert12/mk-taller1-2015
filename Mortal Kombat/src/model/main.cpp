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
#include "../controller/ComboController.h"
#include "../view/Ventana.h"
#include "Personaje.h"

//Variables
Mundo* mundo;
Controller* control;
Personaje* personaje_uno;
Personaje* personaje_dos;
int ModoDeJuego = 0; // 0 P1 vs P2


string ruta_archivo_configuracion = "data/config/Parallax.json";
map<string, int>* mapa_comandos1;
map<string, int>* mapa_comandos2;

Mundo* cargarDatos(){
	Mundo* unMundo;
	ParserJSON* parser;
	try {
			parser = new ParserJSON( ruta_archivo_configuracion );
			unMundo = parser->cargarMundo();
			std::vector<Personaje*> personajes = unMundo->getPersonajes();
			personaje_uno = personajes[0];
			personaje_dos = personajes[1];
			log( "Se creo correctamente el Mundo de la partida.", LOG_DEBUG );
			mapa_comandos1 = parser->getComandos1();
			mapa_comandos2 = parser->getComandos2();
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

void crearControlador(ComboController* combo){
	//Creo el Controlador
	switch(ModoDeJuego){
		case 0: //P1vsP2
			control = new Controller(personaje_uno,personaje_dos,mapa_comandos1, mapa_comandos2,combo);
			break;
		case 1://P1vsCPU o P1 Practica
			control = new Controller(personaje_uno,NULL,mapa_comandos1,mapa_comandos2,combo);
			break;
	}
}

bool _recargarMundo(){

	vector<Combo*> vect;
	ComboController* combo = new ComboController(10, 10 ,vect);

	log ( "Refresh. Se recarga el mundo a partir del mismo archivo de configuracion JSON.", LOG_WARNING );
	free(mundo,control);
	log ( "Refresh: se libero la memoria de lo cargado anteriormente", LOG_WARNING );


	mundo = cargarDatos();
	if (mundo == NULL){
		log ( "No se pudo cargar el mundo luego del refresh, se cierra el programa", LOG_ERROR );
		return false;
	}
	std::vector<Personaje*> personajes = mundo->getPersonajes();
	personaje_uno = personajes[0];
	personaje_dos = personajes[1];
	log( "Se creo correctamente el Mundo de la partida, luego del refresh", LOG_DEBUG );

	crearControlador(combo);
	return true;
}

int main( int argc, char* args[] )
{
	Combo* combo1 =new Combo("012");
	//Combo* combo2 =new Combo("345");
	//Combo* combo3 =new Combo("678");

	vector<Combo*> vect = {combo1};
	//vector<Combo*> vect = {combo1,combo2,combo3};


	ComboController* combo = new ComboController(10, 10 ,vect);

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

	//selector de modo

	//Creo el Controlador
	control = new Controller(personaje_uno,personaje_dos,mapa_comandos1, mapa_comandos2, combo);
	int i = 0;
	//While Principal
	while( !control->Quit()){
		control->KeyState();
		combo->Update();
		combo->checkPosibleCombo();

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
		//usleep(control->getSleep());
		usleep(500000);
	}


	free(mundo,control);
	log("Se cierra el programa y se libera la memoria correspondiente al Mundo",LOG_DEBUG);

	return 0;
}
