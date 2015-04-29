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
const int SPRITE_PATADA_CIRCULAR=15;
const int SPRITE_PATADA_SALTANDO=16;
const int SPRITE_PINA_AGACHADO=  17;
const int SPRITE_PINA_ALTA=		 18;
const int SPRITE_PINA_BAJA=		 19;
const int SPRITE_PINA_SALTANDO=  20;

const int TIEMPOTOTALDESALTO = 8;

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
	float maxAlturaDeSalto;
	int tiempoDeSalto;
	short _estaSaltando;
	bool m_fliped;
	bool sigueAgachado;
	bool estaAtacando;
	bool estaCubriendose;

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

	void _pinaSaltando();
	void _pinaAgachado();
	void _gancho();
	void _patadaSaltando();
	void _patadaAltaAgachado();
	void _patadaBajaAgachado();


public:
	Personaje(std::string nombre_personaje,std::vector<Sprite*> Sprites,float velocidad, bool fliped = false);

	std::vector<Sprite*> getSprites();
	Sprite* getSpriteActual();
	void AvanzarSprite();
	bool enMovimiento();
	void Update(int velocidadScroll);
	void renderizar(float x_dist_ventana, float posOtherPlayer);

	void colorAlternativo(SDL_PixelFormat* format, float h_inicial, float h_final, float desplazamiento);

	void setPosition(float x, float y);
	void setDimensionesMundo(float h, float w);
	float getX();
	float getY();
	float getVida();
	int getSentidoDeMovimiento();
	float getVelocidadDerecha();
	float getVelocidadIzquierda();
	void QuitarVida(int valor);
	std::string getNombre();
	float getAncho();
	float getAlto();

	void Inicial();
	void Frenar();
	void Saltar();
	void Agachar();
	void Levantarse();
	void sacarGuardia();
	void CaminarDerecha();
	void CaminarIzquierda();
	void pinaBaja();
	void pinaAlta();
	void patadaBaja();
	void patadaAlta();
	void patadaCircular();
	void cubrirse();
	void cubrirseAgachado();

	virtual ~Personaje();
};

#endif /* SRC_MODEL_PERSONAJE_H_ */
