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
	unsigned int m_accion;
	unsigned int m_accionSiguiente;

public:
	Accion(unsigned int accion, unsigned int siguiente);
	virtual ~Accion();

	unsigned int getAccion();
	unsigned int getSiguiente();
};

#endif /* SRC_MODEL_ACCION_H_ */
