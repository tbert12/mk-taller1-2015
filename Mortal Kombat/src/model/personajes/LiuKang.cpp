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
	_estaHaciendoFatality = false;
	personajeQueRecibe = NULL;
	_resetDuracion();
}

int LiuKang::_getaccionPropia(){
	if (!_estaHaciendoPoder) return 0;
	return SPRITE_PATADA_SALTANDO;
}

bool LiuKang::_updatePropio(){
	//Retorna true si lo que esta haciendo NO es un poder propio
	if ( !_estaHaciendoPoder and !_estaHaciendoFatality and !_estaHaciendoFatality2) return false;
	if ( spriteActual->ultimoFrame() ){
		if (duracionPoder){
			duracionPoder--;
		} else {
			terminarPoder2();
		}
	} else if (_estaHaciendoFatality){
		bool proxUltimo = spriteActual->inFrezee();
		if (proxUltimo){
			m_yActual = -2*getAlto();
			float x_delOtro = personajeQueRecibe->getX() + personajeQueRecibe->getAncho();
			if ( personajeQueRecibe->getFlipState() ) x_delOtro = personajeQueRecibe->getX() - personajeQueRecibe->getAncho();
			m_xActual = x_delOtro;
		}
		if (m_yActual < m_yPiso){
			float diferencial = m_yActual + 30;
			if (diferencial > m_yPiso) diferencial = m_yPiso;
			m_yActual = diferencial;
		}
		float altura = personajeQueRecibe->getAlto();
		if (spriteActual->inLoop() and m_yActual > altura + 40 and m_yActual < altura + 100  ){
			personajeQueRecibe->morir();
		}

	} else if (_estaHaciendoFatality2){
		_updateFatality2();
	}
	spriteActual->Advance();
	return true;

}

void LiuKang::_resetDuracion(){
	duracionPoder = 2;
}

void LiuKang::terminarPoder2(){
	spriteActual = sprites[SPRITE_INICIAL];
	m_yActual = m_yPiso;
	_resetDuracion();
	m_velocidadActual = 0;
	_estaHaciendoPoder = false;
	_estaAtacando = false;
	_estaSaltando = -1;
}

void LiuKang::poder2(){
	_cambiarSprite(SPRITE_PODER_2);
	m_yActual = m_yPiso - getAlto() - 10;
	float velocidad = 3 * m_velocidad;
	if (m_fliped){
		velocidad = - velocidad;
	}
	m_velocidadActual = velocidad;
	_estaAtacando = true;
	_estaSaltando = 1;
	_estaHaciendoPoder = true;
}

void LiuKang::fatality1(Personaje* elqueRecibe){
	if (_gano) return;
	_gano = true;
	_cambiarSprite(SPRITE_FATALITY_1);
	spriteActual->doLoop(true);
	spriteActual->freezeSprite();
	personajeQueRecibe = elqueRecibe;
	_estaHaciendoFatality = true;
	m_velocidadActual = 0;

}

void LiuKang::terminarAtaque(){
	if (_estaHaciendoPoder){
		terminarPoder2();
		m_velocidadActual = - m_velocidad;
		if (m_fliped) m_velocidadActual = m_velocidad;
		Saltar();
	}
}

void LiuKang::_resetPropio(){
	_estaHaciendoPoder = false;
	_estaHaciendoFatality = false;
	personajeQueRecibe = NULL;
	_resetDuracion();
}

LiuKang::~LiuKang() {
	// Llama automaticante al destructor de Personaje
}

} /* namespace std */
