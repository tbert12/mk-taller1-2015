/*
 * Capa.h
 *
 *  Created on: Mar 26, 2015
 *      Author: root
 */

#ifndef SRC_MODEL_CAPA_H_
#define SRC_MODEL_CAPA_H_

#include "Renderizable.h"
#include "Ventana.h"
#include <list>
#include <string>

class Capa{
public:
	int getZIndex();
	void Actualizar();
	virtual void Mover(bool right);
	int getX();
	virtual void Renderizar();
	Capa(float alto, float ancho, int zIndex, float anchoDeFondo, float velocidadPrincipal, Ventana* ventana);

private:
	float m_alto;
	int m_zIndex;
	float m_anchoDeFondo;
	float m_anchoDeVentana;
	float m_velocidad;
protected:
	float m_ancho;
	float m_XActual;
};

#endif /* SRC_MODEL_CAPA_H_ */
