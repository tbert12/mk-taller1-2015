/*
 * Pelea.h
 *
 *  Created on: 20/5/2015
 *      Author: facu
 */

#ifndef SRC_MODEL_PELEA_H_
#define SRC_MODEL_PELEA_H_

#include "JugadorCPU.h"
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

#include "../view/TextosPelea.h"
#include "logging.h"

#define CICLOS_TEXTOS 50
#define CICLOS_FINAL_ROUND 70
#define CICLOS_FINISH_HIM 150
#define CICLOS_FATALITY 180
#define MODO_JUGADOR_VS_JUGADOR 0
#define MODO_JUGADOR_VS_PC 1
#define MODO_ENTRENAMIENTO 2

class Pelea {

private:
	Personaje* m_personajeUno;
	Personaje* m_personajeDos;
	Personaje* ganador;
	Personaje* perdedor;
	int ModoDeJuego;
	int tiempoRound;
	int NumeroRound;
	int ciclos_round_terminado;
	int ciclos_finish_him;
	int ciclos_render_texto;
	std::vector<int> GanadorRound;
	TextosPelea* textosPelea;
	bool round_finalizado;
	bool partida_finalizada;
	bool pelea_terminada;
	bool finish_him;
	bool fatality;
	bool comenzo_round;
	Tiempo* tiempo;
	Ventana* ventana;
	BarraEnergia* BarraPersonajeUno;
	BarraEnergia* BarraPersonajeDos;
	Escenario* escenario;
	TiempoPartida* tiempo_pantalla;
	CapaPrincipal* capaPrincipal;

	JugadorCPU* cpu = NULL;

	void _crearEstado();
	void _renderEstado();
	void _verificarColisiones();
	void _roundFinalizado();
	bool _partidaFinalizo();
	void _avanzarRound();
	void _resetRound();
	void _mostarGanadorRound();
	void _mostrarFinishHim();
	void _mostrarGanadorPelea();
	void _terminarRound();
	void _renderTextos();

public:
	Pelea(Ventana* la_ventana,Escenario* el_escenario,int un_tiempo, int modo_de_juego,TextosPelea* textos_pelea);
	void start();
	void render();
	bool ganoCpu();
	bool peleaFinalizada();
	bool roundFinalizado();
	bool inFinishHim();
	void setFatality();
	void setFinishHim();
	Personaje* getPersonajeUno();
	Personaje* getPersonajeDos();
	Personaje* getContrincante(Personaje* un_personaje);
	void reset();
	int modoDeJuego();
	int getModoDeJuego();
	virtual ~Pelea();
};

#endif /* SRC_MODEL_PELEA_H_ */
