/*
 * Objeto.cpp
 *
 *  Created on: 28/4/2015
 *      Author: facu
 */

#include "ObjetoArrojable.h"

ObjetoArrojable::ObjetoArrojable(string un_nombre,float velocidad,std::vector<Sprite*> unos_sprites) {
	nombre = un_nombre;
	vida = false;
	m_xActual = 0;
	m_yActual = 0;
	m_velocidad = velocidad;
	sprites = unos_sprites;
	m_AltoMundo = 0;
	m_AnchoMundo = 0;
}
void ObjetoArrojable::setDimensionesMundo(float alto,float ancho){
	m_AltoMundo = alto;
	m_AnchoMundo = ancho;
}

bool ObjetoArrojable::lanzar(float pos_x, float pos_y){
	if (vida) return false;
	m_xActual = pos_x;
	m_yActual = pos_y;
	vida = true;
	return true;
}

void ObjetoArrojable::_Update(){

}

void ObjetoArrojable::renderizar(float x_dist_ventana, float posOtherPlayer){
	//si no tiene vida no lo renderizo
	if (!vida) return;

	_Update();

	//render

}

ObjetoArrojable::~ObjetoArrojable() {
	// TODO Auto-generated destructor stub
}

