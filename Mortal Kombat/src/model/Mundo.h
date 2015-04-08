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
#include "CapaFondo.h"
#include "Personaje.h"
#include "../view/Sprite.h"
#include "../view/Frame.h"
#include "Escenario.h"
#include "../view/Ventana.h"
#include <vector>


class Mundo {
private:
	float ratio_x;
	float ratio_y;
	std::vector<Capa*> capas;
	std::vector<Personaje*> personajes;
	Tiempo* tiempo;
	Escenario* escenario;
	Ventana* ventana; //tiene el renderer

public:
	Mundo(float ratioX,float ratioY);
	bool addPersonaje(Personaje* un_personaje);
	Personaje* getPersonaje(int indice = 0);
	bool addCapa(Capa* unaCapa);
	Capa* getCapa(int indice = 0);
	void setTiempo(Tiempo* unTiempo);
	void setVentana(Ventana* unaVentana);
	Ventana* getVentana();
	void setEscenario(Escenario* unEscenario);
	Escenario* getEscenario();
	void render();
	virtual ~Mundo();
};

#endif /* SRC_MODEL_MUNDO_H_ */
