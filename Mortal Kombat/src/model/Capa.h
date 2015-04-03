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
#include <string>

class Capa : public Renderizable{
public:
	int getZIndex();
	void Actualizar();
	void Mover(int posX);
	int getX();
	Capa(int alto, int ancho, int zIndex, int anchoDeFondo, float velocidadPrincipal);
	bool cargarBackground(std::string background);

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
