/*
 * Personaje.h
 *
 *  Created on: 26/3/2015
 *      Author: Facu
 */

#ifndef SRC_MODEL_PERSONAJE_H_
#define SRC_MODEL_PERSONAJE_H_

//Constants
const int SPRITE_PARADO = 0;
const int SPRITE_CAMINAR = 1;
const int SPRITE_CAMINAR_ATRAS = 2;
const int SPRITE_SALTO = 3;
const int SPRITE_SALTO_DIAGONAL = 4;
const int SPRITE_PUNCHING = 5;
const int SPRITE_KICKING = 6;

#include <stdio.h>
#include <iostream>
#include <vector>
#include "../view/Sprite.h"
#include "Accion.h"


class Personaje {
private:
	std::string nombre;
	int vida;
	int m_xActual;
	int m_yActual;
	unsigned int spriteActual;
	std::vector<Sprite*> sprites;
	float m_velocidad;

	void _cambiarSprite(Accion* accion);

public:
	Personaje(std::string nombre_personaje,std::vector<Sprite*> Sprites, int velocidad);

	int estaScrolleando;
	std::vector<Sprite*> getSprites();
	Sprite* getSpriteActual();

	int getX();
	int getY();
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
