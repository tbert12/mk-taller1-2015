/*
 * JugadorCPU.h
 *
 *  Created on: 5/6/2015
 *      Author: buby
 */

#ifndef SRC_MODEL_JUGADORCPU_H_
#define SRC_MODEL_JUGADORCPU_H_

#include "Personaje.h"

const int DISTANCIA_PINA = 120;
const int DISTANCIA_PATADA = 130;
const int DISTANCIA_TOMA = 120;

class JugadorCPU {
public:
	JugadorCPU(Personaje* personaje_cpu, Personaje* personaje_1);
	virtual ~JugadorCPU();

	void realizarMovimiento();

private:
	Personaje* m_personaje_1;
	Personaje* m_personaje_cpu;
	int m_id_personaje;
	int m_agresividad = 1;
	int m_ciclos_delay = 0;

	bool reaccion(int probabilidad);

	void evaluarAgresividad();

	bool noHayQueHacerNada();

	bool hayQueCubrirse();
	bool hayQueSaltar();
	bool hayQueAgacharse();
	bool hayQueAvanzar();
	bool hayQueRetroceder();

	bool hayQuePegarPina();
	bool hayQuePegarPatada();
	bool hayQuePegarArriba();
	bool hayQuePegarAbajo();
	bool hayQueLanzarPoder();
	bool hayQueHacerToma();

	bool hayQueHacerFatality();

};

#endif /* SRC_MODEL_JUGADORCPU_H_ */
