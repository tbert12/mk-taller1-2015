/*
 * Accion.cpp
 *
 *  Created on: 1/4/2015
 *      Author: facu
 */

#include "Accion.h"

Accion::Accion(unsigned int accion, unsigned int siguiente) {
	m_accion = accion;
	m_accionSiguiente = siguiente;
}

unsigned int Accion::getAccion(){
	return m_accion;
}

unsigned int Accion::getSiguiente(){
	return m_accionSiguiente;
}

Accion::~Accion() {
	// TODO Auto-generated destructor stub
	// RE DE CRACK USAR ESTO DEL TODO Y HABLAR EN INGLES
}

