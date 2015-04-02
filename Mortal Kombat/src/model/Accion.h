/*
 * Accion.h
 *
 *  Created on: 1/4/2015
 *      Author: facu
 */

#ifndef SRC_MODEL_ACCION_H_
#define SRC_MODEL_ACCION_H_

class Accion {

private:
	size_t m_accion;
	size_t m_accionSiguiente;

public:
	Accion(size_t accion, size_t siguiente);
	virtual ~Accion();

	size_t getAccion();
	size_t getSiguiente();
};

#endif /* SRC_MODEL_ACCION_H_ */
