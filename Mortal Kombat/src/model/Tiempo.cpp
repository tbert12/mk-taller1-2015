#include "Tiempo.h"

Tiempo::Tiempo(int segundos) {
	m_tiempoLimite = segundos;
	m_tiempoRestante = segundos;
	time(&tiempo);
}

void Tiempo::start(){
	time(&tiempo);
}

int Tiempo::getTiempo(){
	return m_tiempoRestante;
}

void Tiempo::reset(){
	m_tiempoRestante = m_tiempoLimite;
}

void Tiempo::actualizar(){
	std::time_t tiempo_actual;
	time(&tiempo_actual);
	double transcurrido = difftime(tiempo_actual,tiempo);
	if (transcurrido >= 1.0){
		m_tiempoRestante -= 1;
		tiempo = tiempo_actual;
	}
	if (m_tiempoRestante < 0)
		m_tiempoRestante = 0;
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

}

