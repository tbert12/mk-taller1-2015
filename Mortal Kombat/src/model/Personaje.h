/*
 * Personaje.h
 *
 *  Created on: 26/3/2015
 *      Author: Facu
 */

#ifndef SRC_MODEL_PERSONAJE_H_
#define SRC_MODEL_PERSONAJE_H_

//Constants
const int SPRITE_INICIAL = 0;
const int SPRITE_CAMINAR_DERECHA = 1;
const int SPRITE_CAMINAR_IZQUIERDA = 2;
const int SPRITE_SALTO = 3;
const int SPRITE_SALTO_ANTES = 4;
const int SPRITE_SALTO_CAIDA = 5;
const int SPRITE_SALTO_DIAGONAL_ANTES_D = 6;
const int SPRITE_SALTO_DIAGONAL_DERECHA = 7;
const int SPRITE_SALTO_DIAGONAL_ANTES_I = 8;
const int SPRITE_SALTO_DIAGONAL_IZQUIERDA = 9;
const int SPRITE_AGACHARSE = 10;
const int SPRITE_AGACHADO = 11;
const int SPRITE_LEVANTARSE = 12;
const int SPRITE_PUNCHING = 13;
const int SPRITE_KICKING = 14;

const int VELOCIDAD_ADELANTE = 2.5;
const int VELOCIDAD_ATRAS = -2;

#include <stdio.h>
#include <iostream>
#include <vector>
#include "../view/Sprite.h"


class Personaje {
private:
	std::string nombre;
	float vida;
	float m_xActual;
	float m_yActual;
	float m_xInicial;
	float m_yInicial;
	short _estaSaltando;
	int _tDeSalto;

	float velocidadAdelante;
	float velocidadAtras;
	float m_velocidad;

	Sprite* spriteActual;
	std::vector<Sprite*> sprites;

	float m_AltoMundo;
	float m_AnchoMundo;

	void _cambiarSprite(int accion);

	void _SaltarHorizontal();
	void _SaltarDerecha();
	void _SaltarIzquierda();

	bool _estaAgachado();

	void _parabola();
	void _actualizarY();
	float _yDeSalto(float currentY, float currentT);

public:
	Personaje(std::string nombre_personaje,std::vector<Sprite*> Sprites,float velocidad);

	int estaScrolleando;

	std::vector<Sprite*> getSprites();
	Sprite* getSpriteActual();
	void AvanzarSprite();

	void renderizar(float ancho);

	void setPosition(float x, float y);
	void setDimensiones(float h, float w);
	float getX();
	float getY();
	float getVida();
	bool getSentidoDeMovimiento();
	void QuitarVida(int valor);

	void Inicial();
	void Frenar();
	void Saltar();
	void Agachar();
	void Levantarse();
	void CaminarDerecha();
	void CaminarIzquierda();

	virtual ~Personaje();
};

#endif /* SRC_MODEL_PERSONAJE_H_ */
