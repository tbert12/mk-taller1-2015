/*
 * JugadorCPU.h
 *
 *  Created on: 5/6/2015
 *      Author: buby
 */

#ifndef SRC_MODEL_JUGADORCPU_H_
#define SRC_MODEL_JUGADORCPU_H_

#include "Personaje.h"

class JugadorCPU {
public:
	JugadorCPU(Personaje* personaje_1, Personaje* personaje_cpu);
	virtual ~JugadorCPU();

	void realizarMovimiento();

	void evaluarAgresividad();

private:
	Personaje* m_personaje_1;
	Personaje* m_personaje_cpu;
	int m_agresividad = 1;

	bool reaccion(int probabilidad);

	bool hayQueAtacar();
	bool hayQueCubrirse();
	bool hayQueSaltar();
	bool hayQueAgacharse();
	bool hayQueAvanzar();
	bool hayQueRetroceder();

	bool hayQuePegarArriba();
	bool hayQuePegarAbajo();
	bool hayQueLanzarPoder();
	bool hayQueHacerToma();
};

#endif /* SRC_MODEL_JUGADORCPU_H_ */
