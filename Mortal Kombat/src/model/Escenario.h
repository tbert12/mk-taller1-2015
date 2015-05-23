/*
 * Escenario.h
 *
 *  Created on: 22/5/2015
 *      Author: facu
 */

#ifndef SRC_MODEL_ESCENARIO_H_
#define SRC_MODEL_ESCENARIO_H_

#include "Capa.h"
#include "CapaPrincipal.h"
#include "Personaje.h"

class Escenario {
private:
	std::vector<Capa*> capas;
	CapaPrincipal* capaPrincipal;
	Personaje* PersonajeUno;
	Personaje* PersonajeDos;
public:
	Escenario();
	void addCapa(Capa* unaCapa);
	void addCapaPrincipal(CapaPrincipal* capa_principal,int index);
	void addPersonajes(Personaje* un_Personaje,Personaje* otro_Personaje);
	CapaPrincipal* getCapaPrincipal();
	std::vector<Capa*> getCapas();
	void Update();
	void render();
	virtual ~Escenario();
};

#endif /* SRC_MODEL_ESCENARIO_H_ */
