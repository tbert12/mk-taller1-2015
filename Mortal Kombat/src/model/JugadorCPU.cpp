/*
 * JugadorCPU.cpp
 *
 *  Created on: 5/6/2015
 *      Author: buby
 */

#include "JugadorCPU.h"


JugadorCPU::JugadorCPU(Personaje* personaje_cpu, Personaje* personaje_1) {
	m_personaje_1 = personaje_1;
	m_personaje_cpu = personaje_cpu;
}


JugadorCPU::~JugadorCPU() {
	// TODO Auto-generated destructor stub
}

bool JugadorCPU::reaccion(int probabilidad) {
	bool exito = (rand() % 100) < probabilidad;
	return exito;
}

void JugadorCPU::evaluarAgresividad() {
	int vida_propia = m_personaje_cpu->getVida();
	int vida_rival = m_personaje_1->getVida();

	if (vida_propia > 75) {
		if (vida_rival > 75)
			m_agresividad = 0;	// Modo conservador.
		else
			m_agresividad = 1;	// Modo normal.
	} else if (vida_propia < 25) {
		if (vida_rival > 75 || vida_rival < vida_propia)
			m_agresividad = 2;	// Modo agresivo.
		else
			m_agresividad = 0;
	} else {	// 25 <= vida_propia <= 75
		if (vida_rival > 75)
			m_agresividad = 0;
		else if (vida_rival < 25)
			m_agresividad = 2;
		else
			m_agresividad = 1;
	}
}

bool JugadorCPU::noHayQueHacerNada() {
	int probabilidad;
	switch (m_agresividad) {
		case 0:
			probabilidad = 10;
			break;
		case 1:
			probabilidad = 5;
			break;
		case 2:
			probabilidad = 2;
			break;
		default:
			probabilidad = 0;
	}
	return reaccion(probabilidad);
}

bool JugadorCPU::hayQuePegarPina() {

}

bool JugadorCPU::hayQuePegarPatada() {

}

bool JugadorCPU::hayQuePegarArriba() {

}

bool JugadorCPU::hayQuePegarAbajo() {

}

bool JugadorCPU::hayQueLanzarPoder() {

}

bool JugadorCPU::hayQueHacerToma() {

}

bool JugadorCPU::hayQueAtacar() {

}

bool JugadorCPU::hayQueCubrirse() {

}

bool JugadorCPU::hayQueAvanzar() {

}

bool JugadorCPU::hayQueRetroceder() {

}

// HAY QUE SALTAR, HAY QUE SALTAR, EL QUE NO SALTA ES DE HURACAN!
bool JugadorCPU::hayQueSaltar() {

}

bool JugadorCPU::hayQueAgacharse() {

}

void JugadorCPU::realizarMovimiento() {

	// Modifico actitud de acuerdo al desarrollo del combate.
	evaluarAgresividad();

	// Posibilidad de no hacer nada.
	if (noHayQueHacerNada())
		return;

	// Posibilidades de desplazamiento.


	// Posibilidades de ataque.
	if (hayQueAtacar()) {
		if (hayQuePegarArriba()) {
			if (hayQuePegarPina())
				m_personaje_cpu->pinaAlta();
			else if (hayQuePegarPatada())
				m_personaje_cpu->patadaAlta();
		} else if (hayQuePegarAbajo()) {
			if (hayQuePegarPina())
				m_personaje_cpu->pinaBaja();
			else if (hayQuePegarPatada())
				m_personaje_cpu->patadaBaja();
		} else if (hayQueHacerToma()) {
			m_personaje_cpu->toma1();
		} else if (hayQueLanzarPoder()) {
			m_personaje_cpu->poder1();
		}
	}

}


