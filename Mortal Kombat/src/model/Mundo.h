/*
 * Mundo.h
 *
 *  Created on: Apr 6, 2015
 *      Author: seba
 */

#ifndef SRC_MODEL_MUNDO_H_
#define SRC_MODEL_MUNDO_H_


#include "Personaje.h"
#include "Pelea.h"
#include "Escenario.h"
#include "../view/Ventana.h"
#include <vector>
#include <algorithm>
#include <unistd.h>
#include "logging.h"

class Mundo {
private:
	std::vector<Personaje*> personajes;
	std::vector<Escenario*> escenarios;
	Escenario* escenario_actual;
	Pelea* pelea;
	Ventana* ventana;
	bool empezar;
	int tiempo_round;
	void start();
	void _mostrar_ganador(string nombre);
public:
	bool partida_finalizada;

	Mundo(Ventana* una_ventana,int tiempo_round);
	void addPersonaje(Personaje* un_personaje);
	std::vector<Personaje*> getPersonajes();
	void addEscenario(Escenario* un_escenario);
	Ventana* getVentana();
	void render();
	virtual ~Mundo();
};

#endif /* SRC_MODEL_MUNDO_H_ */
