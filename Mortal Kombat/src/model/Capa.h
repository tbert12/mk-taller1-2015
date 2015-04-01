/*
 * Capa.h
 *
 *  Created on: Mar 26, 2015
 *      Author: root
 */

#ifndef SRC_MODEL_CAPA_H_
#define SRC_MODEL_CAPA_H_

#include "Renderizable.h"
#include <list>

class Capa : public Renderizable{
public:
	int getZIndex();
	void Actualizar();
	void Mover(int posX);
	Capa(int alto, int ancho, int zIndex, int anchoDeFondo, int velocidadPrincipal);

private:
	int m_alto;
	int m_zIndex;
	int m_XActual;
	int m_anchoDeFondo;
	float m_velocidad;
protected:
	int m_ancho;
};

#endif /* SRC_MODEL_CAPA_H_ */
