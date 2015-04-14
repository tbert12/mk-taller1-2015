/*
 * Capa.h
 *
 *  Created on: Mar 26, 2015
 *      Author: root
 */

#ifndef SRC_MODEL_CAPA_H_
#define SRC_MODEL_CAPA_H_

#include "Renderizable.h"
#include "../view/LTexture.h"
#include <list>
#include <string>

class Capa{
public:
	int getZIndex();
	void Actualizar();
	void Mover(bool right);
	float getX();
	virtual void Renderizar();
	Capa(float alto, float ancho, int zIndex, float anchoDeFondo,float ancho_ventana, float velocidadPrincipal);
	virtual ~Capa();
protected:
	int m_zIndex;
	float m_anchoDeFondo;
	float m_velocidad;
	Rect_Logico* rect;
	float m_ancho_ventana;
};

#endif /* SRC_MODEL_CAPA_H_ */
