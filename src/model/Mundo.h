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
#include "../controller/Controller.h"
#include "../controller/ComboController.h"
#include "../controller/Combo.h"
#include "../view/BotonesPantalla.h"
#include "../view/TextosPelea.h"
#include <vector>
#include <algorithm>
#include <unistd.h>
#include "logging.h"

class Mundo {
private:
	map<string, int>* mapa_comandos1;
	map<string, int>* mapa_comandos2;
	int ModoDeJuego;
	int tiempoMax,tolerancia;
	int escenario_anterior;
	std::vector<Personaje*> personajes;
	std::vector<Escenario*> escenarios;
	Escenario* escenario_actual;
	Pelea* pelea;
	Ventana* ventana;
	TextosPelea* textosPelea;
	Personaje* Personaje_uno;
	Personaje* Personaje_dos;
	bool empezar;
	int tiempo_round;
	Controller* control;
	BotonesPantalla* botones_pantalla;
	void start();
	void _mostrar_ganador(string nombre);
public:
	Mundo(Ventana* una_ventana,int tiempo_round,map<string, int>* mapaComan1,map<string, int>* mapaComan2,int tiempoMax,int tolerancia);
	void addPersonaje(Personaje* un_personaje);
	void addPersonajes(vector<Personaje*> nuevos_personajes);
	std::vector<Personaje*> getPersonajes();
	Personaje* getPersonajeUno();
	Personaje* getPersonajeDos();
	void addEscenario(Escenario* un_escenario);
	void addEscenarios(vector<Escenario*> nuevos_escenarios);
	Ventana* getVentana();
	void setModoDeJuego(int modo);
	void setTextosPelea(TextosPelea* un_text);
	void setPersonajesDeJuego(Personaje* p_uno, Personaje* p_dos);
	void render();
	bool ganoCPU();
	bool Quit();
	bool Pausa();
	int getSleep();
	bool Fin();
	void reset();
	virtual ~Mundo();
};

#endif /* SRC_MODEL_MUNDO_H_ */
