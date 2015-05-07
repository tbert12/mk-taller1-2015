#include "Tiempo.h"

Tiempo::Tiempo(int segundos) {
	m_tiempoLimite = segundos;
	m_tiempoRestante = segundos;
	//time(&m_time);
	m_tiempo_de_inicio = m_time;
	m_tiempo_anterior = m_time;
}

void Tiempo::start(){
	//time(&m_tiempo_de_inicio);
	m_tiempoLimite = m_tiempo_de_inicio + m_tiempoRestante;
}

int Tiempo::getTiempo(){
	return m_tiempoRestante;
}

void Tiempo::actualizar(){
	time(&m_time);
	if (m_time - m_tiempo_anterior > 1)
		m_tiempoRestante -= 1;
	if (m_tiempoRestante < 0)
		m_tiempoRestante = 0;
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

