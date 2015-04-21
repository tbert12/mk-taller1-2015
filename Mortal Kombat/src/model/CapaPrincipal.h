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

class CapaPrincipal: public Capa {

public:
	CapaPrincipal(float alto, float ancho, int zIndex, float anchoDeFondo,float ancho_ventana, float velocidadPrincipal, Personaje* personaje);
	CapaPrincipal(float alto, float ancho, int zIndex, float anchoDeFondo,float ancho_ventana, float velocidadPrincipal, Personaje* personajeUno, Personaje* personajeDos);
	int Scrollear(); //0 no scrollea , 1 para la derecha -1 para la izquierda!
	virtual ~CapaPrincipal();
	virtual void Renderizar();
	//virtual void Mover(bool right);

private:
	Personaje* m_Personaje;
	Personaje* m_PersonajeDos;
	void _actualizarX();
	float m_velocidad_derecha;
	float m_velocidad_izquierda;
};


#endif /* SRC_MODEL_CAPAPRINCIPAL_H_ */
