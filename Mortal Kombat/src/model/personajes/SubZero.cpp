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
}

int SubZero::_getaccionPropia(){
	if (_estaHaciendoPoder) {
		if (spriteActual->proxFrameUltimo()) return SPRITE_GANCHO;
		return SPRITE_PATADA_ALTA;
	}
	return 0;
}

bool SubZero::_updatePropio(){
	if (!_estaHaciendoPoder) return false;
	if (!_estaHaciendoFatality) return false;
	if ( spriteActual->ultimoFrame() and _estaHaciendoPoder){
		m_velocidadActual = 0;
		_cambiarSprite(SPRITE_INICIAL);
		_estaHaciendoPoder = false;
		_estaAtacando = false;
		_estaSaltando = false;
	}
	spriteActual->Advance();
	return true;
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
	_cambiarSprite(SPRITE_FATALITY_1);
	_estaHaciendoFatality = true;

}

void SubZero::terminarAtaque(){}

SubZero::~SubZero() {
	// Llama automaticante al destructor de Personaje
}

} /* namespace std */
