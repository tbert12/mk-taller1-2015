/*
 * Objeto.cpp
 *
 *  Created on: 28/4/2015
 *      Author: facu
 */

#include "ObjetoArrojable.h"

ObjetoArrojable::ObjetoArrojable(string un_nombre,float velocidad,Sprite* un_sprites) {
	nombre = un_nombre;
	vida = false;
	m_xActual = 0;
	m_yActual = 0;
	m_velocidad_x = velocidad;
	if(m_velocidad_x <= 0)
		m_velocidad_x = VELOCIDAD_DEFAULT;
	m_velocidad_y = velocidad;//por ahora
	if(m_velocidad_y <= 0)
		m_velocidad_y = VELOCIDAD_DEFAULT;
	sprite = un_sprites;
	if(sprite != NULL) sprite->doLoop(true);
	m_AltoMundo = 0;
	m_AnchoMundo = 0;
	flip = false;
	m_destruir = false;
}

Rect_Logico* ObjetoArrojable::rectanguloAtaque(){
	Rect_Logico* rectangulo = new Rect_Logico;
	rectangulo->x = m_xActual;
	rectangulo->y=  m_yActual;
	rectangulo->w = sprite->getAncho();
	rectangulo->h = sprite->getAlto();
	return rectangulo;
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
	if(m_destruir) return;
	if (!flip) m_xActual += m_velocidad_x;
	else m_xActual -= m_velocidad_x;
}

void ObjetoArrojable::_render(float pos_ventana){
	int x = m_xActual;
	if (flip)
		x -= sprite->getAncho();
	sprite->render(m_xActual - pos_ventana,m_yActual,flip);
	_avanzarSprite();
}

void ObjetoArrojable::_avanzarSprite(){
	sprite->Advance();
	if (m_destruir)
		sprite->doLoop(false);
	if(sprite->ultimoFrame()){
		//llego al final
		_terminar();
	}
}

void ObjetoArrojable::_terminar(){
	vida = false;
	m_destruir = false;
	m_xActual = 0;
	m_yActual = 0;
	sprite->Reset();
	sprite->doLoop(true);
}

void ObjetoArrojable::destruir(){
	m_destruir = true;
}

float ObjetoArrojable::getPosX(){
	return m_xActual;
}

void ObjetoArrojable::update(){
	_Update();
}

void ObjetoArrojable::renderizar(float x_dist_ventana){
	//si no tiene vida no lo renderizo
	if (!vida) return;

	_render(x_dist_ventana);
}


bool ObjetoArrojable::getVida(){
	return vida;
}

ObjetoArrojable::~ObjetoArrojable() {
	if(sprite != NULL)
		delete sprite;
}

