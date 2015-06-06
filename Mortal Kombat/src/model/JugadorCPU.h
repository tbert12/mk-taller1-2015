/*
 * JugadorCPU.h
 *
 *  Created on: 5/6/2015
 *      Author: buby
 */

#ifndef SRC_MODEL_JUGADORCPU_H_
#define SRC_MODEL_JUGADORCPU_H_

#include "Personaje.h"

const int DISTANCIA_PINA = 75;
const int DISTANCIA_PATADA = 100;
const int DISTANCIA_TOMA = 50;

class JugadorCPU {
public:
	JugadorCPU(Personaje* personaje_cpu, Personaje* personaje_1);
	virtual ~JugadorCPU();

	void realizarMovimiento();

private:
	Personaje* m_personaje_1;
	Personaje* m_personaje_cpu;
	int m_agresividad = 1;

	bool reaccion(int probabilidad);

	void evaluarAgresividad();

	bool noHayQueHacerNada();

	bool hayQueAtacar();
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
};

#endif /* SRC_MODEL_JUGADORCPU_H_ */
