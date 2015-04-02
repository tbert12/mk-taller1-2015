/*
 * Accion.cpp
 *
 *  Created on: 1/4/2015
 *      Author: facu
 */

#include "Accion.h"

Accion::Accion(size_t accion, size_t siguiente) {
	m_accion = accion;
	m_accionSiguiente = siguiente;
}

size_t Accion::getAccion(){
	return m_accion;
}

size_t Accion::getSiguiente(){
	return m_accionSiguiente;
}

Accion::~Accion() {
	// TODO Auto-generated destructor stub
	// RE DE CRACK USAR ESTO DEL TODO Y HABLAR EN INGLES
}

