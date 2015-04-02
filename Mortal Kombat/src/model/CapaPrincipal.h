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
	CapaPrincipal(int alto, int ancho, int zIndex, int anchoDeFondo, float velocidadPrincipal, Personaje* personaje);
	bool Scrollear();
	virtual ~CapaPrincipal();
	virtual void Renderizar();

private:
	Personaje* m_Personaje;
};


#endif /* SRC_MODEL_CAPAPRINCIPAL_H_ */
