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
			probabilidad = 5;
			break;
		case 1:
			probabilidad = 10;
			break;
		case 2:
			probabilidad = 15;
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
			if (m_personaje_1->estaCubriendose()) {
				if (reaccion(probabilidad))
					return true;
				return false;
			} else
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
			if (m_personaje_1->estaCubriendose()) {
				if (reaccion(probabilidad))
					return true;
				return false;
			} else
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
	// No puede tirar poder mientras salta.
	if (m_personaje_cpu->estaSaltando())
		return false;

	int probabilidad;
	switch (m_agresividad) {
		case 0:
			probabilidad = 15;
			break;
		case 1:
			probabilidad = 12;
			break;
		case 2:
			probabilidad = 10;
			break;
		default:
			probabilidad = 0;
	}

	if (reaccion(probabilidad)) {
		if (m_personaje_1->estaCubriendose()) {
			if (reaccion(probabilidad)) {
				m_ciclos_delay = 20;
				return true;
			}
			return false;
		} else {
			m_ciclos_delay = 20;
			return true;
		}
	}
	return false;
}

bool JugadorCPU::hayQueHacerToma() {
	int probabilidad;
	switch (m_agresividad) {
		case 0:
			probabilidad = 5;
			break;
		case 1:
			probabilidad = 5;
			break;
		case 2:
			probabilidad = 10;
			break;
		default:
			probabilidad = 0;
	}

	if (reaccion(probabilidad)) {
		float dist = fabs(m_personaje_1->getX() - m_personaje_cpu->getX());
		if (dist <= DISTANCIA_TOMA)
			return true;
	}
	return false;
}

bool JugadorCPU::hayQueAtacar() {
	int probabilidad;
	switch (m_agresividad) {
		case 0:
			probabilidad = 30;
			break;
		case 1:
			probabilidad = 40;
			break;
		case 2:
			probabilidad = 75;
			break;
		default:
			probabilidad = 0;
	}

	if (reaccion(probabilidad)) {
		if (m_personaje_1->estaCubriendose()) {
			if (reaccion(probabilidad))
				return true;
			return false;
		} else
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
				m_ciclos_delay = 20;
				return true;
			} else {
				float dist = fabs(m_personaje_1->getX() - m_personaje_cpu->getX());
				if (dist <= DISTANCIA_PATADA) {
					m_ciclos_delay = 5;
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
			m_ciclos_delay = 10;
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
			probabilidad = 10;
			break;
		case 1:
			probabilidad = 2;
			break;
		case 2:
			probabilidad = 0;
			break;
		default:
			probabilidad = 0;
	}

	if (reaccion(probabilidad)) {
		float dist = fabs(m_personaje_1->getX() - m_personaje_cpu->getX());
		if (dist <= DISTANCIA_PATADA) {
			m_ciclos_delay = 5;
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
			probabilidad = 20;
			break;
		case 1:
			probabilidad = 25;
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
		}
	}
	return false;
}

bool JugadorCPU::hayQueAgacharse() {
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

	if (reaccion(probabilidad)) {
		float dist = fabs(m_personaje_1->getX() - m_personaje_cpu->getX());
		if (dist <= DISTANCIA_PINA) {
			if (!m_personaje_1->estaAgachado() && !m_personaje_1->estaCubriendose())
				m_ciclos_delay = 5;
				return true;
		}
	}
	return false;
}


void JugadorCPU::realizarMovimiento() {

	// Ciclos de delay.
	if (m_ciclos_delay != 0) {
		m_ciclos_delay--;
		return;
	}

	// Verificaciones de estado de Personaje CPU.
	if (m_personaje_cpu->estaCubriendose())
		m_personaje_cpu->dejarDeCubrirse();

	if (m_personaje_cpu->estaAgachado()) {
		if (hayQuePegarArriba()) {
			if (hayQuePegarPina())			// Caso particular del gancho.
				m_personaje_cpu->pinaAlta();
			else if (hayQuePegarPatada())
				m_personaje_cpu->patadaAlta();
		} else if (hayQuePegarAbajo()) {
			if (hayQuePegarPina())
				m_personaje_cpu->pinaBaja();
			else if (hayQuePegarPatada())
				m_personaje_cpu->patadaBaja();
		} else {
			m_personaje_cpu->Levantarse();
		}
		return;
	}

	if (m_personaje_cpu->enMovimiento() && !m_personaje_cpu->estaSaltando())
		m_personaje_cpu->Frenar();




	// Modifico actitud de acuerdo al desarrollo del combate.
	evaluarAgresividad();

	// Hacer fatality siempre que se pueda.


	// Posibilidad de no hacer nada.
	if (noHayQueHacerNada())
		return;

	// Posibilidades de defensa.
	if (hayQueCubrirse()) {
		m_personaje_cpu->cubrirse();
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
	}

	// Posibilidades de ataque.
	if (hayQueAtacar()) {
		if (hayQueLanzarPoder()) {
			m_personaje_cpu->poder1();
		} else if (hayQueHacerToma()) {
			m_personaje_cpu->toma1();
		} else if (hayQuePegarArriba()) {
			if (hayQuePegarPina())
				m_personaje_cpu->pinaAlta();
			else if (hayQuePegarPatada())
				m_personaje_cpu->patadaAlta();
		} else if (hayQuePegarAbajo()) {
			if (hayQuePegarPina())
				m_personaje_cpu->pinaBaja();
			else if (hayQuePegarPatada())
				m_personaje_cpu->patadaBaja();
		}
	}

}


