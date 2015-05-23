/*
 * Pelea.h
 *
 *  Created on: 20/5/2015
 *      Author: facu
 */

#ifndef SRC_MODEL_PELEA_H_
#define SRC_MODEL_PELEA_H_

#include "Tiempo.h"
#include "Escenario.h"
#include "Capa.h"
#include "CapaPrincipal.h"
#include "Personaje.h"
#include "ObjetoArrojable.h"
#include "../view/Ventana.h"
#include "../view/BarraEnergia.h"
#include "../view/TiempoPartida.h"
#include <vector>
#include <algorithm>
#include <unistd.h>
#include "logging.h"

#define CICLOS_FINAL_ROUND 70

class Pelea {

private:
	Personaje* m_personajeUno;
	Personaje* m_personajeDos;
	Personaje* ganador;
	int tiempoRound;
	int NumeroRound;
	int ciclos_round_terminado;
	std::vector<int> GanadorRound;
	bool round_finalizado;
	bool partida_finalizada;
	bool comenzo_round;
	Tiempo* tiempo;
	Ventana* ventana;
	BarraEnergia* BarraPersonajeUno;
	BarraEnergia* BarraPersonajeDos;
	std::vector<Capa*> capas;
	TiempoPartida* tiempo_pantalla;
	CapaPrincipal* capaPrincipal;

	void _crearEstado();
	void _renderEstado();
	void _verificarColisiones();
	void _roundFinalizado();
	void _partidaFinalizada();
	void _resetRound();
	void _mostarGanadorRound();

public:
	Pelea(Ventana* la_ventana,Escenario* el_escenario,int un_tiempo);
	void start();
	void render();
	bool peleaFinalizada();
	virtual ~Pelea();
};

#endif /* SRC_MODEL_PELEA_H_ */
