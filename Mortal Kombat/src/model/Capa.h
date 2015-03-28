/*
 * Capa.h
 *
 *  Created on: Mar 26, 2015
 *      Author: root
 */

#ifndef SRC_MODEL_CAPA_H_
#define SRC_MODEL_CAPA_H_

#include "Renderizable.h"

class Capa : public Renderizable{
public:
	int getZIndex();
	void Actualizar();
	void Mover(int posX);
	Capa(int alto, int ancho, int zIndex, int anchoDeFondo, int velocidadPrincipal);

private:
	int m_ancho;
	int m_alto;
	int m_zIndex;
	int m_XActual;
	float m_velocidad;
};

#endif /* SRC_MODEL_CAPA_H_ */
