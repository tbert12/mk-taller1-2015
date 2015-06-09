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

}

void LiuKang::fatality1(Personaje* personajeQueRecibe){
	_cambiarSprite(SPRITE_FATALITY_1);
	spriteActual->doLoop(true);

}

LiuKang::~LiuKang() {
	// Llama automaticante al destructor de Personaje
}

} /* namespace std */
