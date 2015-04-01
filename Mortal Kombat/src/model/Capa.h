/*
 * Capa.h
 *
 *  Created on: Mar 26, 2015
 *      Author: root
 */

#ifndef SRC_MODEL_CAPA_H_
#define SRC_MODEL_CAPA_H_

#include "Renderizable.h"
<<<<<<< HEAD
#include <list>
=======
#include <string>
>>>>>>> b76f3b85e7f4d08d14f518dabad4098d04f42201

class Capa : public Renderizable{
public:
	int getZIndex();
	void Actualizar();
	void Mover(int posX);
	Capa(int alto, int ancho, int zIndex, int anchoDeFondo, int velocidadPrincipal);
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
