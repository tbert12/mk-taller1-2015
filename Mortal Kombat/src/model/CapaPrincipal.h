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
const int COLISION_PERSONAJE_PERSONAJE_DEFENSA = 0;
const int COLISION_PERSONAJE_PERSONAJE_SIN_FLIP= 1;
const int COLISION_PERSONAJE_PERSONAJE_CON_FLIP= 2;
const int COLISION_PERSONAJE_OBJETO = 			 3;
const int COLISION_OBJETO_OBJETO = 				 4;

class CapaPrincipal: public Capa {

public:
	CapaPrincipal(float alto, float ancho, int zIndex, float anchoDeFondo,float ancho_ventana, float velocidadPrincipal, Personaje* personajeUno, Personaje* personajeDos);
	CapaPrincipal(float alto, float ancho, int zIndex, float anchoDeFondo,float ancho_ventana, float velocidadPrincipal, vector<Personaje*> personajes);
	int Scrollear(); //0 no scrollea , 1 para la derecha -1 para la izquierda!
	int CheckSegundoJugador(int estadoSegundoJugador);
	virtual ~CapaPrincipal();
	virtual void Renderizar();
	virtual void Update(int scroll);

private:
	int _NadieScrollea();
	Rect_Logico* rectAtaqueAnterior1;
	Rect_Logico* rectAtaqueAnterior2;
	Personaje* m_Personaje;
	Personaje* m_PersonajeDos;
	void _actualizarX();
	float m_velocidad_derecha;
	float m_velocidad_izquierda;
	int m_PersonajeQueScrollea; //0 no scrollea ninguno, 1 scrollea el 1, 2 el 2

	void _CheckearColisiones(Personaje*,Personaje*);
};


#endif /* SRC_MODEL_CAPAPRINCIPAL_H_ */
