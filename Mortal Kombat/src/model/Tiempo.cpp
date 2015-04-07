

#include "Tiempo.h"

Tiempo::Tiempo(int segundos) {
	m_tiempoLimite = segundos;
	m_tiempoRestante = segundos;
}

bool Tiempo::transcurrir(int segundos) {
	if ( ! this->tiempoTerminado() ) {
		m_tiempoRestante = m_tiempoRestante - segundos;
		if ( m_tiempoRestante < 0 ) {
			m_tiempoRestante = 0;
		}
		return true;
	} else {
		return false;
	}
}

bool Tiempo::tiempoTerminado() {
	if ( m_tiempoRestante == 0 ) {
		return true;
	} else {
		return false;
	}
}

float Tiempo::tiempoEnMinutos() {
	float minutos = m_tiempoRestante / 60.0;
	return minutos;
}

Tiempo::~Tiempo() {
	// TODO Auto-generated destructor stub
}

