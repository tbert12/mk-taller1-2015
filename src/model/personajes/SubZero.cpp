/*
 * SubZero.cpp
 *
 *  Created on: 8/6/2015
 *      Author: tomi
 */

#include "SubZero.h"

namespace std {

SubZero::SubZero(string nombre_personaje,vector<Sprite*> Sprites,vector<ObjetoArrojable*> arrojables ,float velocidad, bool fliped)
:Personaje(nombre_personaje,Sprites,arrojables,velocidad,fliped){
	_estaHaciendoPoder = false;
	_estaHaciendoFatality = false;
	_pararDeRetrocederFatality1 = false;
}

int SubZero::_getaccionPropia(){
	if (_estaHaciendoPoder) {
		if (spriteActual->proxFrameUltimo()) return SPRITE_GANCHO;
		return SPRITE_PATADA_ALTA;
	}
	return 0;
}

bool SubZero::_updatePropio(){
	if (!_estaHaciendoPoder and !_estaHaciendoFatality and !_estaHaciendoFatality2) return false;
	if (_estaHaciendoPoder)
		_updatePoder2();
	else if (_estaHaciendoFatality)
		_updateFatality1();
	else if (_estaHaciendoFatality2)
		_updateFatality2();
	spriteActual->Advance();
	return true;
}

void SubZero::_updatePoder2(){
	if ( spriteActual->ultimoFrame() and _estaHaciendoPoder){
		m_velocidadActual = 0;
		_cambiarSprite(SPRITE_INICIAL);
		_estaHaciendoPoder = false;
		_estaAtacando = false;
		_estaSaltando = false;
	}
}

void SubZero::_updateFatality1(){
	if (spriteActual->inLoop()){
		_pararDeRetrocederFatality1 = true;
		spriteActual->retrocederFrames(3);
	}
	if (!_pararDeRetrocederFatality1){
		m_yActual = m_yActual - 3;
	}
}

void SubZero::poder2(){
	_cambiarSprite(SPRITE_PODER_2);
	spriteActual->freezeSprite();
	float velocidad = 0.2*m_velocidad;
	if (m_fliped){
		velocidad = - velocidad;
	}
	m_velocidadActual = velocidad;
	_estaSaltando = 1;
	_estaAtacando = true;
	_estaHaciendoPoder = true;

}

void SubZero::fatality1(Personaje* personajeQueRecibe){
	if (_gano) return;
	_cambiarSprite(SPRITE_FATALITY_1);
	spriteActual->doLoop(true);
	_estaHaciendoFatality = true;
	m_yActual = m_yPiso;
	m_velocidadActual = 0;
	_gano = true;
	personajeQueRecibe->morir();

}

void SubZero::terminarAtaque(){}

void SubZero::_resetPropio(){
	_estaHaciendoPoder = false;
	_estaHaciendoFatality = false;
	_pararDeRetrocederFatality1 = false;
}

SubZero::~SubZero() {
	// Llama automaticante al destructor de Personaje
}

} /* namespace std */
