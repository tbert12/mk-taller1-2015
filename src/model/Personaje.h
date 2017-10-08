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
#include <map>
#include "../view/Sprite.h"
#include "ObjetoArrojable.h"
#include "ObjetoDroppable.h"
#include "../controller/Combo.h"


//Constants
const int SPRITE_INICIAL=         		0;
const int SPRITE_CAMINAR=         		1;
const int SPRITE_SALTAR=          		2;
const int SPRITE_SALTAR_DIAGONAL= 		3;
const int SPRITE_AGACHAR=         		4;
const int SPRITE_PATADA_ALTA_AGACHADO=  5;
const int SPRITE_PATADA_BAJA_AGACHADO=  6;
const int SPRITE_RECIBE_PATADA_GIRA=    7;
const int SPRITE_RECIBE_GANCHO = 		8; //CaeYSeLevanta
const int SPRITE_CUBRIRSE=       		9;
const int SPRITE_CUBRIRSE_AGACHADO=    	10;
const int SPRITE_GANA =					11;
const int SPRITE_GANCHO=         		12;
const int SPRITE_MUERE=					13;
const int SPRITE_PATADA_ALTA=			14;
const int SPRITE_PATADA_BAJA=    		15;
const int SPRITE_PATADA_CIRCULAR=		16;
const int SPRITE_PATADA_SALTANDO=		17;
const int SPRITE_PINA_AGACHADO=  		18;
const int SPRITE_PINA_ALTA=		 		19;
const int SPRITE_PINA_BAJA=		 		20;
const int SPRITE_PINA_SALTANDO=  		21;
const int SPRITE_RECIBE_AGACHADO =      22;
const int SPRITE_RECIBE_ALTO = 			23;
const int SPRITE_RECIBE_BAJO =			24;
const int SPRITE_RECIBE_FUERTE = 		25;
const int SPRITE_COMBO_PINA_BAJA =		26;
const int SPRITE_COMBO_PINA_ALTA =		27;
const int SPRITE_TOMA_1 =				28;
const int SPRITE_PODER_1 =				29;
const int SPRITE_PODER_2 =				30;
const int SPRITE_FINISH =				31;
const int SPRITE_FATALITY_1 =			32;
const int SPRITE_ES_TOMADO =			33;
const int SPRITE_BEBE =					34;
const int SPRITE_FATALITY_GANCHO =		35;

const int GOLPE_DE_PODER = 				-1;

const int QUITAR_VIDA_GOLPE_BAJO = 3;
const int QUITAR_VIDA_GOLPE_ALTO = 4;
const int QUITAR_VIDA_PATADA_CIRCULAR = 5;
const int QUITAR_VIDA_GANCHO = 8;

const int MIN_GOLPE_FUERTE = 4;

const int TIEMPOTOTALDESALTO = 15;
const float ALTURA_SALTO_GANCHO = 1.8; //Proporcion a la altura logica del personaje
const float ALTURA_SALTO_DIAG=    1.2;


class Personaje {
protected:

	void _cambiarSprite(int accion);
	float m_velocidad;
	float m_xAnterior;
	float m_velocidadActual;
	float m_proximaVelocidad;
	bool m_fliped;
	bool _estaAtacando;

	/* Logica de Salto */
	float maxAlturaDeSalto;
	int tiempoDeSalto;
	// 0 Cae del Salto, 1 Saltando, -1 No esta Saltanto
	short _estaSaltando;

	std::string nombre;
	std::string nombreDeCarga;
	std::string logo;

	int vida;

	float m_xActual;
	float m_yActual;
	float m_yPiso;
	float m_AltoMundo;
	float m_AnchoMundo;

	bool m_mover;
	bool nextFlip;

	bool _estaCubriendose;
	bool _estaAgachado;
	bool _recibioGolpe;

	int m_cant_pinas = 0;

	bool _estaMuerto;
	bool _gano;

	std::vector<Combo*> mCombos;

	Rect_Logico* m_rectanguloAtaque;
	Rect_Logico* m_rectanguloDefensa;

	Sprite* spriteActual;
	std::vector<Sprite*> sprites;
	std::vector<ObjetoArrojable*> poderes;
	std::vector<ObjetoDroppable*> mObjetos;

	void _UpdatePoder();
	virtual bool _updatePropio();

	virtual int _getaccionPropia();

	void _Caminar(bool derecha);

	void _SaltarHorizontal();

	/* Salto Diagonal*/
	void _SaltarDerecha();
	void _SaltarIzquierda();
	void _parabola();
	void _actualizarY();
	float _yDeSalto(float currentY, float currentT);

	/*Ataque*/
	void _pina(int sprite,int spriteCombo);
	void _pinaSaltando();
	void _patadaSaltando();

	void _pinaAgachado();
	void _gancho();

	void _patadaAltaAgachado();
	void _patadaBajaAgachado();

	void _patadaCircular();

	/*Defensa*/
	void _cubrirseAgachado();
	void _cubrirseParado();

	virtual void _resetPropio();

	//Fatality universal del gancho
	bool _estaHaciendoFatality2;
	void _updateFatality2();
	void _recibirFatality2();
	void _arrancarCabeza();
	Personaje* personajeQueLaRecibe;



public:
	Personaje(std::string nombre_personaje,std::vector<Sprite*> Sprites, std::vector<ObjetoArrojable*> arrojables,float velocidad, bool fliped = false);
	virtual ~Personaje();
	/* Solo para el Menu de Opciones */
	Personaje* copy();

	void Update(float posOtroJugador,bool forzado = false);
	void renderizar(float x_dist_ventana,float posOtherPlayer);
	void reset();

	void AvanzarSprite();

	Rect_Logico* rectanguloAtaque();
	Rect_Logico* rectanguloDefensa();

	void setNombre(std::string);
	void setCombos( std::vector<Combo*> );
	void setPosition(float x, float y);
	void setPositionX(float x);
	void setDimensionesMundo(float h, float w);
	void setScroll(bool scrollear);
	void setFlip(bool flip);
	void setPathLogo(std::string ruta);
	void setObjetos(std::vector<ObjetoDroppable*> objetos);

	std::vector<Combo*> getCombos();
	ObjetoArrojable* getPoderActivo();
	string getPathLogo();
	string getNombre();
	string getNombreDeCarga();
	float getVelocidadDerecha();
	float getVelocidadIzquierda();
	float getVelocidad();
	float getAncho();
	float getAlto();
	float getX();
	float getY();
	bool getFlipState();
	int getVida();
	int getSentidoDeMovimiento();
	int getAccionDeAtaque();

	bool estaAgachado();
	bool estaSaltando();
	bool estaCubriendose();
	bool estaAtacando();
	bool estaMuerto();
	bool enMovimiento();

	void Inicial();
	bool recibirGolpe(int CodigoGolpe, int Danio = 0);
	void QuitarVida(int valor);


	//Acciones para controlador
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
	void lanzarObjeto();

	virtual void terminarAtaque();

	void toma1();  /* Toma clasica que lo lanza para tras */
	void poder1(); /* Relacionado a lanzar un objeto */

	/* Cada personaje tiene el suyo */
	virtual void poder2();
	virtual void fatality1(Personaje* otroPersonaje);

	/* Fatalityes universales */
	void fatality2(Personaje* otroPersonaje);
	void babality(Personaje* otroPersonaje);

	void finishHim();
	void morir();
	void victoria();
};

#endif /* SRC_MODEL_PERSONAJE_H_ */
