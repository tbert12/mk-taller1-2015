/*
 * Pelea.h
 *
 *  Created on: 20/5/2015
 *      Author: facu
 */

#ifndef SRC_MODEL_PELEA_H_
#define SRC_MODEL_PELEA_H_

#include "Tiempo.h"
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

class Pelea {

private:
	Personaje* m_personajeUno;
	Personaje* m_personajeDos;
	Personaje* ganador;
	int tiempoRound;
	int NumeroRound;
	std::vector<int> GanadorRound;
	bool round_finalizado;
	bool partida_finalizada;
	bool comenzo_pelea;
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

public:
	Pelea(Ventana* la_ventana,Personaje* personaje1,Personaje* personaje2,int un_tiempo,std::vector<Capa*> las_capas,CapaPrincipal* capa_principal);
	void start();
	void render();
	bool peleaFinalizada();
	virtual ~Pelea();
};

#endif /* SRC_MODEL_PELEA_H_ */
