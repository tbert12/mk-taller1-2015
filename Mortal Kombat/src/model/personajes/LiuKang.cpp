/*
 * liukang.cpp
 *
 *  Created on: 7/6/2015
 *      Author: tomi
 */

#include "LiuKang.h"

namespace std {

LiuKang::LiuKang(string nombre_personaje,vector<Sprite*> Sprites,vector<ObjetoArrojable*> arrojables ,float velocidad, bool fliped)
:Personaje(nombre_personaje,Sprites,arrojables,velocidad,fliped){
	_estaHaciendoPoder = false;
	_resetDuracion();
}

int LiuKang::_getaccionPropia(){
	if (!_estaHaciendoPoder) return 0;
	return SPRITE_PATADA_SALTANDO;
}

bool LiuKang::_updatePropio(){
	//Retorna true si lo que esta haciendo NO es un poder propio
	if ( !_estaHaciendoPoder ) return false;
	if ( spriteActual->ultimoFrame() ){
		if (duracionPoder){
			duracionPoder--;
		} else {
			terminarPoder2();
			_resetDuracion();
		}
	}
	spriteActual->Advance();
	return true;

}

void LiuKang::_resetDuracion(){
	duracionPoder = 5;
}

void LiuKang::terminarPoder2(){
	spriteActual = sprites[SPRITE_INICIAL];
	m_yActual = m_yPiso;
	m_velocidadActual = 0;
	_estaHaciendoPoder = false;
	_estaAtacando = false;
	_estaSaltando = -1;
}

void LiuKang::poder2(){
	_cambiarSprite(SPRITE_PODER_2);
	m_yActual = m_yPiso - getAlto();
	float velocidad = 3 * m_velocidad;
	if (m_fliped){
		velocidad = - velocidad;
	}
	m_velocidadActual = velocidad;
	_estaAtacando = true;
	_estaSaltando = 1;
	_estaHaciendoPoder = true;
}

void LiuKang::fatality1(Personaje* personajeQueRecibe){
	_cambiarSprite(SPRITE_FATALITY_1);
	spriteActual->doLoop(true);

}

void LiuKang::terminarAtaque(){
	if (_estaHaciendoPoder){
		terminarPoder2();
		m_velocidadActual = - m_velocidad;
		if (m_fliped) m_velocidadActual = m_velocidad;
		Saltar();
	}
}

LiuKang::~LiuKang() {
	// Llama automaticante al destructor de Personaje
}

} /* namespace std */
