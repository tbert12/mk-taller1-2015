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
	ventana = NULL;
	personajes_z_index = 0;
	BarraJugador1 = NULL;
	BarraJugador2 = NULL;
}

bool Mundo::addPersonaje(Personaje* un_personaje){
	personajes.push_back(un_personaje);
	return true;
}
Personaje* Mundo::getPersonaje(int indice){
	if ((size_t)indice <= personajes.size()){
		return personajes[indice];
	}
	return NULL;
}

void Mundo::addCapa(Capa* una_capa) {
	capas.push_back(una_capa);
}

void Mundo::addCapaPrincipal( CapaPrincipal* capa_principal, int index ) {

	if ( index > (int)capas.size() ) {
		this->addCapa(capa_principal);
		personajes_z_index = capas.size()-1;
	} else {
		capas.insert(capas.begin()+index, capa_principal);
		personajes_z_index = index;
	}
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
	_crearBarras();
}
void Mundo::_crearBarras(){
	if (ventana == NULL) return;
	BarraJugador1 = new BarraEnergia(ventana,100);
	BarraJugador2 = new BarraEnergia(ventana,100);
	BarraJugador2->setFlip();
}
Ventana* Mundo::getVentana(){
	return ventana;
}

int Mundo::_verificarScroll(){
	CapaPrincipal* capa_principal = (CapaPrincipal*)capas[personajes_z_index];
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

void Mundo::_renderEstado(){
	if (BarraJugador1 != NULL)
		BarraJugador1->render(personajes[0]->getVida());//cambiar el get vida a int
	if (BarraJugador2 != NULL)
		BarraJugador2->render(personajes[1]->getVida());
}

void Mundo::render(){
	//limpio pantalla
	ventana->clear();

	//verifico scroll
	int scroll = _verificarScroll();


	//actualizo los estados
	for (unsigned int i = 0 ; i <= capas.size() -1 ; i++){
		capas[i]->Update(scroll);
	}

	//aca una vez actualizado to do chequeo las colisiones y demas.

	//renderizo las capas
	for (unsigned int i = 0 ; i <= capas.size() -1 ; i++){
		capas[i]->Renderizar();
	}

	//actualizo el estado de la pantalla
	_renderEstado();

	//actualizo pantalla -> SDL_RenderPresent( Renderer );
	ventana->Refresh();
}


Mundo::~Mundo() {
	//fijar si hay que liberar cada uno de los contenidos de los vectores
	for (unsigned int i = 0 ; i < capas.size() ; i++){
	      delete capas[i];
	}
	capas.clear();
	for (unsigned int i = 0 ; i < personajes.size() ; i++){
		delete personajes[i];
	}
	personajes.clear();
	delete ventana;
	delete tiempo;
	delete BarraJugador1;
	delete BarraJugador2;
}

