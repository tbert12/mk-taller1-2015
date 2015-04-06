/*
 * Mundo.h
 *
 *  Created on: Apr 6, 2015
 *      Author: seba
 */

#ifndef SRC_MODEL_MUNDO_H_
#define SRC_MODEL_MUNDO_H_

#include "Tiempo.h"
#include "../view/LTexture.h"
#include "Capa.h"
#include "CapaPrincipal.h"
#include "Personaje.h"
#include "../view/Sprite.h"
#include "../view/Frame.h"
#include "Escenario.h"
#include "Ventana.h"


class Mundo {
public:
	Mundo();
	virtual ~Mundo();

	float ratio_x;
	float ratio_y;
	Capa** capas;
	Personaje** personajes;
	Tiempo* tiempo;
	Escenario* escenario;
	Ventana* ventana; //tiene el renderer
};

#endif /* SRC_MODEL_MUNDO_H_ */
