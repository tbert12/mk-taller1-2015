/*
 * Mundo.cpp
 *
 *  Created on: Apr 6, 2015
 *      Author: seba
 */

#include "Mundo.h"

Mundo::Mundo(float ratioX,float ratioY) {
	ratio_x = ratioX;
	ratio_y = ratioY;
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
	if (indice <= personajes.size()){
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
	if (indice <= capas.size()){
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

void Mundo::render(){
	Personaje* personaje = personajes[0];//HARCODEADO POR QUE HAY UNO SOLO
	ventana->Refresh(personaje->getSpriteActual());

	//renderizo las capas
	for (int i = 0 ; i < capas.size() ; i++){
		capas[i]->Renderizar();
	}

}

Mundo::~Mundo() {
	//fijar si hay que liberar cada uno de los contenidos de los vectores
	for (int i = 0 ; i < capas.size() ; i++){
	      capas[i]->~Capa();
	}
	capas.clear();
	for (int i = 0 ; i < personajes.size() ; i++){
	      personajes[i]->~Personaje();
	}
	personajes.clear();
	ventana->close_window();
	tiempo->~Tiempo();
}

