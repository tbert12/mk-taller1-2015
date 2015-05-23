/*
 * Mundo.cpp
 *
 *  Created on: Apr 6, 2015
 *      Author: seba
 */

#include "Mundo.h"

Mundo::Mundo(Ventana* una_ventana, int tiempo) {
	ventana = una_ventana;
	escenario_actual = NULL;
	pelea = NULL;
	tiempo_round = tiempo;
	empezar = false;
	partida_finalizada = false;
}

void Mundo::start(){
	if (escenarios[0]){
		escenario_actual = escenarios[0];
		escenario_actual->addPersonajes(personajes[0],personajes[1]);
		pelea = new Pelea(ventana,escenario_actual,tiempo_round);
	}
}

void Mundo::addPersonaje(Personaje* un_personaje){
	personajes.push_back(un_personaje);
}

void Mundo::addEscenario(Escenario* un_escenario){
	escenarios.push_back(un_escenario);
}

std::vector<Personaje*> Mundo::getPersonajes(){
	return personajes;
}


Ventana* Mundo::getVentana(){
	return ventana;
}

void Mundo::render(){
	if(!empezar){
		start();
		empezar = true;
	}

	//limpio pantalla
	ventana->clear();
	
	if(pelea->peleaFinalizada()){
		printf("PATIDA FINALIZADA\n");
		partida_finalizada = true;
	}

	pelea->render();

	//actualizo pantalla -> SDL_RenderPresent( Renderer );
	ventana->Refresh();
}

void Mundo::_mostrar_ganador(string nombre){
	string texto = "Ganador \n" + nombre;
	ventana->mostrarTexto(texto);
	usleep(3000000);
}

Mundo::~Mundo() {

	for (unsigned int i = 0 ; i < escenarios.size() ; i++){
	      delete escenarios[i];
	}
	escenarios.clear();

	for (unsigned int i = 0 ; i < personajes.size() ; i++){
		delete personajes[i];
	}
	personajes.clear();

	if (pelea) delete pelea;

	if(ventana) delete ventana; //Siempre eliminarlo Ultimo (Hace SDL_Quit)
}

