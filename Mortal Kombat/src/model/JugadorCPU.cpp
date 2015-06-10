/*
 * JugadorCPU.cpp
 *
 *  Created on: 5/6/2015
 *      Author: buby
 */

#include "JugadorCPU.h"

enum Personajes_id { LIUKANG, SUBZERO };

JugadorCPU::JugadorCPU(Personaje* personaje_cpu, Personaje* personaje_1) {
	m_personaje_1 = personaje_1;
	m_personaje_cpu = personaje_cpu;

	string nombre_personaje_cpu = m_personaje_cpu->getNombre();
	if (! nombre_personaje_cpu.string::compare(string("Liu Kang")) )
		m_id_personaje = LIUKANG;
	else if (! nombre_personaje_cpu.string::compare(string("Sub-Zero")) )
		m_id_personaje = SUBZERO;

}


JugadorCPU::~JugadorCPU() {
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
			m_agresividad = 1;	// Modo normal.
		else
			m_agresividad = 0;	// Modo conservador.
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
			probabilidad = 15;
			break;
		case 1:
			probabilidad = 10;
			break;
		case 2:
			probabilidad = 5;
			break;
		default:
			probabilidad = 100;
	}
	return reaccion(probabilidad);
}

bool JugadorCPU::hayQuePegarPina() {
	// Caso particular del gancho para pina alta estando agachado.
	// No se trabaja con probabilidades en este caso.
	float dist = fabs(m_personaje_1->getX() - m_personaje_cpu->getX());
	if (dist <= DISTANCIA_PINA) {
		if (m_personaje_1->estaAtacando() && !m_personaje_1->estaAgachado()) {
			return true;
		}
	}

	int probabilidad;
	switch (m_agresividad) {
		case 0:
			probabilidad = 40;
			break;
		case 1:
			probabilidad = 60;
			break;
		case 2:
			probabilidad = 80;
			break;
		default:
			probabilidad = 0;
	}

	if (reaccion(probabilidad)) {
		if (dist <= DISTANCIA_PINA) {
			return true;
		}
	}
	return false;
}

bool JugadorCPU::hayQuePegarPatada() {
	int probabilidad;
	switch (m_agresividad) {
		case 0:
			probabilidad = 30;
			break;
		case 1:
			probabilidad = 50;
			break;
		case 2:
			probabilidad = 70;
			break;
		default:
			probabilidad = 0;
	}

	if (reaccion(probabilidad)) {
		float dist = fabs(m_personaje_1->getX() - m_personaje_cpu->getX());
		if (dist <= DISTANCIA_PATADA) {
			return true;
		}
	}
	return false;
}

bool JugadorCPU::hayQuePegarArriba() {
	int probabilidad;
	switch (m_agresividad) {
		case 0:
			probabilidad = 30;
			break;
		case 1:
			probabilidad = 40;
			break;
		case 2:
			probabilidad = 50;
			break;
		default:
			probabilidad = 0;
	}

	if (reaccion(probabilidad)) {
		if (m_personaje_1->estaCubriendose() && !m_personaje_1->estaAgachado()) {
			if (reaccion(probabilidad))
				return true;
			return false;
		} else if (!m_personaje_1->estaAgachado())
			return true;
	}
	return false;
}

bool JugadorCPU::hayQuePegarAbajo() {
	int probabilidad;
	switch (m_agresividad) {
		case 0:
			probabilidad = 30;
			break;
		case 1:
			probabilidad = 40;
			break;
		case 2:
			probabilidad = 50;
			break;
		default:
			probabilidad = 0;
	}

	if (reaccion(probabilidad)) {
		if (m_personaje_1->estaCubriendose()) {
			if (reaccion(probabilidad)) {
				return true;
			} else if (m_personaje_1->estaAgachado()) {
				return true;
			} else {
				return false;
			}
		} else
			return true;
	}
	return false;
}

bool JugadorCPU::hayQueLanzarPoder() {

	int probabilidad;
	switch (m_agresividad) {
		case 0:
			probabilidad = 10;
			break;
		case 1:
			probabilidad = 15;
			break;
		case 2:
			probabilidad = 20;
			break;
		default:
			probabilidad = 0;
	}

	if (reaccion(probabilidad)) {
		float dist = fabs(m_personaje_1->getX() - m_personaje_cpu->getX());
		if (dist >= DISTANCIA_PATADA * 2) {
			if (m_personaje_1->estaCubriendose()) {
				if (reaccion(probabilidad)) {
					return true;
				}
				return false;
			} else {
				return true;
			}
		} else if ( (dist > DISTANCIA_PATADA && dist < DISTANCIA_PATADA * 2) ) {
			if (m_personaje_1->estaAtacando()) {
				return true;
			} else if (reaccion(probabilidad)) {
				return true;
			}
		} else {
			if (reaccion(probabilidad))
				return true;
		}
	}
	return false;
}

bool JugadorCPU::hayQueHacerToma() {
	int probabilidad;
	switch (m_agresividad) {
		case 0:
			probabilidad = 15;
			break;
		case 1:
			probabilidad = 20;
			break;
		case 2:
			probabilidad = 25;
			break;
		default:
			probabilidad = 0;
	}

	if (reaccion(probabilidad)) {
		float dist = fabs(m_personaje_1->getX() - m_personaje_cpu->getX());
		if (dist <= DISTANCIA_TOMA && m_personaje_1->estaCubriendose())
			return true;
	}
	return false;
}

bool JugadorCPU::hayQueCubrirse() {
	int probabilidad;
	switch (m_agresividad) {
		case 0:
			probabilidad = 75;
			break;
		case 1:
			probabilidad = 50;
			break;
		case 2:
			probabilidad = 25;
			break;
		default:
			probabilidad = 0;
	}

	if (reaccion(probabilidad)) {
		if (m_personaje_1->estaAtacando()) {
			if (m_personaje_1->getAccionDeAtaque() == SPRITE_PODER_1
					|| m_personaje_1->getAccionDeAtaque() == SPRITE_PODER_2) {
				return true;
			} else {
				float dist = fabs(m_personaje_1->getX() - m_personaje_cpu->getX());
				if (dist <= DISTANCIA_PATADA) {
					return true;
				}
			}
		}
	}
	return false;
}

bool JugadorCPU::hayQueAvanzar() {
	int probabilidad;
	switch (m_agresividad) {
		case 0:
			probabilidad = 30;
			break;
		case 1:
			probabilidad = 40;
			break;
		case 2:
			probabilidad = 50;
			break;
		default:
			probabilidad = 0;
	}

	if (reaccion(probabilidad)) {
		float dist = fabs(m_personaje_1->getX() - m_personaje_cpu->getX());
		if (dist >= DISTANCIA_PATADA) {
			return true;
		} else if (dist < DISTANCIA_PATADA && dist >= DISTANCIA_TOMA) {
			if (reaccion(probabilidad))
				return true;
		}
	}
	return false;
}

bool JugadorCPU::hayQueRetroceder() {
	int probabilidad;
	switch (m_agresividad) {
		case 0:
			probabilidad = 15;
			break;
		case 1:
			probabilidad = 10;
			break;
		case 2:
			probabilidad = 5;
			break;
		default:
			probabilidad = 0;
	}

	if (reaccion(probabilidad)) {
		float dist = fabs(m_personaje_1->getX() - m_personaje_cpu->getX());
		if (dist <= DISTANCIA_PATADA) {
			return true;
		}
	}
	return false;
}

// HAY QUE SALTAR, HAY QUE SALTAR, EL QUE NO SALTA ES DE HURACAN!
bool JugadorCPU::hayQueSaltar() {
	int probabilidad;
	switch (m_agresividad) {
		case 0:
			probabilidad = 10;
			break;
		case 1:
			probabilidad = 20;
			break;
		case 2:
			probabilidad = 30;
			break;
		default:
			probabilidad = 0;
	}

	if (reaccion(probabilidad)) {
		float dist = fabs(m_personaje_1->getX() - m_personaje_cpu->getX());
		if (dist > DISTANCIA_PATADA) {
			return true;
		} else if (m_personaje_1->getAccionDeAtaque() == SPRITE_PODER_1
				|| m_personaje_1->getAccionDeAtaque() == SPRITE_PODER_2) {
			return true;
		}
	}
	return false;
}

bool JugadorCPU::hayQueAgacharse() {
	int probabilidad;
	switch (m_agresividad) {
		case 0:
			probabilidad = 15;
			break;
		case 1:
			probabilidad = 10;
			break;
		case 2:
			probabilidad = 5;
			break;
		default:
			probabilidad = 0;
	}

	if (reaccion(probabilidad)) {
		float dist = fabs(m_personaje_1->getX() - m_personaje_cpu->getX());
		if (dist <= DISTANCIA_PINA) {
			if (!m_personaje_1->estaAgachado()) {
				if (reaccion(probabilidad))
					return true;
			} else {
				return true;
			}
		} else if (m_personaje_1->getAccionDeAtaque() == SPRITE_PODER_1
				|| m_personaje_1->getAccionDeAtaque() == SPRITE_PODER_2) {
			return true;
		}
	}
	return false;
}


void JugadorCPU::realizarMovimiento() {

	// Si termino el round, no puede moverse.
	if (m_personaje_cpu->getAccionDeAtaque() == SPRITE_MUERE || m_personaje_cpu->getAccionDeAtaque() == SPRITE_FINISH
|| m_personaje_cpu->getAccionDeAtaque() == SPRITE_GANA) {
		m_personaje_cpu->Frenar();
		return;
	}

	// Ciclos de delay.
	if (m_ciclos_delay != 0) {
		m_ciclos_delay--;
		return;
	}

	// Verificaciones de estado de Personaje CPU.
	if (m_personaje_cpu->estaCubriendose()) {
		m_personaje_cpu->dejarDeCubrirse();
		return;
	}

	if (m_personaje_cpu->estaAgachado()) {
		if (hayQuePegarArriba()) {
			if (hayQuePegarPina())	{		// Caso particular del gancho.
				m_personaje_cpu->pinaAlta();
				m_ciclos_delay = 20;
			} else if (hayQuePegarPatada()) {
				m_personaje_cpu->patadaAlta();
				m_ciclos_delay = 5;
			}
		} else if (hayQuePegarAbajo()) {
			if (hayQuePegarPina()) {
				m_personaje_cpu->pinaBaja();
				m_ciclos_delay = 5;
			} else if (hayQuePegarPatada()) {
				m_personaje_cpu->patadaBaja();
				m_ciclos_delay = 5;
			}
		} else if (hayQueCubrirse()) {
			m_personaje_cpu->cubrirse();
			m_ciclos_delay = 5;
		} else {
			m_personaje_cpu->Levantarse();
		}
		return;
	}


	// Modifico actitud de acuerdo al desarrollo del combate.
	evaluarAgresividad();

	// Hacer fatality siempre que se pueda.
	if (m_personaje_1->getAccionDeAtaque() == SPRITE_FINISH) {
		m_personaje_cpu->Frenar();
		switch (m_id_personaje) {
			case LIUKANG:
				m_personaje_cpu->fatality1(m_personaje_1);
				break;
			case SUBZERO:
				m_personaje_cpu->fatality1(m_personaje_1);
				break;
			default:
				m_personaje_cpu->fatality1(m_personaje_1);
		}

	}

	// Posibilidad de no hacer nada.
	if (noHayQueHacerNada())
		return;

	// Posibilidades de defensa.
	if (hayQueCubrirse()) {
		m_personaje_cpu->cubrirse();
		m_ciclos_delay = 5;
		return;
	}

	// Posibilidades de desplazamiento.
	if (hayQueAvanzar()) {
		if (m_personaje_cpu->getFlipState())
			m_personaje_cpu->CaminarIzquierda();
		else
			m_personaje_cpu->CaminarDerecha();
	} else if (hayQueRetroceder()) {
		if (m_personaje_cpu->getFlipState())
			m_personaje_cpu->CaminarDerecha();
		else
			m_personaje_cpu->CaminarIzquierda();
	} else if (hayQueSaltar()) {
		m_personaje_cpu->Saltar();
	} else if (hayQueAgacharse()) {
		m_personaje_cpu->Agachar();
		m_ciclos_delay = 5;
	}

	// Posibilidades de ataque.
	if (hayQueLanzarPoder()) {
		if (!m_personaje_cpu->estaSaltando()) {
			m_personaje_cpu->Frenar();
			// Cada personaje tiene poderes distintos.
			float dist = fabs(m_personaje_1->getX() - m_personaje_cpu->getX());
			switch (m_id_personaje) {
				case LIUKANG:
					if (dist < DISTANCIA_PATADA * 2 || reaccion(50))
						m_personaje_cpu->poder1();
					else
						m_personaje_cpu->poder2();
					break;
				case SUBZERO:
					if (dist <= DISTANCIA_PATADA)
						m_personaje_cpu->poder2();
					else
						m_personaje_cpu->poder1();
					break;
				default:
					m_personaje_cpu->poder1();
			}
			m_ciclos_delay = 20;
		}
	} else if (hayQueHacerToma()) {
		if (!m_personaje_cpu->estaSaltando()) {
			m_personaje_cpu->toma1();
			m_ciclos_delay = 10;
		}
	} else if (hayQuePegarArriba()) {
		if (hayQuePegarPina()) {
			m_personaje_cpu->pinaAlta();
			m_ciclos_delay = 2;
		} else if (hayQuePegarPatada()) {
			m_personaje_cpu->patadaAlta();
			m_ciclos_delay = 2;
		}
	} else if (hayQuePegarAbajo()) {
		if (hayQuePegarPina()) {
			m_personaje_cpu->pinaBaja();
			m_ciclos_delay = 2;
		} else if (hayQuePegarPatada()) {
			m_personaje_cpu->patadaBaja();
			m_ciclos_delay = 2;
		}
	}

}


