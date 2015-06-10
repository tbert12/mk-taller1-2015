/*
 * ObjetoDroppable.cpp
 *
 *  Created on: 9/6/2015
 *      Author: facu
 */

#include "ObjetoDroppable.h"

ObjetoDroppable::ObjetoDroppable(string un_nombre, float una_velocidad, Sprite* un_sprites,bool loopeable) {
	nombre = un_nombre;
	velocidad = una_velocidad;
	vida = false;
	mRebotar = false;
	tiempo = 0;
	contadorPorWhile = 0;
	loop = loopeable;
	m_yPiso = 0;
	m_xActual = 0;
	m_yActual = 0;
	m_xInicial = 0;
	m_yInicial = 0;
	m_velocidad_x = VELOCIDAD_OBJETO_DEFAULT_X;
	m_velocidad_y = VELOCIDAD_OBJETO_DEFAULT_Y;
	sprite = un_sprites;
	flip = false;

	mCantidad = 0;
}

void ObjetoDroppable::y_piso(float y_piso) {
	m_yPiso = y_piso;
}

void ObjetoDroppable::lanzar(float pos_x,float pos_y,bool flipeo, bool rebotar, int cantidad){
	if (vida) return;
	vida = true;
	flip = flipeo;
	m_xActual = pos_x;
	m_yActual = pos_y;
	m_xInicial = m_xActual;
	m_yInicial = m_yActual;
	mRebotar = rebotar;
	tiempo = 1;
	contadorPorWhile = 0;
	mCantidad = cantidad;
	if(sprite != NULL){
		sprite->hardReset();
		sprite->doLoop(false);
	}
}

void ObjetoDroppable::renderizar(float pos_ventana){
	_render(pos_ventana);
}

void ObjetoDroppable::_render(float pos_ventana){
	if (!vida) return;
	_Update();
	//for (int i = 0; i<mCantidad;i++)
	//sprite->render(m_xActual - pos_ventana + random() % 20,m_yActual + random() % 20,flip);
	sprite->render(m_xActual - pos_ventana,m_yActual,flip);
	_avanzarSprite();
}

bool ObjetoDroppable::getVida(){
	return vida;
}

void ObjetoDroppable::_avanzarSprite(){
	sprite->Advance();
	if(sprite->ultimoFrame() and !mRebotar){
		_terminar();
	}
}

void ObjetoDroppable::_Update(){
	if(!vida) return;
	_verificarTiempo();
	float mover = m_velocidad_x;
	if (flip){
		mover = - m_velocidad_x;
	}

	if (!mRebotar) m_xActual += mover;

	float gravity = 1;
	if (mRebotar) gravity = -tiempo*tiempo*0.5;
	m_yActual += -m_velocidad_y*tiempo + GRAVEDAD*gravity;
	if (m_yActual > m_yPiso or m_xActual <= 0){
		m_yActual = m_yPiso;
		m_yInicial = m_yActual;
		//m_velocidad_y = m_velocidad_y + 2;
		if (mRebotar){
			if (m_velocidad_y > 0)
				m_velocidad_y = 0;

			m_velocidad_x = m_velocidad_x - 1;
			if (m_velocidad_x < 0) m_velocidad_x = 0;
			tiempo = 0;
		} else {
			_terminar();
		}
	}
}

void ObjetoDroppable::_verificarTiempo(){
	contadorPorWhile++;
	if (contadorPorWhile >= ciclos_por_segundo){
		tiempo = 0;
	}
}

void ObjetoDroppable::reset(){
	_terminar();
}

void ObjetoDroppable::_terminar(){
	vida = false;
	mRebotar = false;
	tiempo = 1;
	contadorPorWhile = 0;
	m_xActual = 0;
	m_yActual = 0;
	m_xInicial = 0;
	m_yInicial = 0;
	m_velocidad_x = VELOCIDAD_OBJETO_DEFAULT_X;
	m_velocidad_y = VELOCIDAD_OBJETO_DEFAULT_Y;
	flip = false;
	mCantidad = 0;
}

ObjetoDroppable::~ObjetoDroppable() {
	if(sprite != NULL)
		delete sprite;
}

