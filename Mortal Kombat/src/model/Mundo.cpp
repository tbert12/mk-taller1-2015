/*
 * Mundo.cpp
 *
 *  Created on: Apr 6, 2015
 *      Author: seba
 */

#include "Mundo.h"

Mundo::Mundo(float ancho,float alto) {
	ancho_mundo = ancho;
	alto_mundo = alto;
	tiempo = NULL;
	escenario = NULL;
	ventana = NULL;
}

bool Mundo::addPersonaje(Personaje* un_personaje){
	//if (personajes == NULL){
	//	return false;
	//}
	personajes.push_back(un_personaje);
	return true;
}
Personaje* Mundo::getPersonaje(int indice){
	if ((size_t)indice <= personajes.size()){
		return personajes[indice];
	}
	return NULL;
}

bool Mundo::addCapa(Capa* una_capa){
	//if (capas == NULL){
	//		return false;
	//}
	capas.push_back(una_capa);
	return true;
}
Capa* Mundo::getCapa(int indice){
	if ((size_t)indice <= capas.size()){
		return capas[indice];
	}
	return NULL;
}
void Mundo::setTiempo(Tiempo* unTiempo){
	tiempo = unTiempo;
}
void Mundo::setVentana(Ventana* unaVentana){
	ventana = unaVentana;
}
Ventana* Mundo::getVentana(){
	return ventana;
}
void Mundo::setEscenario(Escenario* unEscenario){
	escenario = unEscenario;
}
Escenario* Mundo::getEscenario(){
	return escenario;
}
int Mundo::_verificarScroll(){
	CapaPrincipal* capa_principal = (CapaPrincipal*)capas[capas.size()-1];
	return capa_principal->Scrollear();
}

void Mundo::render(){
	//limpio pantalla
	ventana->clear();

	//verifico scroll
	int scroll = _verificarScroll();
	//renderizo las capas
	for (unsigned int i = 0 ; i <= capas.size()-1 ; i++){
<<<<<<< HEAD
		capas[i]->Mover(true);
=======
		if(scroll > 0) {
			capas[i]->Mover(true);
			printf("mover derecha \n");
		}
		if(scroll < 0) {
			capas[i]->Mover(false);
			printf("mover izquierda \n");
		}
>>>>>>> 85bd7a198744ff541d20009763ef9ffefbdd3060
		capas[i]->Renderizar();
	}

	//actualizo pantalla -> SDL_RenderPresent( Renderer );
	ventana->Refresh();
}

Mundo::~Mundo() {
	//fijar si hay que liberar cada uno de los contenidos de los vectores
	for (unsigned int i = 0 ; i < capas.size() ; i++){
	      capas[i]->~Capa();
	}
	capas.clear();
	for (unsigned int i = 0 ; i < personajes.size() ; i++){
	      personajes[i]->~Personaje();
	}
	personajes.clear();
	ventana->close_window();
	tiempo->~Tiempo();
}

