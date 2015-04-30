/*
 * Personaje.h
 *
 *  Created on: 26/3/2015
 *      Author: Facu
 */

#ifndef SRC_MODEL_PERSONAJE_H_
#define SRC_MODEL_PERSONAJE_H_

//Constants
const int SPRITE_INICIAL=         0;
const int SPRITE_CAMINAR=         1;
const int SPRITE_SALTAR=          2;
const int SPRITE_SALTAR_DIAGONAL= 3;
const int SPRITE_AGACHAR=         4;
const int SPRITE_PATADA_ALTA_AGACHADO=  5;
const int SPRITE_PATADA_BAJA_AGACHADO=  6;
const int SPRITE_CUBRIRSE=        9;
const int SPRITE_CUBRIRSE_AGACHADO=    10;
const int SPRITE_GANCHO=         12;
const int SPRITE_PATADA_ALTA=    14;
//const int SPRITE_PATADA_BAJA=    15;
const int SPRITE_PATADA_CIRCULAR=15;
const int SPRITE_PATADA_SALTANDO=16;
const int SPRITE_PINA_AGACHADO=  17;
const int SPRITE_PINA_ALTA=		 18;
const int SPRITE_PINA_BAJA=		 19;
const int SPRITE_PINA_SALTANDO=  20;

const int TIEMPOTOTALDESALTO = 14;

#include <stdio.h>
#include <iostream>
#include <vector>
#include "../view/Sprite.h"


class Personaje {
private:
	std::string nombre;

	int vida;

	float m_xActual;
	float m_yActual;
	float m_yPiso;

	bool m_fliped;

	float maxAlturaDeSalto;
	int tiempoDeSalto;
	// 0 Cae del Salto, 1 Saltando, -1 No esta Saltanto
	short _estaSaltando;

	bool _estaCubriendose;
	bool _estaAgachado;

	float m_velocidad;
	float m_velocidadActual;

	float m_AltoMundo;
	float m_AnchoMundo;

	Sprite* spriteActual;
	std::vector<Sprite*> sprites;

	void _cambiarSprite(int accion);

	void _SaltarHorizontal();
	void _SaltarDerecha();
	void _SaltarIzquierda();


	void _parabola();
	void _actualizarY();
	float _yDeSalto(float currentY, float currentT);

	void _pinaSaltando();
	void _patadaSaltando();

	void _pinaAgachado();
	void _gancho();

	void _patadaAltaAgachado();
	void _patadaBajaAgachado();

	void _patadaCircular();

	void _cubrirseAgachado();
	void _cubrirseParado();

public:
	Personaje(std::string nombre_personaje,std::vector<Sprite*> Sprites,float velocidad, bool fliped = false);

	std::vector<Sprite*> getSprites();
	Sprite* getSpriteActual();
	void AvanzarSprite();

	bool enMovimiento();

	void Update(int velocidadScroll);
	void renderizar(float x_dist_ventana, float posOtherPlayer);

	void setPosition(float x, float y);
	void setDimensionesMundo(float h, float w);

	int getSentidoDeMovimiento();
	float getVelocidadDerecha();
	float getVelocidadIzquierda();

	void QuitarVida(int valor);
	int getVida();

	string getNombre();
	float getAncho();
	float getAlto();
	float getX();
	float getY();

	bool estaAgachado();

	void Inicial();
	void Frenar();
	void Saltar();
	void Agachar();
	void Levantarse();
	void CaminarDerecha();
	void CaminarIzquierda();
	void pinaBaja();
	void pinaAlta();
	void patadaBaja();
	void patadaAlta();
	void cubrirse();
	void dejarDeCubrirse();

	virtual ~Personaje();
};

#endif /* SRC_MODEL_PERSONAJE_H_ */
