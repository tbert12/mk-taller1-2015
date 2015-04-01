/*
 * Personaje.h
 *
 *  Created on: 26/3/2015
 *      Author: Facu
 */

#ifndef SRC_MODEL_PERSONAJE_H_
#define SRC_MODEL_PERSONAJE_H_

#include <stdio.h>
#include <iostream>
#include "../view/Sprite.h"


class Personaje {
private:
	std::string nombre;
	int vida;
	//std::list<std::string> sprites;
	std::string sprites;
	int m_xActual;
	unsigned int spriteActual;
	Sprite** sprites;

	void _cambiarSprite(unsigned int accion);

public:
	Personaje(std::string nombre_personaje,Sprite** Sprites);

	Sprite** getSprites();
	Sprite* getSpriteActual();

	int getX();
	int Vida();
	void QuitarVida(int valor);

	void Inicial();
	void Saltar();
	void Agachar();
	void CaminarDerecha();
	void CaminarIzquierda();
	void SaltarDerecha();
	void SaltarIzquierda();

	virtual ~Personaje();
};

#endif /* SRC_MODEL_PERSONAJE_H_ */
