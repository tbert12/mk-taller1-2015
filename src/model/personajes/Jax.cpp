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
	return SPRITE_TOMA_1;
}

bool Jax::_updatePropio(){
	//Retorna true si lo que esta haciendo NO es un poder propio
	if ( !_estaHaciendoPoder and !_estaHaciendoFatality and !_estaHaciendoFatality2) return false;
	if (_estaHaciendoPoder){
		if ( spriteActual->inFrezee() ){
			if (!poderes[1]->getVida()){
				poderes[1]->lanzar(getX(),m_yPiso,m_fliped);
			} else {
				//Lean aca, ya sale pero no detecta la colision
				//La capa principal no debe saber que esta el poder
				poderes[1]->destruir();
			}
		} else {
			terminarPoder2();
		}
	} else if (_estaHaciendoFatality){
		//Programar Fatality

	} else if (_estaHaciendoFatality2){
		_updateFatality2();
	}
	spriteActual->Advance();
	return true;

}

void Jax::terminarPoder2(){
	if (!spriteActual->ultimoFrame()) return;
	spriteActual = sprites[SPRITE_INICIAL];
	_estaHaciendoPoder = false;
	_estaAtacando = false;
}

void Jax::poder2(){
	_cambiarSprite(SPRITE_PODER_2);
	spriteActual->freezeSprite();
	m_velocidadActual = 0;
	m_proximaVelocidad = 0;
	_estaAtacando = true;
	_estaHaciendoPoder = true;
}

void Jax::fatality1(Personaje* elqueRecibe){
	if (_gano) return;
	_gano = true;
	return;

}

void Jax::terminarAtaque(){
	if (_estaHaciendoPoder){
		terminarPoder2();
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
