/*
 * CapaPrincipal.h
 *
 *  Created on: Mar 28, 2015
 *      Author: root
 */

#ifndef SRC_MODEL_CAPAPRINCIPAL_H_
#define SRC_MODEL_CAPAPRINCIPAL_H_

#include "Capa.h"
#include "Personaje.h"
#include <SDL2/SDL.h>

//Constants
const int COLISION_NO_COLISION = 				-1;
const int COLISION_PERSONAJE_PERSONAJE_DEFENSA = 0;
const int COLISION_PERSONAJE_PERSONAJE_SIN_FLIP= 1;
const int COLISION_PERSONAJE_PERSONAJE_CON_FLIP= 2;
const int COLISION_PERSONAJE_OBJETO_SIN_FLIP =	 3;
const int COLISION_PERSONAJE_OBJETO_CON_FLIP =	 4;
const int COLISION_OBJETO_OBJETO = 				 5;

const float PERSONAJE_POS_RESPECTO_CAM_UNO = 0.8;
const float PERSONAJE_POS_RESPECTO_CAM_DOS = 0.5;

class CapaPrincipal: public Capa {

public:
	CapaPrincipal(float alto, float ancho, int zIndex, float anchoDeFondo,float ancho_ventana, float velocidadPrincipal, float pos_piso);
	int Scrollear(); //0 no scrollea , 1 para la derecha -1 para la izquierda!
	void addPersonajes(Personaje* uno,Personaje* dos);
	Personaje* getPersonajSinFlip();
	Personaje* getPersonajConFlip();
	int CheckearColisiones();

	virtual ~CapaPrincipal();
	virtual void Renderizar();
	virtual void Update(int scroll);
	virtual void reset();


private:
	int _scroll;
	float pos_inicial_personajeUno;
	float pos_inicial_personajeDos;
	float pos_inicial_piso;

	int _NadieScrollea();
	Rect_Logico* rectAtaqueAnterior1;
	Rect_Logico* rectAtaqueAnterior2;
	Personaje* m_PersonajeUno;
	Personaje* m_PersonajeDos;
	Personaje* m_personajeSinFlip;
	Personaje* m_personajeConFlip;
	void _actualizarX();
	float m_velocidad_derecha;
	float m_velocidad_izquierda;
	int m_PersonajeQueScrollea; //0 no scrollea ninguno, 1 scrollea el 1, 2 el 2

	void _ChequearSiSePisan();
	int _getIdDePersonaje(Personaje* personaje_a_ver);
	int CheckSegundoJugador(int estadoSegundoJugador);
	int _CheckearColisiones(Personaje*,Personaje*);
	void _LateUpdate();
};


#endif /* SRC_MODEL_CAPAPRINCIPAL_H_ */
