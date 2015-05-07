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
	m_velocidad_x = velocidad;
	m_velocidad_y = velocidad;//por ahora
	sprites = unos_sprites;
	m_AltoMundo = 0;
	m_AnchoMundo = 0;
	sprite_actual = 0;
	flip = false;
}
void ObjetoArrojable::setDimensionesMundo(float alto,float ancho){
	m_AltoMundo = alto;
	m_AnchoMundo = ancho;
}

bool ObjetoArrojable::lanzar(float pos_x, float pos_y,bool flipeo){
	if (vida) return false;
	m_xActual = pos_x;
	m_yActual = pos_y;
	vida = true;
	flip = flipeo;
	return true;
}

void ObjetoArrojable::_Update(){
	if (!flip) m_xActual += m_velocidad_x;
	else m_xActual -= m_velocidad_x;
}

void ObjetoArrojable::_render(float pos_ventana){
	sprites[sprite_actual]->render(m_xActual - pos_ventana,m_yActual,flip);
}

void ObjetoArrojable::destruir(){
	vida = false;
	m_xActual = 0;
	m_yActual = 0;
}

float ObjetoArrojable::getPosX(){
	return m_xActual;
}

void ObjetoArrojable::renderizar(float x_dist_ventana){
	//si no tiene vida no lo renderizo
	if (!vida) return;

	_Update();

	_render(x_dist_ventana);
}


bool ObjetoArrojable::getVida(){
	return vida;
}

ObjetoArrojable::~ObjetoArrojable() {
	for (size_t i=0; i < sprites.size() ; i++){
			delete sprites[i];
		}
}

