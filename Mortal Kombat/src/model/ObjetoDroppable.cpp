/*
 * ObjetoDroppable.cpp
 *
 *  Created on: 9/6/2015
 *      Author: facu
 */

#include "ObjetoDroppable.h"

ObjetoDroppable::ObjetoDroppable(Sprite* un_sprites,float y_piso,bool loopeable) {
	vida = false;
	tiempo = 0;
	contadorPorWhile = 0;
	loop = loopeable;
	m_yPiso = y_piso;
	m_xActual = 0;
	m_yActual = 0;
	m_xInicial = 0;
	m_yInicial = 0;
	m_velocidad_x = VELOCIDAD_OBJETO_DEFAULT;
	m_velocidad_y = VELOCIDAD_OBJETO_DEFAULT;
	sprite = un_sprites;
	flip = false;
}

void ObjetoDroppable::lanzar(float pos_x,float pos_y,bool flipeo){
	if (vida) return;
	vida = true;
	flip = flipeo;
	m_xActual = pos_x;
	m_yActual = pos_y;
	m_xInicial = m_xActual;
	m_yInicial = m_yActual;
	tiempo = 0;
	contadorPorWhile = 0;
	if(sprite != NULL){
		sprite->hardReset();
		if (loop)
			sprite->doLoop(true);
	}
}

void ObjetoDroppable::_render(float pos_ventana){
	if (!vida) return;
	_Update();
	sprite->render(m_xActual - pos_ventana,m_yActual,flip);
	_avanzarSprite();
}

bool ObjetoDroppable::getVida(){
	return vida;
}

void ObjetoDroppable::_avanzarSprite(){
	sprite->Advance();
	if(sprite->ultimoFrame()){
		_terminar();
	}
}

void ObjetoDroppable::_Update(){
	if(!vida) return;
	_verificarTiempo();
	if (flip){
		m_xActual -= m_velocidad_x;
	}
	else{
		m_xActual += m_velocidad_x;
	}
	m_yActual = m_yInicial + m_velocidad_y*tiempo + 0.5*G*tiempo*tiempo;
	if (m_yActual > m_yPiso) m_yActual = m_yPiso;
}

void ObjetoDroppable::_verificarTiempo(){
	contadorPorWhile++;
	if (contadorPorWhile >= ciclos_por_segundo){
		tiempo++;
		contadorPorWhile = 0;
	}
}

void ObjetoDroppable::_terminar(){
	vida = false;
	tiempo = 0;
	contadorPorWhile = 0;
	m_xActual = 0;
	m_yActual = 0;
	m_xInicial = 0;
	m_yInicial = 0;
	m_velocidad_x = VELOCIDAD_OBJETO_DEFAULT;
	m_velocidad_y = VELOCIDAD_OBJETO_DEFAULT;
	flip = false;
}

ObjetoDroppable::~ObjetoDroppable() {
	if(sprite != NULL)
		delete sprite;
}

