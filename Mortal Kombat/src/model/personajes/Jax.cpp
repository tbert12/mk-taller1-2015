/*
 * Jax.cpp
 *
 *  Created on: 10/6/2015
 *      Author: tomi
 */

#include "Jax.h"

namespace std {

Jax::Jax(string nombre_personaje,vector<Sprite*> Sprites,vector<ObjetoArrojable*> arrojables ,float velocidad, bool fliped)
:Personaje(nombre_personaje,Sprites,arrojables,velocidad,fliped){
	_estaHaciendoPoder = false;
	_estaHaciendoFatality = false;
	personajeQueRecibe = NULL;
}

int Jax::_getaccionPropia(){
	if (!_estaHaciendoPoder) return 0;
	return SPRITE_PATADA_SALTANDO;
}

bool Jax::_updatePropio(){
	//Retorna true si lo que esta haciendo NO es un poder propio
	if ( !_estaHaciendoPoder and !_estaHaciendoFatality and !_estaHaciendoFatality2) return false;
	if ( spriteActual->ultimoFrame() ){
		//Programar Poder Propio
	} else if (_estaHaciendoFatality){
		//Programar Fatality

	} else if (_estaHaciendoFatality2){
		_updateFatality2();
	}
	spriteActual->Advance();
	return true;

}

void Jax::terminarPoder2(){
	spriteActual = sprites[SPRITE_INICIAL];
	m_yActual = m_yPiso;
	m_velocidadActual = 0;
	_estaHaciendoPoder = false;
	_estaAtacando = false;
	_estaSaltando = -1;
}

void Jax::poder2(){
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

void Jax::fatality1(Personaje* elqueRecibe){
	if (_gano) return;
	_gano = true;
	_cambiarSprite(SPRITE_FATALITY_1);
	spriteActual->doLoop(true);
	spriteActual->freezeSprite();
	personajeQueRecibe = elqueRecibe;
	_estaHaciendoFatality = true;
	m_velocidadActual = 0;

}

void Jax::terminarAtaque(){
	if (_estaHaciendoPoder){
		terminarPoder2();
		m_velocidadActual = - m_velocidad;
		if (m_fliped) m_velocidadActual = m_velocidad;
		Saltar();
	}
}

void Jax::_resetPropio(){
	_estaHaciendoPoder = false;
	_estaHaciendoFatality = false;
	personajeQueRecibe = NULL;
}
Jax::~Jax() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
