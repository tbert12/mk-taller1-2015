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
#include <vector>
#include "../view/Sprite.h"


class Personaje {
private:
	std::string nombre;
	int vida;
	int m_xActual;
	unsigned int spriteActual;
	std::vector<Sprite*> sprites;

	void _cambiarSprite(unsigned int accion);

public:
	Personaje(std::string nombre_personaje,std::vector<Sprite*> Sprites);

	std::vector<Sprite*> getSprites();
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
