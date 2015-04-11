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
	personaje_z_index = 0;
	capas = std::vector<Capa*>(6);
}

void Mundo::setZindexCapaPrincipal(int index){
	personaje_z_index = index;
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

bool Mundo::addCapa(Capa* una_capa,int index){
	if (std::find(indices.begin(), indices.end(), index)!= indices.end()){
		log(string("No se pudo agregar la capa con z_index:%i",index),LOG_ERROR);
		return false;
	}
	capas[index] = una_capa;
	indices.push_back(index);
	std::sort(indices.begin(),indices.end());
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
	CapaPrincipal* capa_principal = (CapaPrincipal*)capas[personaje_z_index];
	return capa_principal->Scrollear();
}

bool Mundo::mostrarImagen(string ruta){
	if(!ventana->mostrarImagen(ruta)){
		log("No se pudo mostrar la imagen",LOG_ERROR);
		return false;
	}
	log("Se muestra imagen de inicio",LOG_DEBUG);
	return true;
}

void Mundo::render(){
	//limpio pantalla
	ventana->clear();

	//verifico scroll
	int scroll = _verificarScroll();

	//renderizo las capas
	for (unsigned int i = 0 ; i <= indices.size() -1 ; i++){
		//capas[indices[i]]->Mover(true);
		if(scroll > 0) {
			capas[indices[i]]->Mover(true);
		}
		if(scroll < 0) {
			capas[indices[i]]->Mover(false);
		}

		capas[indices[i]]->Renderizar();
	}

	//actualizo pantalla -> SDL_RenderPresent( Renderer );
	ventana->Refresh();
}


Mundo::~Mundo() {
	//fijar si hay que liberar cada uno de los contenidos de los vectores
	for (unsigned int i = 0 ; i < indices.size() -1 ; i++){
	      capas[indices[i]]->~Capa();
	}
	capas.clear();
	for (unsigned int i = 0 ; i < personajes.size() ; i++){
	      personajes[i]->~Personaje();
	}
	personajes.clear();
	ventana->close_window();
	tiempo->~Tiempo();
}

