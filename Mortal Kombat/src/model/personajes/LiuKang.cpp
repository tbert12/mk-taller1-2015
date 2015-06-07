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
	maxAlturaDeSalto = getAlto();
	tiempoDeSalto = 1;
	_estaSaltando = 1;
	float velocidad = 3 * m_velocidad;
	if (m_fliped){
		velocidad = - velocidad;
	}
	m_velocidadActual = 3 * m_velocidad;
	_estaAtacando = true;

}

void LiuKang::fatality1(Personaje* personajeQueRecibe){

}

LiuKang::~LiuKang() {
}

} /* namespace std */
