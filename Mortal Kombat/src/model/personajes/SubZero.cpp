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
}

void SubZero::poder2(){
	_cambiarSprite(SPRITE_PODER_2);
	float velocidad = m_velocidad;
	if (m_fliped){
		velocidad = - velocidad;
	}
	m_velocidadActual = m_velocidad;
	_estaAtacando = true;

}

void SubZero::fatality1(Personaje* personajeQueRecibe){
	_cambiarSprite(SPRITE_FATALITY_1);

}

SubZero::~SubZero() {
	// Llama automaticante al destructor de Personaje
}

} /* namespace std */
