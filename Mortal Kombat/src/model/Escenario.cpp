/*
 * Escenario.cpp
 *
 *  Created on: 22/5/2015
 *      Author: facu
 */

#include "Escenario.h"

Escenario::Escenario() {
	capaPrincipal = NULL;
	PersonajeUno = NULL;
	PersonajeDos = NULL;

}

void Escenario::addCapa(Capa* una_capa) {
	capas.push_back(una_capa);
}

std::vector<Capa*> Escenario::getCapas(){
	return capas;
}

void Escenario::addCapaPrincipal(CapaPrincipal* capa_principal, int index){
	if ( index > (int)capas.size() ) {
		this->addCapa(capa_principal);
	} else {
		capas.insert(capas.begin()+index, capa_principal);
	}
	capaPrincipal = capa_principal;
}

void Escenario::addPersonajes(Personaje* un_Personaje,Personaje* otro_Personaje){
	PersonajeUno = un_Personaje;
	PersonajeDos = otro_Personaje;
	capaPrincipal->addPersonajes(PersonajeUno,PersonajeDos);
}

CapaPrincipal* Escenario::getCapaPrincipal(){
	return capaPrincipal;
}

void Escenario::Update(){
	//verifico scroll
	int scroll = capaPrincipal->Scrollear();

	//actualizo los estados
	for (unsigned int i = 0 ; i <= capas.size() -1 ; i++){
		capas[i]->Update(scroll);
	}
}

void Escenario::render(){
	//renderizo las capas
	for (unsigned int i = 0 ; i <= capas.size() -1 ; i++){
		capas[i]->Renderizar();
	}
}

Escenario::~Escenario() {
	for (unsigned int i = 0 ; i < capas.size() ; i++){
		      delete capas[i];
	}
	capas.clear();

	capaPrincipal = NULL;
	PersonajeUno = NULL;
	PersonajeDos = NULL;
}

